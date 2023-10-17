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
  STRUCT(line, db_file, isnt_empty, query[1], size);
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
  //printHashTable(hashtable);
  hash_commands(query, hashtable);
  //printHashTable(hashtable);
  write_hash(db_file, hashtable, query[1], &isnt_empty);
  printHashTable(hashtable);
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
      free(key);
    free(hash_line);
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
  ht->table = malloc(sizeof(Node_hash**) * size);
  for (int i = 0; i < size; i++) {
    ht->table[i] = NULL;
  }
  return ht;
}

int hash_calc(char *key) {
  int hash = 0;
  for (int i = 0; i < strlen(key); i++) {
      hash += (int)key[i];
  }
  return hash % MAX_LEN; 
}
/*

void HSET(HashTable *hashtable, char *key, char *value) {
  int index = hash_calc(key);
  Node_hash *temp = hashtable->table[index];
  while (temp != NULL) {
    if (strcmp(temp->key, key) == 0) {
      if (hashtable->head == NULL) {
        Node_hash *newNode = (Node_hash *)malloc(sizeof(Node_hash));
        newNode->key = key;
        newNode->element = value;
        newNode->next = NULL;
        newNode->prev = NULL;
        newNode->next = hashtable->table[index];
        hashtable->table[index] = newNode;
      }
      else {
        Squeue->tail->next = node;
        queue->tail = node;
  }
      }

    }
  }

}
*/

void HSET(HashTable* hashtable, char key, char *value) { 
  int index = hash_calc(key); 
  Node_hash *newNode = (Node_hash*)malloc(sizeof(Node_hash)); 
  newNode->key = key; 
  newNode->element = value;
  newNode->next = NULL;
  if (hashtable->table[index] == NULL) { 
    hashtable->table[index] = newNode; 
  } else { 
      Node_hash *current = hashtable->table[index]; 
      while (current->next != NULL) {
        current = current->next; 
        } 
      current->next = newNode; 
      } 
}

char *HDEL(HashTable *hashtable, char *key) {
}

char *HGET(HashTable *hashtable, char *key) {
}

void write_hash(char *filename, HashTable *hashtable, char *struct_name, int *isnt_empty) {
  FILE *temp = fopen("temp.txt", "a+");
  FILE *fp = fopen(filename, "r");
  if (fp && temp) {
    char *string = malloc(MAX_LEN * sizeof(char));
    while (fgets(string, MAX_LEN, fp) != NULL) {
      if ((strncmp(string, struct_name, strlen(struct_name)) == 0) || *isnt_empty == 0) {
        fprintf(temp, "%s ", struct_name);

        for (int i = 0; i < hashtable->size; i++) {
          Node_hash *temp_hash = hashtable->table[i];
          while (temp_hash != NULL) {
            if (temp_hash->key != NULL && temp_hash->value != NULL) {
              char *temp_key = malloc(strlen(temp_hash->key) + 1);
              char *temp_value = malloc(strlen(temp_hash->value) + 1);
              strcpy(temp_key, temp_hash->key);
              strcpy(temp_value, temp_hash->value);
              fprintf(temp, "%s,%s ", temp_key, temp_value);
              free(temp_key);
              free(temp_value);
            }
            temp_hash = temp_hash->next;
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
    remove(struct_name);
    rename("temp.txt", filename);
  } else {
    ERROR;
  }
  fclose(fp);
  fclose(temp);
}

void printHashTable(HashTable *hashtable) {
    printf("Hash Table:\n");
    for (int i = 0; i < hashtable->size; i++) {
        printf("[%d]: ", i);
        Node_hash *temp = hashtable->table[i];
        while (temp != NULL) {
            printf("(%s, %s) ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
}
