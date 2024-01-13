#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

// Push an element into the queue
void QPUSH(Queue *queue, int element) {
  Node_que *node = malloc(sizeof(Node_que));
  node->data = element;

  // If the queue is empty, set the new node as both head and tail
  if (queue->head == NULL) {
    queue->head = node;
    queue->tail = node;
  } else {
    queue->tail->next = node;
    queue->tail = node;
  }
  queue->size++;
}

// Pop an element from the queue
void QPOP(Queue *queue) {
  if (queue->head == NULL) {
    return;
  }

  Node_que *temp = queue->head;
  queue->head = queue->head->next;
  free(temp);
  queue->size--;

  if (queue->head == NULL) {
    queue->tail = NULL;
  }
}

// Free the memory allocated for the queue
void freeQueue(Queue *queue) {
  Node_que *current = queue->head;
  Node_que *next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }

  // Reset the queue properties
  queue->head = NULL;
  queue->tail = NULL;
  queue->size = 0;
}
