#include "array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 256

// Function to create an array
Array *createArray(int size) {
  Array *array = (Array *)malloc(sizeof(Array));
  array->data = (int *)malloc(size * sizeof(int));
  array->size = 0;
  return array;
}

// Function to add an element to the end of the array
int ARADD(Array *arr, int element) {
  if (arr->size < MAX_LEN) {
    arr->data[arr->size++] = element;
    return element;
  }
  return -1;
}

void printArray(Array *arr) {
  for (int i = 0; i < arr->size; i++) {
    printf("%d ", arr->data[i]);
  }
  printf("\n");
}

// Function to remove an element at a specific index in the array
void ARREM(Array *arr, int index) {
  if (arr->size > 0 && index >= 0 && index < arr->size) {
    for (int i = index; i < arr->size - 1; i++) {
      arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
  }
}
