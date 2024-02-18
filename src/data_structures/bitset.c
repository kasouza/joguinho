#include "joguinho/data_structures/bitset.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Bitset *create_bitset() {
    Bitset *bitset = malloc(sizeof(Bitset));
    if (!bitset) {
        return NULL;
    }

    bitset->bits = calloc(BITSET_INITIAL_CAP, sizeof(uint8_t));
    if (!bitset->bits) {
        free(bitset);
        return NULL;
    }

    bitset->cap = BITSET_INITIAL_CAP;

    return bitset;
}

void bitset_set(Bitset *bitset, size_t idx, bool val) {
    if (idx >= (bitset->cap * sizeof(*bitset->bits) * 8)) {
        size_t new_cap = bitset->cap * 2;

        uint8_t *new_bits = calloc(new_cap, sizeof(*bitset->bits));
        for (size_t i = 0; i < bitset->cap; i++) {
            new_bits[i] = bitset->bits[i];
        }

        bitset->bits = new_bits;
        bitset->cap = new_cap;
    }

    size_t bits_len = (bitset->cap * sizeof(*bitset->bits) * 8);
    size_t array_idx = idx / (sizeof(*bitset->bits) * 8);
    size_t bit_idx = idx - (array_idx * sizeof(*bitset->bits) * 8);

    bitset->bits[array_idx] |= ((uint8_t)val << bit_idx);
}

bool bitset_get(Bitset *bitset, size_t idx) {
    assert(idx <= (bitset->cap * sizeof(*bitset->bits) * 8));

    size_t bits_len = (bitset->cap * sizeof(*bitset->bits) * 8);
    size_t array_idx = idx / (sizeof(*bitset->bits) * 8);
    size_t bit_idx = idx - (array_idx * sizeof(*bitset->bits) * 8);

    return (bitset->bits[array_idx] >> bit_idx) & (uint8_t)1;
}

void free_bitset(Bitset *bitset) {
    if (bitset->bits) {
        free(bitset->bits);
    }

    free(bitset);
}
