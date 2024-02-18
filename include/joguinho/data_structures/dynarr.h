#ifndef KASOUZA_JOGUINHO_INCLUDE_JOGUINHO_DATA_STRUCTURES_INCLUDE_JOGUINHO_DATA_STRUCTURES_ARRAY_H
#define KASOUZA_JOGUINHO_INCLUDE_JOGUINHO_DATA_STRUCTURES_INCLUDE_JOGUINHO_DATA_STRUCTURES_ARRAY_H

#include <stddef.h>

#define DYNARR_INITIAL_CAP 8

typedef struct {
    size_t len;
    size_t cap;
    size_t stride;
    char *dat;
} DynArr;

#define create_dynarr(type) _create_dynarr(sizeof(type), DYNARR_INITIAL_CAP)
DynArr *_create_dynarr(size_t stride, size_t cap);

#define dynarr_buffer(dynarr, type) ((type *)dynarr)

#define dynarr_at(dynarr, type, idx) (dynarr_buffer(dynarr, type)[idx])
#define dynarr_set(dynarr, type, idx, item)                                    \
    (dynarr_buffer(dynarr, type)[idx] = item)

void dynarr_resize(DynArr *dynarr, size_t new_cap);

#define dynarr_push_literal(dynarr, type, item)                                \
    do {                                                                       \
        type __DYNARR_TEMP_ITEM__ = item;                                      \
        dynarr_push(dynarr, &__DYNARR_TEMP_ITEM__);                            \
    } while (false)

void dynarr_push(DynArr *dynarr, void *item);

void free_dynarr(DynArr *dynarr);

#endif
