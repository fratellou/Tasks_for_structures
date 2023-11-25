#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
  int *data;
  int size;
} Array;

typedef struct {
  int maxSum;
  int startIndex;
  int endIndex;
} Result;

Array *createArray(int size);
int ARADD(Array *arr, int element);

#endif