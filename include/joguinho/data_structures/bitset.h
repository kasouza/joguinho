#ifndef KASOUZA_JOGUINHO_INCLUDE_JOGUINHO_DATA_STRUCTURES_INCLUDE_JOGUINHO_DATA_STRUCTURES_BITSET_H
#define KASOUZA_JOGUINHO_INCLUDE_JOGUINHO_DATA_STRUCTURES_INCLUDE_JOGUINHO_DATA_STRUCTURES_BITSET_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define BITSET_INITIAL_CAP 1

typedef struct {
    uint8_t *bits;
    size_t cap;
} Bitset;

Bitset *create_bitset();
void bitset_set(Bitset *bitset, size_t idx, bool val);
bool bitset_get(Bitset *bitset, size_t idx);
void free_bitset(Bitset *bitset);

#endif
