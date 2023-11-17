#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 256

// Creates and initializes a new set data structure
Set *createSet(int size) {
  Set *set = (Set *)malloc(sizeof(Set));
  set->size = size;
  for (int i = 0; i < size; i++) {
    set->buckets[i] = NULL;
  }
  return set;
}

// Adds an element to the set
void SADD(Set *set, int element) {
  int index = element % set->size;
  if (set->buckets[index] != NULL) {
    return;
  }
  Node_set *newNode = (Node_set *)malloc(sizeof(Node_set));
  newNode->element = element;
  newNode->next = set->buckets[index];
  set->buckets[index] = newNode;
}
