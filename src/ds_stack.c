#include <stdlib.h>
#include "ds_stack.h"

ds_stack *ds_stack_create(ds_destructor destroy){
  ds_stack* stack = malloc(sizeof(ds_stack));
  if (!stack) return NULL;
  stack->top = NULL;
  stack->size = 0;
  stack->destroy = destroy;
  return stack;
}

void ds_stack_destroy(ds_stack *stack) {
  //clear data
  while (stack->top){
    ds_stack_node *tmp = stack->top;
    if (stack->destroy) stack->destroy(tmp->data);

    stack->top = tmp->next;
    free(tmp);
  }
  free(stack);
}

ds_status ds_stack_push(ds_stack *stack, void *data) {
  if (!stack)return DS_ERR_BAD_ARG;
  ds_stack_node* node = malloc(sizeof(ds_stack_node));
  if (!node)return DS_ERR_ALLOC;
  node->data=data;
  node->next = stack->top;
  stack->top = node;
  stack->size++;
  return DS_OK;
}

//pop top element off stack
ds_status ds_stack_pop(ds_stack *stack, void **out) {
  if (!stack || !out) return DS_ERR_BAD_ARG;
  if (!stack->top) return  DS_ERR_EMPTY;
  ds_stack_node* node = stack->top;
  *out = node->data;
  stack->top = node->next;
  free(node); //leaving data intact
  return DS_OK;
}

//"peep" at first top node in stack
ds_status ds_stack_peek(ds_stack *stack, void **out) {
  if (!stack || !out) return DS_ERR_BAD_ARG;
  if (!stack->top) return  DS_ERR_EMPTY;
  *out = stack->top->data;
  return DS_OK;
}

size_t ds_stack_size(const ds_stack *stack) {
  if (stack) return stack->size;
  return 0;
}
bool ds_stack_is_empty(const ds_stack *stack) {
  if (!stack || stack->size == 0) return 1;
  else return 0;
}
