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
    Stack stack = {NULL};
    if (flag) {
        for (int i = 1; i < size; i++) {
            SPUSH(&stack, line[i]);
        }
    }
    stack_commands(query, &stack);
    write_stack(db_file, &stack, query[1], flag);
    
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
        char *element = stack->head->data;
        stack->head = stack->head->next;
        return element;
    }
}

void write_stack(char *filename, Stack *stack, char *struct_name, int flag) {
    FILE *temp = fopen("temp.txt", "w+");
    FILE *fp = fopen(filename, "r");
    if (fp && temp) {
        char *string = malloc(MAX_LEN * sizeof(char));
        while (fgets(string, MAX_LEN, fp) != NULL) {
            if ((strncmp(string, struct_name, strlen(struct_name)) == 0) || flag == 0) {
                fprintf(temp, "%s ", struct_name);
                while (stack->head != NULL) {
                    fprintf(temp, "%s ", stack->head->data);
                    SPOP(stack);
                }
                fprintf(temp, "\n");
                if (flag == 0) {
                    fprintf(temp, "%s", string);
                    flag = 1;
                }
            } else {
                fprintf(temp, "%s", string);
            }
        }
        free(string);
        remove(struct_name);
        rename("temp.txt", filename);
    } else {
        ERROR;
    }
    fclose(fp);
    fclose(temp);
}
