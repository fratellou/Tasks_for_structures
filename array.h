#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
  int *data;
  int size;
} Array;

Array *createArray(int size);
int ARADD(Array *arr, int element);
void printArray(Array *arr);
void ARREM(Array *arr, int index);

#endif