#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue {
    char **elements;
    int front;
    int size;
} Queue;

void queue(char *db_file, char **query);
void queue_commands(char **query, Queue *queue);
void QPUSH(Queue *queue, char *element);
char *QPOP(Queue *queue);

#endif