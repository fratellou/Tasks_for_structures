#include "array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 256

// Function to create an array
Array *createArray(int size) {
  Array *array = (Array *)malloc(sizeof(Array));
  array->data = (char *)malloc(size * sizeof(char));
  array->size = 0;
  return array;
}
