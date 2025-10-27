#pragma once
#include "ds_common.h"

//basic Typedefs and function decs
typedef struct ds_queue_node {
    void *data;
    struct ds_queue_node *next;
} ds_queue_node;

typedef struct {
    ds_queue_node *front;
    ds_queue_node *rear;
    size_t size;
    ds_destructor destroy;
} ds_queue;

ds_queue *ds_queue_create(ds_destructor destroy);
void ds_queue_destroy(ds_queue *queue);
ds_status ds_queue_enqueue(ds_queue *queue, void *data);
ds_status ds_queue_dequeue(ds_queue *queue, void **out);
ds_status ds_queue_peek(const ds_queue *queue, void **out);
size_t ds_queue_size(const ds_queue *queue);
bool ds_queue_is_empty(const ds_queue *queue);
