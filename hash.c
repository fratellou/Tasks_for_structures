#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"

void hash(char *db_file, char **query) {
    char **val_line = malloc(MAX_LEN * sizeof(char *));
    char **key_line = malloc(MAX_LEN * sizeof(char *));
    int size = 0;
    int flag = 0;
    printf("%s", db_file);
    // HASH_STRUCT(val_line, key_line, db_file, &flag, query[1], &size);
    HashTable hash;
    hash.values = NULL;
    hash.keys = NULL;
    hash.size = 0;
    hash.capacity = 0;
    hash.values = malloc(MAX_LEN * sizeof(char *));
    hash.keys = malloc(MAX_LEN * sizeof(char *));
    printf("hello");
    if (flag) {
        for (int i = 1; i < MAX_LEN; i++) {
            printf("true");
            // HSET(&hash, key_line[i], val_line[i]);
        }
    }
    for (int i = 0; i < 3; i++) {
        printf("%s\n", val_line[i]);
    }
    hash_commands(query, &hash);
    // HASH_SAVE(db_file, hash, stack.top, query[1], flag, 0);

    for (int i = 0; i < size; i++) {
        free(val_line[i]);
        free(key_line[i]);
    }

    free(key_line);
    free(val_line);
}

void hash_commands(char **query, HashTable *hash) {
    if (!strcmp(query[0], "HSET")) {
        HSET(hash, query[2], query[3]);
        printf("-> %s\n", query[2]);
    } else if (!strcmp(query[0], "HDEL")) {
        char *value = HDEL(hash, query[2]);
        printf("-> %s\n", value);
        free(value);
    } else if (!strcmp(query[0], "HGET")) {
        char *value = HGET(hash, query[2]);
        printf("-> %s\n", value);
    } else {
        ERROR;
    }
}

int hash_make(char *key, int capacity) {
    int sum = 0;
    int len = strlen(key);
    for (int i = 0; i < len; i++) {
        sum += key[i];
    }
    return sum % capacity;
}

void HSET(HashTable *hashtable, char *key, char *value) {
    int index = hash_make(key, hashtable->capacity);

    while (hashtable->keys[index] != NULL) {
        if (strcmp(hashtable->keys[index], key) == 0) {
            free(hashtable->values[index]);
            hashtable->values[index] = strdup(value);
            return;
        }
        index = (index + 1) % hashtable->capacity;
    }

    hashtable->keys[index] = strdup(key);
    hashtable->values[index] = strdup(value);
    hashtable->size++;
}

char *HDEL(HashTable *hashtable, char *key) {
    int index = hash_make(key, hashtable->capacity);

    while (hashtable->keys[index] != NULL) {
        if (strcmp(hashtable->keys[index], key) == 0) {
            char *value =
                hashtable
                    ->values[index];  // ошибка была здесь - нужно возвращать указатель на char, а не char
            free(hashtable->keys[index]);
            free(hashtable->values[index]);
            hashtable->keys[index] = NULL;
            hashtable->values[index] = NULL;
            hashtable->size--;
            return value;
        }
        index = (index + 1) % hashtable->capacity;
    }

    return NULL;  // ошибка была здесь - нужно вернуть NULL, если ключ не найден
}

char *HGET(HashTable *hashtable, char *key) {
    int index = hash_make(key, hashtable->capacity);
    while (hashtable->keys[index] != NULL) {
        if (strcmp(hashtable->keys[index], key) == 0) {
            return hashtable->values[index];
        }
        index = (index + 1) % hashtable->capacity;
    }
    return NULL;
}

void HASH_STRUCT(char **line, char **keys_line, char *filename, int *flag, char *struct_name, int *size) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        FILE *new = fopen(filename, "a+");
        fprintf(new, "\n");
        fclose(new);
        ERROR;
    }
    fclose(fp);
    FILE *file = fopen(filename, "r");
    if (file) {
        char *string = malloc(MAX_LEN * sizeof(char));
        while (fgets(string, MAX_LEN, file) != NULL) {
            if (strncmp(string, struct_name, strlen(struct_name)) == 0) {
                char *istr = strtok(string, " ");
                while (istr != NULL) {
                    if (strcmp(istr, "\n") != 0) {
                        char *istr_line = strtok(istr, ",");
                        while (istr_line != NULL) {
                            keys_line[*size] = malloc(MAX_LEN * sizeof(char));
                            line[*size] = malloc(MAX_LEN * sizeof(char));
                        }
                        strcpy(line[*size], istr);
                        size++;
                    }
                    istr = strtok(NULL, " ");
                }
                *flag = 1;
                break;
            }
        }
        free(string);
        fclose(file);
    } else {
        ERROR;
    }
}
