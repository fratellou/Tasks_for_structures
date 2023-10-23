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
void stack_commands(char **query, Stack *stack);
void SPUSH(Stack *stack, char *element);
char *SPOP(Stack *stack);
void write_stack(char *filename, Stack *stack, char *struct_name, int *flag, char *struct_type);

#endif