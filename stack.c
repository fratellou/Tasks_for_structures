#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"
#define MAX_SIZE 256

void stack(char *db_file, char **query) {
   Stack stack = {NULL};
   read_stack(db_file, &stack); 
   stack_commands(query, &stack);
   write_stack(db_file, &stack);
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
    Node *node = malloc(sizeof(Node));
    node->data = element;
    if (stack->head == NULL) {
        stack->head = node;
    } else {
        node->next = stack->head; 
        stack->head = node;
    }

}

char *SPOP(Stack *stack) {
    if (stack->head == NULL) {
        return NULL;
    } else {
        char* element = stack->head->data;
        stack->head = stack->head->next;
        return element;
    }
}

void write_stack(char *filename, Stack *stack) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    Node *current = stack->head;
    while (current != NULL) {
        fwrite(current->data, sizeof(char), strlen(current->data), file);
        current = current->next;
    }
    fclose(file);
}

Stack* read_stack(char *filename, Stack *stack) {
    if (stack == NULL) {
        stack = malloc(sizeof(Stack));
        stack->head = NULL;
    }
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
    char buffer[MAX_SIZE];
    while (fgets(buffer, MAX_SIZE, file) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        SPUSH(stack, buffer);
    }
    fclose(file);
    return stack;
}