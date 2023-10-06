#ifndef HASH_H
#define HASH_H

typedef struct HashTable {
    char **keys;
    char **values;
    int size;
    int capacity;
} HashTable;

void hash(char *db_file, char **query);
void hash_commands(char **query, HashTable *hash);
int hash_make(char *key, int capacity);
void HSET(HashTable *hashtable, char *key, char *value);
char *HDEL(HashTable *hashtable, char *key);
char *HGET(HashTable *hashtable, char *key);
void HASH_STRUCT(char **line, char **keys_line, char *filename, int *flag, char *struct_name, int *size);

#endif