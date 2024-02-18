#ifndef KASOUZA_JOGUINHO_INCLUDE_JOGUINHO_DATA_STRUCTURES_INCLUDE_JOGUINHO_DATA_STRUCTURES_MAP_H
#define KASOUZA_JOGUINHO_INCLUDE_JOGUINHO_DATA_STRUCTURES_INCLUDE_JOGUINHO_DATA_STRUCTURES_MAP_H

#include "joguinho/data_structures/dynarr.h"

typedef int (*compare_t)(const void *a, const void *b);

typedef struct {
    DynArr *keys;
    DynArr *values;
    compare_t compare;
} Map;

#define create_map(key_type, value_type, compare)                              \
    _create_map(sizeof(key_type), sizeof(value_type), compare)

Map *_create_map(size_t key_stride, size_t value_stride, compare_t compare);

#define map_set_literal(map, key_type, key, val_type, val)                     \
    do {                                                                       \
        key_type __MAP_TEMP_KEY__ = key;                                       \
        val_type __MAP_TEMP_VAL__ = val;                                       \
        map_set(map, &__MAP_TEMP_KEY__, &__MAP_TEMP_VAL__);                    \
    } while (false)
void map_set(Map *map, void *key, void *value);

#define map_get_literal(map, type, key) ((type *)_map_get(map, &(type){key}))
#define map_get(map, type, key) ((type *)_map_get(map, key))
void *_map_get(Map *map, const void *key);

#define map_remove_literal(map, type, key) map_remove(map, &(type){key})
void map_remove(Map *map, const void *key);

void free_map(Map *map);

#endif
