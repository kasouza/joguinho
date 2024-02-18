#include "joguinho/data_structures/map.h"
#include "joguinho/data_structures/dynarr.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Map *_create_map(size_t key_stride, size_t value_stride, compare_t compare) {
    assert(key_stride > 0);
    assert(value_stride > 0);
    assert(compare != NULL);

    Map *map = malloc(sizeof(Map));
    if (!map) {
        return NULL;
    }

    map->keys = _create_dynarr(key_stride, DYNARR_INITIAL_CAP);
    if (!map->keys) {
        free(map);
        return NULL;
    }

    map->values = _create_dynarr(value_stride, DYNARR_INITIAL_CAP);
    if (!map->values) {
        free_dynarr(map->keys);
        free(map);
        return NULL;
    }

    map->compare = compare;

    return map;
}

void map_set(Map *map, void *key, void *value) {
    assert(map != NULL);
    assert(key != NULL);
    assert(value != NULL);

    for (size_t i = 0; i < map->keys->len; i++) {
        if (map->compare(dynarr_bytes_at(map->keys, i), key) == 0) {
            dynarr_set(map->values, i, value);
            return;
        }
    }

    dynarr_push(map->keys, key);
    dynarr_push(map->values, value);
}

void *_map_get(Map *map, const void *key) {
    for (size_t i = 0; i < map->keys->len; i++) {
        if (map->compare(dynarr_bytes_at(map->keys, i), key) == 0) {
            return dynarr_bytes_at(map->values, i);
        }
    }

    return NULL;
}

void map_remove(Map *map, const void *key) {
    for (size_t i = 0; i < map->keys->len; i++) {
        if (map->compare(dynarr_bytes_at(map->keys, i), key) == 0) {
            dynarr_unsorted_remove(map->keys, i);
            dynarr_unsorted_remove(map->values, i);
        }
    }
}

void free_map(Map *map) {
    assert(map != NULL);
    if (map->keys) {
        free_dynarr(map->keys);
    }

    if (map->values) {
        free_dynarr(map->values);
    }

    free(map);
}
