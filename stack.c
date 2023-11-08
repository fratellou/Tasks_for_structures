#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function pushes an element onto the stack
void SPUSH(Stack *stack, char *element) {
  Node *node = malloc(sizeof(Node));
  node->data = strdup(element);
  if (stack->head == NULL) {
    stack->head = node;
  } else {
    node->next = stack->head;
    stack->head = node;
  }
  stack->size++;
}

// This function pops an element from the stack
void SPOP(Stack *stack) {
  if (stack->head == NULL) {
  } else {
    stack->head = stack->head->next;
    stack->size--;
  }
}
