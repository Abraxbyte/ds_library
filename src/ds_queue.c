#include <stdlib.h>
#include "ds_queue.h"

ds_queue *ds_queue_create(ds_destructor destroy) {
  ds_queue* q = malloc(sizeof(ds_queue));
  if(!q) return NULL; //chheck if alloc error
  q->front = NULL; 
  q->rear = NULL; 
  q->size = 0; 
  q->destroy =  destroy;
  return q;
}

void ds_queue_destroy(ds_queue *q) {
  ds_queue_node* current = q->front;
  while(current){
    ds_queue_node *next = current->next;
    if (q->destroy) q->destroy(current->data);
    free(current);
    current = next;
  }
  free(q);
}

ds_status ds_queue_enqueue(ds_queue *q, void *data) {
  if(!q)  return DS_ERR_BAD_ARG; 
  ds_queue_node *node = malloc(sizeof(ds_queue_node)); 
  if (!node) return DS_ERR_ALLOC; 
  node->data = data;
  node->next = NULL;
  if (!q->rear) q->front = q->rear = node;
  else{
    q->rear->next = node;
    q->rear = node;
  }
  q->size++;
  return DS_OK;
}
ds_status ds_queue_dequeue(ds_queue *q, void **out) {
  if(!q || !out)  return DS_ERR_BAD_ARG; 
  if (!q->front) return DS_ERR_EMPTY;
  ds_queue_node* node = q->front;
  if (node->next) q->front = node->next;
  else {
    q->front = NULL;
    q->rear = NULL;
  }
  *out = node->data;
  q->size--;
  free(node);
  return DS_OK;
}
ds_status ds_queue_peek(const ds_queue *q, void **out) {
  if(!q || !out)  return DS_ERR_BAD_ARG; 
  if (!q->front) return DS_ERR_EMPTY;
  *out = q->front->data;
  return DS_OK;
}

size_t ds_queue_size(const ds_queue *q) {
  if (!q || q->size==0) return 0;
  else return q->size;
}

bool ds_queue_is_empty(const ds_queue *q) {
    return !q || q->size == 0;
}
