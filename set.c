#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"

void set(char *db_file, char **query) {
    FILE *file = fopen(db_file, "a+");
    if (file != NULL) {
        char *set_name = malloc(MAX_LEN * sizeof(char));
        Set set;
        set.elements = NULL;
        set.size = 0;
        set_commands(query, &set);

        fclose(file);
        free(set_name);
        // SAVE(db_file, &set);
    } else
        ERROR;
}

void set_commands(char **query, Set *set) {
    if (!strcmp(query[0], "SADD")) {
        set->elements = malloc(MAX_LEN * sizeof(char *));
        SADD(set, query[2]);
        printf("-> %s\n", query[2]);
        free(set->elements);
    } else if (!strcmp(query[0], "SREM")) {
        SREM(set, query[2]);
        printf("-> %s\n", query[2]);
    } else if (!strcmp(query[0], "SISMEMBER")) {
        if (!SISMEMBER(set, query[2]))
            printf("\n-> FALSE");
        else
            printf("\n-> TRUE");
    } else
        ERROR;
}

void SADD(Set *set, char *element) {
    for (int i = 0; i < set->size; i++) {
        if (strcmp(set->elements[i], element) == 0) {
            return;
        }
    }

    set->elements = realloc(set->elements, (set->size + 1) * sizeof(char *));
    set->elements[set->size] = strdup(element);
    set->size++;
}

void SREM(Set *set, char *element) {
    for (int i = 0; i < set->size; i++) {
        if (strcmp(set->elements[i], element) == 0) {
            free(set->elements[i]);
            for (int j = i; j < set->size - 1; j++) {
                set->elements[j] = set->elements[j + 1];
            }
            set->size--;
            set->elements = realloc(set->elements, set->size * sizeof(char *));
            return;
        }
    }
}

int SISMEMBER(Set *set, char *element) {
    for (int i = 0; i < set->size; i++) {
        if (strcmp(set->elements[i], element) == 0) {
            return 1;
        }
    }
    return 0;
}
