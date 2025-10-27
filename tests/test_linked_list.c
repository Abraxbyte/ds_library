#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "ds_linked_list.h"

static void int_free(void *p){ free(p); }
static int  int_cmp(const void *a, const void *b){
    int ia = *(const int*)a, ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

int main(void){
    ds_list *l = ds_list_create(int_free);
    assert(l);

    // push_back 1..3
    for (int i=1;i<=3;i++){
        int *p = malloc(sizeof(int));
        *p = i;
        assert(ds_list_push_back(l, p) == DS_OK);
    }
    assert(ds_list_size(l) == 3);

    // front/back
    assert(*(int*)ds_list_front(l) == 1);
    assert(*(int*)ds_list_back(l)  == 3);

    // pop_front -> 1
    void *out = NULL;
    assert(ds_list_pop_front(l, &out) == DS_OK);
    assert(*(int*)out == 1); free(out);
    assert(ds_list_size(l) == 2);

    // find 3
    int key3 = 3;
    int *found = ds_list_find(l, int_cmp, &key3);
    assert(found && *found == 3);

    // remove_if 3
    size_t removed = 0;
    assert(ds_list_remove_if(l, int_cmp, &key3, &removed) == DS_OK);
    assert(removed == 1);
    assert(ds_list_size(l) == 1);

    // pop_back remaining (2) with auto-destroy
    assert(ds_list_pop_back(l, NULL) == DS_OK);
    assert(ds_list_is_empty(l));

    ds_list_destroy(l);
    puts("linked_list tests passed");
    return 0;
}
