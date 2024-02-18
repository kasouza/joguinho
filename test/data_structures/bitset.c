#include "./bitset.h"
#include "../test.h"

#include "joguinho/data_structures/bitset.h"

#include <stdbool.h>
#include <stdint.h>

bool test_create_bitset() {
    Bitset *bitset = create_bitset();
    t_ASSERT(bitset != NULL);
    t_ASSERT(bitset->bits != NULL);
    t_ASSERT(bitset->cap = BITSET_INITIAL_CAP);

    free_bitset(bitset);
    bitset = NULL;

    return true;
}

bool test_bitset() {
    Bitset *bitset = create_bitset();

    for (size_t i = 0; i < 256; i++) {
        bitset_set(bitset, i, (i % 7 || i % 3) == 0);
    }

    for (size_t i = 0; i < 256; i++) {
        t_ASSERT(bitset_get(bitset, i) == ((i % 7 || i % 3) == 0));
    }

    free_bitset(bitset);
    bitset = NULL;

    return true;
}

void test_suite_bitset() {
    t_register_test(test_create_bitset);
    t_register_test(test_bitset);
}
