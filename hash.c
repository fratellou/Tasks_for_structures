#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"

void hash(char *db_file, char **query) {

  char **line = malloc(
      MAX_LEN * sizeof(char *)); //Строка в файле, содержащая записи структуры
  int isnt_empty = 0;
  int size = 0;
  HashTable *hashtable = createHashTable(MAX_LEN);
  STRUCT(line, db_file, isnt_empty, query[1], size, "hash:");
  if (isnt_empty) {
    for (int i = 0; i < size; i++) {
      char new_string[MAX_LEN];
      strcpy(new_string, line[i]);
      char *first_key = strtok(line[i], ",");
      char *second_val = strtok(NULL, ",");
      HSET(hashtable, first_key, second_val);
    }
  }
  hash_commands(query, hashtable);
  write_hash(db_file, hashtable, query[1], "hash:");
}

void hash_commands(char **query, HashTable *hash) {
  if (!strcmp(query[0], "HSET")) {
    HSET(hash, query[2], query[3]);
    printf("-> %s\n", query[3]);
  } else if (!strcmp(query[0], "HDEL")) {
    char *value = HDEL(hash, query[2]);
    printf("-> %s\n", value);
  } else if (!strcmp(query[0], "HGET")) {
    char *value = HGET(hash, query[2]);
    printf("-> %s\n", value);
  } else {
    ERROR;
  }
}

HashTable *createHashTable(int size) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  ht->size = size;
  ht->table = malloc(sizeof(Node_hash **) * size);
  for (int i = 0; i < size; i++) {
    ht->table[i] = NULL;
  }
  return ht;
}

int hash_calc(char *key) {
  int hash = 0;
  for (int i = 0; i < (int)strlen(key); i++) {
    hash += (int)key[i];
  }
  return hash % MAX_LEN;
}

void HSET(HashTable *hashtable, char *key, char *value) {
  int index = hash_calc(key);
  if (hashtable->table[index] != NULL &&
      strcmp(hashtable->table[index]->key, key) != 0) {
    ERROR;
    return;
  }
  Node_hash *newNode = (Node_hash *)malloc(sizeof(Node_hash));
  newNode->key = key;
  newNode->element = value;
  newNode->next = NULL;
  if (hashtable->table[index] == NULL) {
    hashtable->table[index] = newNode;
    hashtable->table[index]->head = newNode;
  } else {
    newNode->next = hashtable->table[index]->head;
    hashtable->table[index]->head = newNode;
  }
}

char *HDEL(HashTable *hashtable, char *key) {
  int index = hash_calc(key);
  if (hashtable->table[index] == NULL ||
      hashtable->table[index]->head == NULL) {
    return NULL;
  } else {
    Node_hash *current = hashtable->table[index]->head;
    if (strcmp(current->key, key) == 0) {
      char *element = current->element;
      hashtable->table[index]->head = NULL;
      return element;
    }
    Node_hash *prev = hashtable->table[index]->head;
    while (current != NULL) {
      if (strcmp(current->key, key) == 0) {
        char *element = current->element;
        if (prev->next != NULL)
          prev->next = current->next;
        return element;
      }
      prev = current;
      current = current->next;
    }
  }
  return NULL;
}

char *HGET(HashTable *hashtable, char *key) {
  int index = hash_calc(key);
  Node_hash *current = hashtable->table[index];
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return current->element;
    }
    current = current->next;
  }
  return NULL;
}

void hash_free(HashTable *hashtable) {
  for (int i = 0; i < MAX_LEN; i++) {
    if (hashtable->table[i] == NULL)
      continue;
    else {
      while (hashtable->table[i]->head != NULL) {
        Node_hash *temp = hashtable->table[i]->head;
        hashtable->table[i]->head = hashtable->table[i]->head->next;
        free(temp->key);
        free(temp->element);
        free(temp);
      }
    }
    free(hashtable->table[i]);
  }
  free(hashtable->table);
  free(hashtable);
}

void write_hash(char *filename, HashTable *hashtable, char *struct_name,
                char *struct_type) {
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
        for (int i = 0; i < MAX_LEN; i++) {
          if (hashtable->table[i] == NULL)
            continue;
          Node_hash *current = hashtable->table[i]->head;
          if (current->element == NULL || current->key == NULL)
            continue;
          while (current != NULL) {
            fprintf(temp, "%s,%s ", current->key, current->element);
            current = current->next;
          }
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
