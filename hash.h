#ifndef HASH_H
#define HASH_H

typedef struct Node_hash {
  char *element;
  char *key;
  struct Node_hash *head;
  struct Node_hash *next;
} Node_hash;

typedef struct HashTable {
  Node_hash **table;
  int size;
} HashTable;

void hash(char *db_file, char **query);
void hash_commands(char **query, HashTable *hash);
HashTable *createHashTable(int size);
int hash_calc(char *key);
void HSET(HashTable *hashtable, char *key, char *value);
char *HDEL(HashTable *hashtable, char *key);
char *HGET(HashTable *hashtable, char *key);
void hash_free(HashTable *hashtable);
void write_hash(char *filename, HashTable *hashtable, char *struct_name,
                char *struct_type);

#endif