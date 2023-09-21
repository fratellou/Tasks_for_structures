#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void QPUSH(Queue *queue, char *element) {
    // Увеличение заднего указателя очереди и добавление элемента
    queue->rear++;
    if (queue->rear >= queue->capacity) {
        queue->capacity *= 2;  // Увеличение размера очереди в случае нехватки места
        queue->elements = realloc(queue->elements, queue->capacity * sizeof(char *));
    }
    queue->elements[queue->rear] = strdup(element);
}

// Функция для удаления и получения элемента из начала очереди
char *QPOP(Queue *queue) {
    if (queue->front > queue->rear) {
        return NULL;  // Очередь пустая
    }

    char *element = queue->elements[queue->front];
    queue->front++;
    return element;
}

// Функция для чтения элемента из начала очереди без его удаления
char *QPEEK(Queue *queue) {
    if (queue->front > queue->rear) {
        return NULL;  // Очередь пустая
    }

    return queue->elements[queue->front];
}