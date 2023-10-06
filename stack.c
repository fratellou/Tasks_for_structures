#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"

void stack(char *db_file, char **query) {
    char **line = malloc(MAX_LEN * sizeof(char *));  //Строка в файле, содержащая записи структуры
    int size = 0;
    int flag = 0;
    STRUCT(line, db_file, flag, query[1], size);
    Stack stack;
    stack.elements = NULL;
    stack.top = 0;
    stack.elements = malloc(MAX_LEN * sizeof(char *));
    if (flag) {
        for (int i = 1; i < size; i++) {
            SPUSH(&stack, line[i]);
        }
    }
    stack_commands(query, &stack);
    SAVE(db_file, stack, stack.top, query[1], flag, 0);
    for (int i = 0; i <= size; i++) {
        free(line[i]);
    }
    free(line);
}

void stack_commands(char **query, Stack *stack) {
    if (!strcmp(query[0], "SPUSH")) {
        SPUSH(stack, query[2]);
        printf("-> %s\n", query[2]);
    } else if (!strcmp(query[0], "SPOP")) {
        printf("-> %s\n", SPOP(stack));
    } else
        ERROR;
}

void SPUSH(Stack *stack, char *element) {
    if (stack->top < MAX_LEN) {
        stack->elements[stack->top] = element;
        stack->top++;
    } else
        ERROR;
}

char *SPOP(Stack *stack) {
    if (stack->top > 0) {
        stack->top--;
        char *element = stack->elements[stack->top];
        return element;
    } else
        return NULL;
}
