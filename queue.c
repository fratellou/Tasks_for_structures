#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"

void queue(char *db_file, char **query) {
    char **line = malloc(MAX_LEN * sizeof(char *));  //Строка в файле, содержащая записи структуры
    int size = 0;
    int flag = 0;
    STRUCT(line, db_file, flag, query[1], size);
    Queue queue;
    queue.elements = NULL;
    queue.front = 0;
    queue.size = 0;
    queue.elements = malloc(MAX_LEN * sizeof(char *));
    if (flag) {
        for (int i = 1; i < size; i++) {
            QPUSH(&queue, line[i]);
        }
    }
    queue_commands(query, &queue);
    for (int j = 0; j <= MAX_LEN; j++) {
        printf("%s\t", queue.elements[j]);
    }
    SAVE(db_file, queue, queue.size - 1, query[1], flag);
    for (int i = 0; i <= size; i++) {
        free(line[i]);
    }
    free(line);
}

void queue_commands(char **query, Queue *queue) {
    if (!strcmp(query[0], "QPUSH")) {
        QPUSH(queue, query[2]);
        printf("-> %s\n", query[2]);
    } else if (!strcmp(query[0], "QPOP")) {
        printf("-> %s\n", QPOP(queue));
    } else
        ERROR;
}

void QPUSH(Queue *queue, char *element) {
    if (queue->size < MAX_LEN) {
        queue->elements[(queue->front + queue->size) % MAX_LEN] = element;
        queue->size++;
    } else
        ERROR;
}

char *QPOP(Queue *queue) {
    if (queue->size > 0) {
        char *element = queue->elements[queue->front];
        queue->front = ((queue->front) + 1) % MAX_LEN;
        queue->size--;
        return element;
    }
    return NULL;
}
