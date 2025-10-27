#include <assert.h>
#include <stdio.h>
#include "../include/ds_stack.h"

static void test_stack_basic() {
    ds_stack *s = ds_stack_create(NULL);
    assert(s);
    assert(ds_stack_is_empty(s));

    int a = 1, b = 2, c = 3;
    assert(ds_stack_push(s, &a) == DS_OK);
    assert(ds_stack_push(s, &b) == DS_OK);
    assert(ds_stack_push(s, &c) == DS_OK);
    assert(ds_stack_size(s) == 3);

    int *p = NULL;
    assert(ds_stack_peek(s, (void **)&p) == DS_OK && *p == 3);

    assert(ds_stack_pop(s, (void **)&p) == DS_OK && *p == 3);
    assert(ds_stack_pop(s, (void **)&p) == DS_OK && *p == 2);
    assert(ds_stack_pop(s, (void **)&p) == DS_OK && *p == 1);
    assert(ds_stack_pop(s, (void **)&p) == DS_ERR_EMPTY);

    ds_stack_destroy(s);
    printf("test_stack_basic passed\n");
}

int main(void) {
    test_stack_basic();
    return 0;
}

