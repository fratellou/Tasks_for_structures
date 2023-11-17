#ifndef SET_H
#define SET_H
#define MAX_LEN 256

typedef struct Node_set {
  int element;
  struct Node_set *next;
} Node_set;

typedef struct Set {
  Node_set *buckets[MAX_LEN];
  int size;
} Set;

Set *createSet(int size);
void SADD(Set *set, int element);
#endif