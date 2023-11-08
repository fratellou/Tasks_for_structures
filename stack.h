#ifndef STACK_H
#define STACK_H

typedef struct Node {
  char *data;
  struct Node *next;
} Node;

typedef struct Stack {
  Node *head;
  int size;
} Stack;

void stack(char *db_file, char **query);
void SPUSH(Stack *stack, char *element);
void SPOP(Stack *stack);


#endif