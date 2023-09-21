#ifndef SET_H
#define SET_H

typedef struct Set {
    char **elements;
    int size;
} Set;

void set(char *db_file, char **query);
void set_commands(char **query, Set *set);
void SADD(Set *set, char *element);
void SREM(Set *set, char *element);
int SISMEMBER(Set *set, char *element);
#endif