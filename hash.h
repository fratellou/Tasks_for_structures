#ifndef HASH_H
#define HASH_H

typedef struct HashTable {
    char **keys;
    char **values;
    int size;
    int capacity;
} HashTable;

#endif