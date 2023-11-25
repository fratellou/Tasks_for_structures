#ifndef HASH_H
#define HASH_H

typedef struct Node_hash {
  char *element;
  char *key;
  struct Node_hash *next;
} Node_hash;

typedef struct HashTable {
  Node_hash **table;
  int size;
  int capacity;
} HashTable;

HashTable *createHashTable(int size);
int hash_calc(char *key, int capacity);
void HSET(HashTable *hashtable, char *key, char *value);
char *HGET(HashTable *hashtable, char *key);
void printHashTable(HashTable *hashtable);

#endif