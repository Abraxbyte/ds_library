#include <stdlib.h>
#include "ds_linked_list.h"

//basic node, any data
typedef struct node {
  void *data; 
  struct node *next;
  struct node *prev;
}node;

//list structure: stores basic info and destructor
struct ds_list{
  node *head;
  node *tail;
  ds_destructor dtor;
  size_t size;
};

//Create new node, init with values
static node* make_node(void *data){
  node *n = (node*)malloc(sizeof(*n));
  if (n== NULL) return NULL;
  n->data = data;
  n->prev = n->next = NULL;
  return n;
}

//create new list, returns pointer to list
ds_list* ds_list_create(ds_destructor dtor){
  ds_list *list = (ds_list*)calloc(1, sizeof(*list));
  if (list == NULL) return NULL;
  list->dtor = dtor;
  return list;
}

//clears a list of all entris (from head to tail)
void ds_list_clear(ds_list *list){
  if(list == NULL) return; //check if list exists
  node *current = list->head; 
  while (current) {
    node *next = current->next;
    list->dtor(current->data); //remove data with destructor
    free(current); //remove node
    current = next;//go to next node
  }
  //also clean list struct
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

void ds_list_destroy(ds_list *list){
  if(list== NULL) return;
  ds_list_clear(list);
  free(list);
}

size_t ds_list_size(const ds_list *list){
  return list ? list->size : 0;
}
//maybe unnecceary
bool ds_list_is_empty(const ds_list *list){
  return !list || list->size == 0;
}

// Return data of first node NULL if emptyA
void* ds_list_front(const ds_list *list){
  return (list && list->head) ? list->head->data : NULL;
} 

void* ds_list_back(const ds_list *list){
  return (list && list->tail) ? list->tail->data : NULL;
}

//insert new node at front
ds_status  ds_list_push_front(ds_list *list, void *data){
  if(!list) return DS_ERR_BAD_ARG; // no list passed
  node* new_node = make_node(data);
  if(!new_node) return DS_ERR_ALLOC; //check allocation worked
  new_node->next = list->head;
  if (list->head) list->head->prev = new_node;
  else list->tail = new_node;
  list->head = new_node;
  if (list->tail == NULL) list->tail = new_node;
  list->size++ ;
  return DS_OK; 
}

ds_status  ds_list_push_back(ds_list *list, void *data){
  if(!list) return DS_ERR_BAD_ARG; // no list passed
  node* new_node = make_node(data);
  if(!new_node) return DS_ERR_ALLOC; //check allocation worked
  new_node->prev = list->tail;

  if (list->tail) list->tail->next = new_node;
  else list->head = new_node;
  list->tail = new_node;
  list->size++ ;
  return DS_OK; 
}

static ds_status ds_pop_common(ds_list *list, bool front, void **out){
  if(!list) return DS_ERR_BAD_ARG; //
  if(!list->head) return DS_ERR_EMPTY;
  node *del_node = front ? list->head : list->tail;
  if (front) {
    list->head = del_node->next;
    if (list->head) list->head->prev = NULL;
    else list->tail = NULL;
  } else {
    list->tail = del_node->prev;
    if (list->tail) list->tail->next = NULL;
    else list->head = NULL;
  }

  if (out) *out = del_node->data;
  else if (list->dtor) list->dtor(del_node->data);
  else free(del_node->data);
  free(del_node);
  list->size--;
  return DS_OK;
}

ds_status  ds_list_pop_front(ds_list *list, void **out){ 
  return ds_pop_common(list,1, out);
}
ds_status  ds_list_pop_back(ds_list *list, void **out){
  return ds_pop_common(list,0, out);
}
//
//return pointer to data matching key
void* ds_list_find(const ds_list *list, ds_compare cmp, const void *key){
  if (!list || !cmp) return NULL;
    for (node *n = list->head; n; n = n->next) {
        if (cmp(n->data, key) == 0) return n->data;
    }
    return NULL;
}

//remove all nodes that match
ds_status ds_list_remove_if(ds_list *list, ds_compare cmp, const void *key, size_t *removed) {
    if (!list || !cmp) return DS_ERR_BAD_ARG;
    size_t count = 0;
    node *n = list->head;
    while (n) {
        node *nx = n->next;
        if (cmp(n->data, key) == 0) {
            if (n->prev) n->prev->next = n->next; else list->head = n->next;
            if (n->next) n->next->prev = n->prev; else list->tail = n->prev;
            if (list->dtor) list->dtor(n->data);
            free(n);
            list->size--; count++;
        }
        n = nx;
    }
    if (removed) *removed = count;
    return count ? DS_OK : DS_ERR_NOT_FOUND;
}
