#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
  char *data;
  int size;
} Array;

Array *createArray(int size);

#endif