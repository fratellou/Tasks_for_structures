#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node_que {
  int data;
  struct Node_que *next;
} Node_que;

typedef struct Queue {
  Node_que *head;
  Node_que *tail;
  int size;
} Queue;

void QPUSH(Queue *queue, int element);
void QPOP(Queue *queue);
void freeQueue(Queue *queue);

#endif