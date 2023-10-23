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
      char *key = malloc(MAX_LEN * sizeof(char)); 
    char **hash_line = malloc(MAX_LEN * sizeof(char *));
  if (isnt_empty) {
    for (int i = 0; i < size; i++) {
      char *ptr = strtok(line[i], ",");
      int hash_size = 0;  
      strcpy(key, ptr);                                  
      while (ptr != NULL) {                                               
            if (strcmp(ptr, "\n")) {                                          
              hash_line[hash_size] = malloc(MAX_LEN * sizeof(char));                     
              strcpy(hash_line[hash_size], ptr);                                        
              hash_size++;                                                          
            }                                                                 
            ptr = strtok(NULL, ",");                                         
          }   
      for (int j = 0; j < hash_size; j++) {
        HSET(hashtable, key, hash_line[j]);
      }        
    }
  }
  hash_commands(query, hashtable);
  write_hash(db_file, hashtable, query[1], &isnt_empty, key, "hash:");
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
  ht->table = malloc(sizeof(Node_hash**) * size);
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

void HSET(HashTable* hashtable, char *key, char *value) { 
  int index = hash_calc(key); 
  Node_hash *newNode = (Node_hash*)malloc(sizeof(Node_hash)); 
  newNode->key = key; 
  newNode->element = value;
  newNode->next = NULL;
  if (hashtable->table[index] == NULL) { 
    hashtable->table[index] = newNode;
    hashtable->head = newNode;
    hashtable->tail = newNode; 
  } else { 
      Node_hash *current = hashtable->table[index]; 
      while (current->next != NULL) {
        current = current->next; 
        } 
      current->next = newNode; 
      } 
      hashtable->tail = newNode;
}

char *HDEL(HashTable *hashtable, char *key) {
  int index = hash_calc(key);
  Node_hash *current = hashtable->table[index];
  Node_hash *prev = NULL;
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      if (prev == NULL) { 
        hashtable->table[index] = current->next;
      } else {
        prev->next = current->next;
      }
      char *value = current->element;
      free(current->key);
      free(current);
      return value;
    }
    prev = current;
    current = current->next;
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

void write_hash(char *filename, HashTable *hashtable, char *struct_name, int *isnt_empty, char *key, char *struct_type) {
  FILE *temp = fopen("temp.txt", "a+");
  FILE *fp = fopen(filename, "r");
  if (fp && temp) {
    char *string = malloc(MAX_LEN * sizeof(char));
    while (fgets(string, MAX_LEN, fp) != NULL) {
      char *istr = strtok(string, " "); 
      char *second_word = strtok(NULL, " "); 
        if (((strcmp(istr, struct_type) == 0) && (strcmp(second_word, struct_name) == 0))  || *isnt_empty == 0) {
        fprintf(temp, "%s %s", struct_type, struct_name);
        for (int i = 0; i < hashtable->size; i++) {
          Node_hash *temp_hash = hashtable->table[i];
          if (temp_hash->key != NULL && temp_hash->element != NULL) {
              if (strcmp(temp_hash->key, key) == 0) {
                 fprintf(temp, "%s", temp_hash->element);
                 if (temp_hash->next != NULL) fprintf(temp, ",");
                }
          }
        }
        fprintf(temp, "\n");
        if (*isnt_empty == 0) {
          fprintf(temp, "%s", string);
          *isnt_empty = 1;
        }
      } else {
        fprintf(temp, "%s", string);
      }
    }
    free(string);
    remove(filename);
    rename("temp.txt", filename);
  } else {
    ERROR;
  }
  fclose(fp);
  fclose(temp);
}
