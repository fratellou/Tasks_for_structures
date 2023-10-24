#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"

void set(char *db_file, char **query) {
  char **line = malloc(
      MAX_LEN * sizeof(char *)); // Строка в файле, содержащая записи структуры
  int size = 0;
  int isnt_empty = 0;
  STRUCT(line, db_file, isnt_empty, query[1], size, "set:");
  Set set;
  set.size = MAX_LEN;
  set.buckets = malloc(MAX_LEN * sizeof(Node_set *)); 
  if (isnt_empty) {
    for (int i = 1; i < size; i++) {
      SADD(&set, line[i]);
    }
  }
  set_commands(query, &set);
  write_set(db_file, &set, query[1], "set:");
  freeSet(&set);
}

void set_commands(char **query, Set *set) {
  if (!strcmp(query[0], "SADD")) {
    SADD(set, query[2]);
    printf("-> %s\n", query[2]);
  } else if (!strcmp(query[0], "SREM")) {
    SREM(set, query[2]);
    printf("-> %s\n", query[2]);
  } else if (!strcmp(query[0], "SISMEMBER")) {
    if (!SISMEMBER(set, query[2]))
      printf("\n-> FALSE");
    else
      printf("\n-> TRUE");
  } else {
    ERROR;
  }
}

int set_calc(char* element, int size) {
  int sum = 0;
  int i = 0;
  while (element[i] != '\0') {
    sum += element[i];
    i++;
  }
  return sum % size;
}

void SADD(Set *set, char *element) {
  int index = set_calc(element, set->size);
  Node_set *newNode = (Node_set *)malloc(sizeof(Node_set));
  newNode->element = strdup(element); 
  newNode->next = set->buckets[index];
  set->buckets[index] = newNode;
}

void SREM(Set *set, char *element) {
  int index = set_calc(element, set->size);
  Node_set *prev = NULL;
  Node_set *curr = set->buckets[index];
  while (curr != NULL) {
    if (strcmp(curr->element, element) == 0) {
      if (prev == NULL) {
        set->buckets[index] = curr->next;
      } else {
        prev->next = curr->next;
      }

      free(curr->element); 
      free(curr);
      return;
    }
    prev = curr;
    curr = curr->next;
  }
}

int SISMEMBER(Set *set, char *element) {
  int index = set_calc(element, set->size);
  Node_set *curr = set->buckets[index];
  while (curr != NULL) {
    if (strcmp(curr->element, element) == 0) {
      return 1;
    }
    curr = curr->next;
  }
  return 0;
}

void freeSet(Set *set) {
  for (int i = 0; i < set->size; i++) {
    Node_set *curr = set->buckets[i];
    while (curr != NULL) {
      Node_set *temp = curr;
      curr = curr->next;
      free(temp->element);
      free(temp);
    }
  }
  free(set->buckets);
}

void write_set(char *filename, Set *set, char *struct_name, char *struct_type) {
  FILE *temp = fopen("temp.txt", "a+");
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
        Node_set *current = set->buckets[0];
        while (current != NULL) {
          fprintf(temp, "%s ", current->element);
          current = current->next;
        }
        fprintf(temp, "\n");
        new_input = 1;
      }
      if ((strcmp(istr, struct_type) == 0) && (strcmp(second_word, struct_name) == 0)) {
        continue;
      }
      else {
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