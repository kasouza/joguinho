#ifndef KASOUZA_JOGUINHO_INCLUDE_JOGUINHO_INCLUDE_JOGUINHO_UTILS_H
#define KASOUZA_JOGUINHO_INCLUDE_JOGUINHO_INCLUDE_JOGUINHO_UTILS_H

#include <stddef.h>

#define LOG(...) fprintf(stderr, __VA_ARGS__)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(n, min, max) (MIN(MAX(n, min), max))
#define TO_INDEX(x, y, width) ((x) + (y) * (width))

char *read_file(const char *path);

#endif
