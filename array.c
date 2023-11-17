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

// Function to insert an element at a specific index in the array
int ARINS(Array *arr, int index, int element) {
  if (arr->size < MAX_LEN && index >= 0 && index <= arr->size) {
    for (int i = arr->size; i > index; i--) {
      arr->data[i] = arr->data[i - 1];
    }
    arr->data[index] = element;
    arr->size++;
    return element;
  }
  return -1;
}
