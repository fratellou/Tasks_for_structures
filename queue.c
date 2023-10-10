#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"

void queue(char *db_file, char **query) {
  char **line = malloc(
      MAX_LEN * sizeof(char *)); //Строка в файле, содержащая записи структуры
  int flag = 0;
  int size = 0;
  Queue queue = {NULL, NULL, 0};
  STRUCT(line, db_file, flag, query[1], size);
  if (flag) {
    for (int i = 1; i < size; i++) {
      QPUSH(&queue, line[i]);
    }
  }
  queue_commands(query, &queue);
  write_queue(db_file, &queue, query[1], &flag);

  for (int i = 0; i <= queue.size; i++) {
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
  struct Node_que *node = malloc(sizeof(Node_que));
  node->data = element;
  if (queue->head == NULL) {
    queue->head = node;
    queue->tail = node;
  } else {
    queue->tail->next = node;
    queue->tail = node;
  }
  queue->size++;
}

char *QPOP(Queue *queue) {
  if (queue->head == NULL) {
    return NULL;
  } else {
    char *val = queue->head->data;
    queue->head = queue->head->next;
    queue->size--;
    return val;
  }
}

void write_queue(char *filename, Queue *queue, char *struct_name, int *flag) {
  FILE *temp = fopen("temp.txt", "w+");
  FILE *fp = fopen(filename, "r");
  if (fp && temp) {
    char *string = malloc(MAX_LEN * sizeof(char));
    while (fgets(string, MAX_LEN, fp) != NULL) {
      if ((strncmp(string, struct_name, strlen(struct_name)) == 0) ||
          *flag == 0) {
        fprintf(temp, "%s ", struct_name);
        for (int i = 0; i < queue->size; i++) {
          fprintf(temp, "%s ", queue->head->data);
          queue->head = queue->head->next;
        }
        fprintf(temp, "\n");
        if (*flag == 0) {
          fprintf(temp, "%s", string);
          *flag = 1;
        }
      } else {
        fprintf(temp, "%s", string);
      }
    }
    free(string);
    remove(struct_name);
    rename("temp.txt", filename);
  } else {
    ERROR;
  }
  fclose(fp);
  fclose(temp);
}
