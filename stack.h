#ifndef STACK_H
#define STACK_H

typedef struct Node {
  char data;
  struct Node *next;
} Node;

typedef struct Stack {
  Node *head;
  int size;
} Stack;

void SPUSH(Stack *stack, char element);
char SPOP(Stack *stack);


#endif