#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"

void stack(char *db_file, char **query) {
  char **line = malloc(
      MAX_LEN * sizeof(char *)); //Строка в файле, содержащая записи структуры
  int isnt_empty = 0;
  int size = 0;
  Stack stack = {NULL, 0};
  STRUCT(line, db_file, isnt_empty, query[1], size, "stack:");
  if (isnt_empty) {
    for (int i = size - 1; i > 0; i--) {
      SPUSH(&stack, line[i]);
      printf("%s\n", line[i]);
    }
  }
  stack_commands(query, &stack);
  write_stack(db_file, &stack, query[1], &isnt_empty, "stack:");

  for (int i = 0; i <= stack.size; i++) {
    free(line[i]);
  }
  free(line);
}

void stack_commands(char **query, Stack *stack) {
  if (!strcmp(query[0], "SPUSH")) {
    SPUSH(stack, query[2]);
    printf("-> %s\n", query[2]);
  } else if (!strcmp(query[0], "SPOP")) {
    printf("-> %s\n", SPOP(stack));
  } else
    ERROR;
}

void SPUSH(Stack *stack, char *element) {
  Node *node = malloc(sizeof(Node));
  node->data = element;
  if (stack->head == NULL) {
    stack->head = node;
  } else {
    node->next = stack->head;
    stack->head = node;
  }
  stack->size++;
}

char *SPOP(Stack *stack) {
  if (stack->head == NULL) {
    return NULL;
  } else {
    char *element = stack->head->data;
    stack->head = stack->head->next;
    stack->size--;
    return element;
  }
}

void write_stack(char *filename, Stack *stack, char *struct_name, int *isnt_empty, char *struct_type) { 
  FILE *temp = fopen("temp.txt", "a+"); 
  FILE *fp = fopen(filename, "r"); 
  if (fp && temp) { 
    char string[MAX_LEN]; 
    while (fgets(string, MAX_LEN, fp) != NULL) { 
      char *istr = strtok(string, " "); 
      char *second_word = strtok(NULL, " "); 
      if (((strcmp(istr, struct_type) == 0) && (strcmp(second_word, struct_name) == 0))  || *isnt_empty == 0) {
          fprintf(temp, "%s %s ", struct_type, struct_name);
          Node *current = stack->head; 
          for (int i = 0; i < stack->size; i++) { 
            fprintf(temp, "%s ", current->data);
            current = current->next; 
            } 
            fprintf(temp, "\n"); 
            
            if (*isnt_empty == 0) { 
              fprintf(temp, "%s", string); 
              *isnt_empty = 1; } 
          } else {
             fprintf(temp, "%s", string); 
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