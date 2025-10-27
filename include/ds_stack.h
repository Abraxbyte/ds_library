#pragma once
#include "ds_common.h"

typedef struct ds_stack_node {
    void *data;
    struct ds_stack_node *next;
} ds_stack_node;

typedef struct {
    ds_stack_node *top;
    size_t size;
    ds_destructor destroy;
} ds_stack;


ds_stack *ds_stack_create(ds_destructor destroy);
void ds_stack_destroy(ds_stack *stack);

ds_status ds_stack_push(ds_stack *stack, void *data);
ds_status ds_stack_pop(ds_stack *stack, void **out);
ds_status ds_stack_peek(ds_stack *stack, void **out);

size_t ds_stack_size(const ds_stack *stack);
bool ds_stack_is_empty(const ds_stack *stack);
