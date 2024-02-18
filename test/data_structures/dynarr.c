#include "joguinho/data_structures/dynarr.h"
#include "../test.h"
#include <stdlib.h>

bool test_array_create() {
    DynArr *array = create_dynarr(int);
    t_ASSERT(array != NULL);
    t_ASSERT(array->dat != NULL);
    t_ASSERT(array->cap == DYNARR_INITIAL_CAP);
    t_ASSERT(array->len == 0);
    t_ASSERT(array->stride == sizeof(int));

    free_dynarr(array);
    array = NULL;

    return true;
}

bool test_array_push() {
    DynArr *array = create_dynarr(int);
    t_ASSERT(array->cap == DYNARR_INITIAL_CAP);

    int *data = (int *)(array->dat);

    int a = 33;
    dynarr_push(array, &a);
    t_ASSERT(data[0] == 33);

    dynarr_push_literal(array, int, 54);
    t_ASSERT(data[0] == 33);
    t_ASSERT(data[1] == 54);

    free_dynarr(array);
    array = NULL;
    data = NULL;

    DynArr *array2 = _create_dynarr(sizeof(int), 8);

    for (size_t i = 0; i < 9; i++) {
        dynarr_push(array2, &i);
        int *data2 = (int *)array2->dat;
        t_ASSERT(data2[i] == i);
    }

    t_ASSERT(array2->cap > DYNARR_INITIAL_CAP);

    size_t previous_capacity = array2->cap;
    for (size_t i = 0; i < 30; i++) {
        dynarr_push_literal(array2, int, 54 * i);

        int *data2 = (int *)array2->dat;
        t_ASSERT(data2[array2->len - 1] == 54 * i);
    }

    t_ASSERT(array2->cap > DYNARR_INITIAL_CAP);
    free_dynarr(array2);

    return true;
}

bool test_array_resize() {
    DynArr *array = create_dynarr(int);
    t_ASSERT(array->cap == DYNARR_INITIAL_CAP);

    dynarr_resize(array, 32);
    t_ASSERT(array->cap == 32);

    free_dynarr(array);
    array = NULL;

    return true;
}

void test_suite_dynarr() {
    t_register_test(test_array_create);
    t_register_test(test_array_push);
    t_register_test(test_array_resize);
}
