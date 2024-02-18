#include "./data_structures/dynarr.h"
#include "./test.h"
#include "data_structures/bitset.h"
#include "data_structures/map.h"

int main(void) {
    test_suite_dynarr();
    test_suite_map();
    test_suite_bitset();
    t_run_tests();
    return 0;
}
