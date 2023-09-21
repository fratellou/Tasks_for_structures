#ifndef STACK_H
#define STACK_H

typedef struct Stack {
    char **elements;
    int top;
} Stack;

void stack(char *db_file, char **query);
void stack_commands(char **query, Stack *stack);
void SPUSH(Stack *stack, char *element);
char *SPOP(Stack *stack);

#endif