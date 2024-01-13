#ifndef SET_H
#define SET_H
#define MAX_LEN 256

typedef struct Node_set {
  char *element;
  struct Node_set *next;
} Node_set;

typedef struct Set {
  Node_set **buckets;
  int size;
} Set;

Set *createSet(int size);
int set_calc(char *element, int size);
void SADD(Set *set, char *element);
void SREM(Set *set, char *element);
int SISMEMBER(Set *set, char *element);
Set *SUNION(Set *set1, Set *set2);
Set *SINTER(Set *set1, Set *set2);
Set *SDIFF(Set *set1, Set *set2);
void printSet(Set *set);
void freeSet(Set *set);
#endif