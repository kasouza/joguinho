#include "./map.h"
#include "../test.h"
#include "joguinho/data_structures/dynarr.h"
#include "joguinho/data_structures/map.h"

int compare_ints(const void *a, const void *b) {
    return *((int *)a) - *((int *)b);
}

bool test_create_map() {
    Map *map = create_map(int, int, compare_ints);
    t_ASSERT(map != NULL);
    t_ASSERT(map->compare == compare_ints);
    t_ASSERT(map->keys != NULL);
    t_ASSERT(map->values != NULL);
    t_ASSERT(map->keys->stride == sizeof(int));
    t_ASSERT(map->values->stride == sizeof(int));

    free_map(map);
    map = NULL;

    return true;
}

bool test_map_set() {
    Map *map = create_map(int, int, compare_ints);

    map_set_literal(map, int, 33, int, 54);
    map_set_literal(map, int, 22, int, 93);

    t_ASSERT(dynarr_at(map->keys, int, 0) == 33);
    t_ASSERT(dynarr_at(map->values, int, 0) == 54);

    t_ASSERT(dynarr_at(map->keys, int, 1) == 22);
    t_ASSERT(dynarr_at(map->values, int, 1) == 93);

    map_set_literal(map, int, 33, int, 94);
    t_ASSERT(dynarr_at(map->keys, int, 0) == 33);
    t_ASSERT(dynarr_at(map->values, int, 0) == 94);

    t_ASSERT(dynarr_at(map->keys, int, 1) == 22);
    t_ASSERT(dynarr_at(map->values, int, 1) == 93);

    return true;
}

bool test_map_get() {
    Map *map = create_map(int, int, compare_ints);

    map_set_literal(map, int, 33, int, 54);
    map_set_literal(map, int, 22, int, 93);

    t_ASSERT(dynarr_at(map->values, int, 0) == *map_get_literal(map, int, 33));
    t_ASSERT(dynarr_at(map->values, int, 1) == *map_get_literal(map, int, 22));

    map_set_literal(map, int, 33, int, 94);
    t_ASSERT(dynarr_at(map->values, int, 0) == *map_get_literal(map, int, 33));
    t_ASSERT(dynarr_at(map->values, int, 1) == *map_get_literal(map, int, 22));

    t_ASSERT(NULL == map_get_literal(map, int, 999));

    return true;
}

bool test_map_remove() {
    Map *map = create_map(int, int, compare_ints);

    map_set_literal(map, int, 33, int, 54);
    map_set_literal(map, int, 22, int, 93);

    t_ASSERT(dynarr_at(map->values, int, 0) == *map_get_literal(map, int, 33));
    t_ASSERT(dynarr_at(map->values, int, 1) == *map_get_literal(map, int, 22));

    map_remove_literal(map, int, 33);
    t_ASSERT(NULL == map_get_literal(map, int, 33));
    t_ASSERT(dynarr_at(map->values, int, 1) == *map_get_literal(map, int, 22));

    map_remove_literal(map, int, 22);
    t_ASSERT(NULL == map_get_literal(map, int, 22));

    return true;
}

void test_suite_map() {
    t_register_test(test_create_map);
    t_register_test(test_map_set);
    t_register_test(test_map_get);
    t_register_test(test_map_remove);
}
