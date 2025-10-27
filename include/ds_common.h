//Shared types and macros for all modules 
#pragma once
#include <stddef.h> //more minimal stdlib, inlcludes NULL and size_t
#include <stdbool.h>
typedef void (*ds_destructor)(void *p);
typedef int  (*ds_compare)(const void *a, const void *b);
typedef void (*ds_foreach_fn)(void *data, void *ctx);

typedef enum {
    DS_OK = 0,
    DS_ERR_ALLOC = -1,
    DS_ERR_EMPTY = -2,
    DS_ERR_NOT_FOUND = -3,
    DS_ERR_BAD_ARG = -4
} ds_status;
