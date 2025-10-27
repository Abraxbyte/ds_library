#include <assert.h>
#include <stdio.h>
#include "../include/ds_queue.h"

static void test_queue_basic() {
    ds_queue *q = ds_queue_create(NULL);
    assert(q);
    assert(ds_queue_is_empty(q));

    int a = 1, b = 2, c = 3;
    assert(ds_queue_enqueue(q, &a) == DS_OK);
    assert(ds_queue_enqueue(q, &b) == DS_OK);
    assert(ds_queue_enqueue(q, &c) == DS_OK);
    assert(ds_queue_size(q) == 3);

    int *p = NULL;
    assert(ds_queue_peek(q, (void **)&p) == DS_OK && *p == 1);
    assert(ds_queue_dequeue(q, (void **)&p) == DS_OK && *p == 1);
    assert(ds_queue_dequeue(q, (void **)&p) == DS_OK && *p == 2);
    assert(ds_queue_dequeue(q, (void **)&p) == DS_OK && *p == 3);
    assert(ds_queue_dequeue(q, (void **)&p) == DS_ERR_EMPTY);

    ds_queue_destroy(q);
    printf("test_queue_basic passed\n");
}

int main(void) {
    test_queue_basic();
    return 0;
}

