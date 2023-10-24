#ifndef SET_H
#define SET_H

typedef struct Node_set {
  char *element;
  struct Node_set *next;
} Node_set;

typedef struct Set {
  Node_set **buckets;
  int size;
} Set;

void set(char *db_file, char **query);
void set_commands(char **query, Set *set);
int set_calc(char *element, int size);
void SADD(Set *set, char *element);
void SREM(Set *set, char *element);
int SISMEMBER(Set *set, char *element);
void freeSet(Set *set);
void write_set(char *filename, Set *set, char *struct_name, char *struct_type);
#endif