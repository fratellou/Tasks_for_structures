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

  Set *set = createSet(MAX_LEN);
  STRUCT(line, db_file, isnt_empty, query[1], size, "set:");
  if (isnt_empty) {
    for (int i = 1; i < size; i++) {
      SADD(set, line[i]);
    }
  }
  set_commands(query, set);
  // write_set(db_file, set, query[1], "set:");
}

void set_commands(char **query, Set *set) {
  if (!strcmp(query[0], "SADD")) {
    SADD(set, query[2]);
    printf("-> %s\n", query[2]);
  } else if (!strcmp(query[0], "SREM")) {
    char *value = SREM(set, query[2]);
    printf("-> %s\n", value);
  } else if (!strcmp(query[0], "SISMEMBER")) {
    if (!SISMEMBER(set, query[2]))
      printf("\n-> FALSE");
    else
      printf("\n-> TRUE");
  } else {
    ERROR;
  }
}

Set *createSet(int size) {
  Set *set = (Set *)malloc(sizeof(Set));
  set->size = size;
  set->buckets = malloc(sizeof(Node_set *) * size);
  for (int i = 0; i < size; i++) {
    set->buckets[i] = NULL;
  }
  return set;
}

void SADD(Set *set, char *element) {
  for (int i = 0; i < set->size; i++) {
    if (set->buckets[i] != NULL &&
        strcmp(set->buckets[i]->element, element) == 0) {
      ERROR;
      return;
    }
  }
  Node_set *newNode = (Node_set *)malloc(sizeof(Node_set));
  newNode->element = strdup(element);
  newNode->next = set->buckets[set->size];
  set->buckets[set->size] = newNode;
  set->size++;
}

char *SREM(Set *set, char *element) {
  int index;
  for (index = 0; index < set->size; index++) {
    if (set->buckets[index] != NULL &&
        strcmp(set->buckets[index]->element, element) == 0) {
      char *value = set->buckets[index]->element;
      if (index == 0) {
        set->buckets[index] = set->buckets[index]->next;
      } else {
        set->buckets[index - 1]->next = set->buckets[index]->next;
      }
      return value;
    }
  }
  return NULL;
}

int SISMEMBER(Set *set, char *element) {
  int index;
  for (index = 0; index < set->size; index++) {
    if (set->buckets[index] != NULL &&
        strcmp(set->buckets[index]->element, element) == 0) {
      return 1;
    }
  }
  return 0;
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
        for (int i = 0; i < set->size; i++) {
          if (set->buckets[i] != NULL && set->buckets[i]->element != NULL)
            fprintf(temp, "%s ", set->buckets[i]->element);
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