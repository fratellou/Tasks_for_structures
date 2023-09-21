#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash(char *key, int capacity) {
    int sum = 0;
    int len = strlen(key);
    for (int i = 0; i < len; i++) {
        sum += key[i];
    }
    return sum % capacity;
}
// Функция для добавления пары ключ-значение в хэш-таблицу
void HSET(HashTable *hashtable, char *key, char *value) {
    int index = hash(key, hashtable->capacity);

    // Поиск свободного слота для вставки пары ключ-значение
    while (hashtable->keys[index] != NULL) {
        if (strcmp(hashtable->keys[index], key) == 0) {
            // Ключ уже существует, обновляем значение
            free(hashtable->values[index]);
            hashtable->values[index] = strdup(value);
            return;
        }
        index = (index + 1) % hashtable->capacity;
    }

    // Вставка пары ключ-значение
    hashtable->keys[index] = strdup(key);
    hashtable->values[index] = strdup(value);
    hashtable->size++;
}

// Функция для удаления пары ключ-значение из хэш-таблицы
void HDEL(HashTable *hashtable, char *key) {
    int index = hash(key, hashtable->capacity);

    // Поиск пары ключ-значение по ключу и удаление ее
    while (hashtable->keys[index] != NULL) {
        if (strcmp(hashtable->keys[index], key) == 0) {
            free(hashtable->keys[index]);
            free(hashtable->values[index]);
            hashtable->keys[index] = NULL;
            hashtable->values[index] = NULL;
            hashtable->size--;
            return;
        }
        index = (index + 1) % hashtable->capacity;
    }
}

// Функция для получения значения по ключу из хэш-таблицы
char *HGET(HashTable *hashtable, char *key) {
    int index = hash(key, hashtable->capacity);

    // Поиск значения по ключу
    while (hashtable->keys[index] != NULL) {
        if (strcmp(hashtable->keys[index], key) == 0) {
            return hashtable->values[index];
        }
        index = (index + 1) % hashtable->capacity;
    }

    return NULL;  // Значение не найдено
}