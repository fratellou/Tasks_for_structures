#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue {
    char **elements;
    int front;
    int rear;
    int capacity;
} Queue;

void QPUSH(Queue *queue, char *element);
char *QPOP(Queue *queue);
char *QPEEK(Queue *queue);

#endif