#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
    int* items; 
    int capacity; 
    int size; 
} Array;

void array(char *db_file, char **query);
void array_commands(char **query, Set *set);
Array *createArray(int size);
int set_calc(char *key);
char *SADD(Set *set, char *element);
char *SREM(Set *set, char *element);
int SISMEMBER(Set *set, char *element);
void write_set(char *filename, Set *set, char *struct_name, char *struct_type);
void free_set(Set *set);
#endif