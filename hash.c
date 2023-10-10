#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"

void hash(char *db_file, char **query) {

  char **line = malloc(
      MAX_LEN * sizeof(char *)); //Строка в файле, содержащая записи структуры
  int flag = 0;
  int size = 0;
  HashTable *hashtable = createHashTable(MAX_LEN);
  STRUCT(line, db_file, flag, query[1], size);
  if (flag) {
    for (int i = 1; i < size; i++) {
      char key[5];
      char *ptr = strtok(line[i], ",");
      strcpy(key, ptr);
      ptr = strtok(NULL, ",");
      HSET(hashtable, key, ptr);
    }
  }
  hash_commands(query, hashtable);
  write_hash(db_file, hashtable, query[1], &flag);

  for (int i = 0; i < MAX_LEN; i++) {
    Node_hash *temp = hashtable->table[i];
    while (temp != NULL) {
        if (temp->key != NULL && temp->value != NULL) {
                    Node_hash *prev = temp;
      temp = temp->next;
      free(prev);
            }

    }
  }
  
  free(hashtable->table);
  free(hashtable);
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
  ht->table = (Node_hash **)malloc(sizeof(Node_hash *) * size);
  for (int i = 0; i < size; i++) {
    ht->table[i] = NULL;
  }
  return ht;
}

Node_hash *createNode(char *key, char *value) {
  Node_hash *newNode = (Node_hash *)malloc(sizeof(Node_hash));
  newNode->key = key;
  newNode->value = value;
  newNode->next = NULL;
  return newNode;
}

int hash_calc(char *key) {
  int sum = 0;
  for (int i = 0; i < (int)strlen(key); i++) {
    sum += key[i];
  }
  return sum % MAX_LEN;
}

void HSET(HashTable *hashtable, char *key, char *value) {
  int index = hash_calc(key);
  Node_hash *temp = hashtable->table[index];
  while (temp != NULL) {
    if (strcmp(temp->key, key) == 0) {
      temp->value = value;
      return;
    }
    temp = temp->next;
  }
  Node_hash *newNode = createNode(key, value);
  newNode->next = hashtable->table[index];
  hashtable->table[index] = newNode;
}

char *HDEL(HashTable *hashtable, char *key) {
  int index = hash_calc(key);
  Node_hash *temp = hashtable->table[index];
  Node_hash *prev = NULL;
  while (temp != NULL) {
    if (strcmp(temp->key, key) == 0) {
      if (prev == NULL) {
        hashtable->table[index] = temp->next;
      } else {
        prev->next = temp->next;
      }
      return temp->value;
    }
    prev = temp;
    temp = temp->next;
  }
  return NULL;
}

char *HGET(HashTable *hashtable, char *key) {
  int index = hash_calc(key);
  Node_hash *temp = hashtable->table[index];
  while (temp != NULL) {
    if (strcmp(temp->key, key) == 0) {
      return temp->value;
    }
    temp = temp->next;
  }
  return NULL;
}

void write_hash(char *filename, HashTable *hashtable, char *struct_name, int *flag) {
  FILE *temp = fopen("temp.txt", "a+");
  FILE *fp = fopen(filename, "r");
  if (fp && temp) {
    char *string = malloc(MAX_LEN * sizeof(char));
    while (fgets(string, MAX_LEN, fp) != NULL) {
      if ((strncmp(string, struct_name, strlen(struct_name)) == 0) || *flag == 0) {
        fprintf(temp, "%s ", struct_name);

        for (int i = 0; i < hashtable->size; i++) {
          Node_hash *temp_hash = hashtable->table[i];
          while (temp_hash != NULL) {
            if (temp_hash->key != NULL && temp_hash->value != NULL) {
              fprintf(temp, "%s,%s ", temp_hash->key, temp_hash->value);
            }
            temp_hash = temp_hash->next;
          }
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
