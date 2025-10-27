#pragma once
#include "ds_common.h"


typedef struct ds_list ds_list;

ds_list*   ds_list_create(ds_destructor dtor);       // allow dtor be NULL
void       ds_list_destroy(ds_list *list);

size_t     ds_list_size(const ds_list *list);
bool       ds_list_is_empty(const ds_list *list);

void*      ds_list_front(const ds_list *list);       // NULL if empty
void*      ds_list_back(const ds_list *list);

ds_status  ds_list_push_front(ds_list *list, void *data);
ds_status  ds_list_push_back(ds_list *list, void *data);

ds_status  ds_list_pop_front(ds_list *list, void **out); // out may be NULL to auto-destroy via dtor
ds_status  ds_list_pop_back(ds_list *list, void **out);

void       ds_list_clear(ds_list *list);

void*      ds_list_find(const ds_list *list, ds_compare cmp, const void *key);
ds_status  ds_list_remove_if(ds_list *list, ds_compare cmp, const void *key, size_t *removed);
