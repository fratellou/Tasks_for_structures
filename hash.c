#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 256

// Function to create a new hash table
HashTable *createHashTable(int capacity) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  ht->size = 0;
  ht->table = (Node_hash **)calloc(capacity, sizeof(Node_hash *));
  ht->capacity = capacity;
  return ht;
}

// Function to calculate the hash value for a given key
int hash_calc(char *key, int capacity) {
  int hash = 0;
  for (int i = 0; i < (int)strlen(key); i++) {
    hash += (int)key[i];
  }
  return hash % capacity;
}

// Function to insert or update a key-value pair in the hash table
void HSET(HashTable *hashtable, char *key, char *value) {
  int index = hash_calc(key, hashtable->capacity);
  Node_hash *newNode = (Node_hash *)malloc(sizeof(Node_hash));

  newNode->key = (char *)malloc(strlen(key) + 1);
  strcpy(newNode->key, key);

  newNode->element = (char *)malloc(strlen(value) + 1);
  strcpy(newNode->element, value);

  newNode->next = NULL;

  if (hashtable->table[index] == NULL) {
    hashtable->table[index] = newNode;
  } else {
    Node_hash *current = hashtable->table[index];
    while (current->next != NULL) {
      if (strcmp(current->key, key) == 0) {
        current->element = value;
      }
      current = current->next;
    }
    current->next = newNode;
  }
  hashtable->size++;
}

// Retrieves an element from the hash table based on the provided key
char *HGET(HashTable *hashtable, char *key) {
  int index = hash_calc(key, hashtable->capacity);
  Node_hash *current = hashtable->table[index];
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return current->element;
    }
    current = current->next;
  }
  return NULL;
}