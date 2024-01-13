#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 256

// Creates and initializes a new set data structure
Set *createSet(int size) {
  Set *set = (Set *)malloc(sizeof(Set));
  set->size = size;
  set->buckets = (Node_set **)malloc(size * sizeof(Node_set *));

  for (int i = 0; i < size; i++) {
    set->buckets[i] = NULL;  // Initialize each bucket to NULL
  }

  return set;
}

// Calculates the index for a given element
int set_calc(char *element, int size) {
  int hash = 0;
  for (int i = 0; i < (int)strlen(element); i++) {
    hash += element[i];
  }
  return hash % size;
}

// Adds an element to the set
void SADD(Set *set, char *element) {
  int index = set_calc(element, set->size);
  Node_set *current = set->buckets[index];
  while (current != NULL) {
    if (strcmp(current->element, element) == 0) {
      return;
    }
    current = current->next;
  }

  Node_set *newNode = (Node_set *)malloc(sizeof(Node_set));
  newNode->element = strdup(element);
  newNode->next = set->buckets[index];
  set->buckets[index] = newNode;
}

// Removes an element from the set
void SREM(Set *set, char *element) {
  int index = set_calc(element, set->size);
  Node_set *current = set->buckets[index];
  Node_set *previous = NULL;

  while (current != NULL) {
    if (strcmp(current->element, element) == 0) {
      if (previous != NULL) {
        previous->next = current->next;
        free(current->element);
        free(current);
      } else {
        Node_set *temp = current->next;
        free(current->element);
        free(current);
        set->buckets[index] = temp;
      }
      return;
    }
    previous = current;
    current = current->next;
  }
}

// Checks if an element is a member of the set
int SISMEMBER(Set *set, char *element) {
  int index = set_calc(element, set->size);
  Node_set *current = set->buckets[index];
  while (current != NULL) {
    if (strcmp(current->element, element) == 0) {
      return 1;
    }
    current = current->next;
  }
  return 0;
}

// Returns the union of two sets
Set *SUNION(Set *set1, Set *set2) {
  Set *result = createSet(set1->size);

  for (int i = 0; i < set1->size; i++) {
    Node_set *current = set1->buckets[i];
    while (current != NULL) {
      SADD(result, current->element);
      current = current->next;
    }
  }

  for (int i = 0; i < set2->size; i++) {
    Node_set *current = set2->buckets[i];
    while (current != NULL) {
      SADD(result, current->element);
      current = current->next;
    }
  }

  return result;
}

// Returns the intersection of two sets
Set *SINTER(Set *set1, Set *set2) {
  Set *result = createSet(set1->size);
  for (int i = 0; i < set1->size; i++) {
    Node_set *current = set1->buckets[i];
    while (current != NULL) {
      if (SISMEMBER(set2, current->element)) {
        SADD(result, current->element);
      }
      current = current->next;
    }
  }
  return result;
}

// Returns the difference of two sets (set1 - set2)
Set *SDIFF(Set *set1, Set *set2) {
  Set *result = createSet(set1->size);
  for (int i = 0; i < set1->size; i++) {
    Node_set *current = set1->buckets[i];
    while (current != NULL) {
      if (!SISMEMBER(set2, current->element)) {
        SADD(result, current->element);
      }
      current = current->next;
    }
  }
  return result;
}

void printSet(Set *set) {
  for (int i = 0; i < set->size; i++) {
    Node_set *current = set->buckets[i];
    while (current != NULL) {
      printf("%s ", current->element);
      current = current->next;
    }
  }
  printf("\n");
}

void freeSet(Set *set) {
  for (int i = 0; i < set->size; i++) {
    Node_set *current = set->buckets[i];
    while (current != NULL) {
      Node_set *next = current->next;
      free(current->element);
      free(current);
      current = next;
    }
  }
  free(set->buckets);  // Free the array of buckets
  free(set);           // Free the set structure
}