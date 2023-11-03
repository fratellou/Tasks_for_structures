#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"

void queue(char *db_file, char **query) {
  char **line = malloc(
      MAX_LEN * sizeof(char *)); 
  int isnt_empty = 0;
  int size = 0;
  Queue queue = {NULL, NULL, 0};
  STRUCT(line, db_file, isnt_empty, query[1], size, "queue:");
  if (isnt_empty) {
    for (int i = 1; i < size; i++) {
      QPUSH(&queue, line[i]);
    }
  }
  queue_commands(query, &queue);
  write_queue(db_file, &queue, query[1], "queue:");
  for (int i = 0; i < queue.size; i++) {
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
  Node_que *node = malloc(sizeof(Node_que));
  node->data = strdup(element);
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

void write_queue(char *filename, Queue *queue, char *struct_name,
                 char *struct_type) {
  FILE *temp = fopen("temp.txt", "w+");
  FILE *fp = fopen(filename, "r");
  if (fp && temp) {
    char string[MAX_LEN];
    int new_input = 0;
    while (fgets(string, MAX_LEN, fp) != NULL) {
      char new_string[MAX_LEN];
      strcpy(new_string, string);
      char *istr = strtok(string, " ");
      char *second_word = strtok(NULL, " ");
      if (new_input == 0) {
        fprintf(temp, "%s %s ", struct_type, struct_name);
        for (int i = 0; i < queue->size; i++) {
          fprintf(temp, "%s ", queue->head->data);
          Node_que *temp_node = queue->head;
          queue->head = queue->head->next;
          free(temp_node->data);
        }
        fprintf(temp, "\n");
        new_input = 1;
      }
      if ((strcmp(istr, struct_type) == 0) &&
          (strcmp(second_word, struct_name) == 0)) {
        continue;
      } else {
        fprintf(temp, "%s", new_string);
      }
    }
    remove(filename);
    rename("temp.txt", filename);
  } else {
    ERROR;
  }
  fclose(fp);
  fclose(temp);
}
