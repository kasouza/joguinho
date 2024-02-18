#include "joguinho/data_structures/dynarr.h"
#include "joguinho/utils.h"

#include <assert.h>
#include <malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

DynArr *_create_dynarr(size_t stride, size_t cap) {
    assert(stride > 0);
    assert(cap > 0);

    DynArr *dynarr = malloc(sizeof(DynArr));
    if (!dynarr) {
        return NULL;
    }

    dynarr->dat = malloc(stride * cap);
    if (!dynarr->dat) {
        free(dynarr);
        return NULL;
    }

    dynarr->cap = cap;
    dynarr->len = 0;
    dynarr->stride = stride;

    return dynarr;
}

void dynarr_resize(DynArr *dynarr, size_t new_cap) {
    assert(dynarr != NULL);
    assert(new_cap > 0);

    void *new_dat = malloc(dynarr->stride * new_cap);

    size_t n_to_copy = MIN(dynarr->len, new_cap);
    memcpy(new_dat, dynarr->dat, dynarr->stride * n_to_copy);

    free(dynarr->dat);
    dynarr->dat = new_dat;
    dynarr->cap = new_cap;
}

void dynarr_push(DynArr *dynarr, void *item) {
    assert(dynarr != NULL);
    assert(item != NULL);

    if (dynarr->len >= dynarr->cap) {
        dynarr_resize(dynarr, dynarr->cap * 2);
    }

    size_t idx = dynarr->len;
    dynarr->len++;

    dynarr_set(dynarr, idx, item);
}

void dynarr_set(DynArr *dynarr, size_t idx, void *item) {
    assert(dynarr != NULL);
    assert(dynarr->dat != NULL);
    assert(idx < dynarr->len);

    char *data = item;
    for (size_t j = 0; j < dynarr->stride; j++) {
        dynarr->dat[idx * dynarr->stride + j] = data[j];
    }
}

void dynarr_remove(DynArr *dynarr, size_t idx) {
    for (size_t i = idx; i < dynarr->len - 1; i++) {
        for (size_t j = 0; j < dynarr->stride; j++) {
            dynarr->dat[i * dynarr->stride + j] =
                dynarr->dat[(i + 1) * dynarr->stride + j];
        }
    }

    dynarr->len--;
}

void dynarr_unsorted_remove(DynArr *dynarr, size_t idx) {
    for (size_t j = 0; j < dynarr->stride; j++) {
        dynarr->dat[idx * dynarr->stride + j] =
            dynarr->dat[(dynarr->len - 1) * dynarr->stride + j];
    }

    dynarr->len--;
}

void free_dynarr(DynArr *dynarr) {
    assert(dynarr->dat != NULL);
    assert(dynarr != NULL);

    free(dynarr->dat);
    free(dynarr);
}
