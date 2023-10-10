#ifndef HASH_H
#define HASH_H

typedef struct Node_hash {
  char *value;
  char *key;
  struct Node_hash *next;
} Node_hash;

typedef struct HashTable {
  Node_hash **table;
  int size;
} HashTable;

void hash(char *db_file, char **query);
void hash_commands(char **query, HashTable *hash);
HashTable *createHashTable(int size);
Node_hash *createNode(char *key, char *value);
int hash_calc(char *key);
void HSET(HashTable *hashtable, char *key, char *value);
char *HDEL(HashTable *hashtable, char *key);
char *HGET(HashTable *hashtable, char *key);
void write_hash(char *filename, HashTable *hashtable, char *struct_name,
                int *flag);
void printHashTable(HashTable *hashtable);

#endif