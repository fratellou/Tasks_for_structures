#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"

void array(char *db_file, char **query) {
  char **line = malloc(
      MAX_LEN * sizeof(char *)); // Строка в файле, содержащая записи структуры
  int size = 0;
  int isnt_empty = 0;

  Array *array = createArray(MAX_LEN);
  STRUCT(line, db_file, isnt_empty, query[1], size, "arr:");
  if (isnt_empty) {
    for (int i = 1; i < size; i++) {
      ARADD(array, line[i]);
    }
  }
  array_commands(query, array);
  write_array(db_file, array, query[1], "arr:");
  free_array(array);
  for (int i = 0; i <= size; i++) {
    free(line[i]);
  }
  free(line);
}

void array_commands(char **query, Array *array) {
  if (!strcmp(query[0], "ARADD")) {
    char *value = ARADD(set, query[2]);
    printf("-> %s\n", value);
  } else if (!strcmp(query[0], "ARREM")) {
    char *value = ARREM(set, query[2]);
    printf("-> %s\n", value);
  } else if (!strcmp(query[0], "ARISMEMBER")) {
    if (!ARISMEMBER(set, query[2]))
      printf("\n-> FALSE\n");
    else
      printf("\n-> TRUE\n");
  } else {
    ERROR;
  }
}

Array *createArray(int size) {
    array->items = (int*)malloc(capacity * sizeof(int));
    array->capacity = capacity;
    array->size = 0;
  return array;
}

int set_calc(char *key) {
  int hash = 0;
  for (int i = 0; i < (int)strlen(key); i++) {
    hash += (int)key[i];
  }
  return hash % MAX_LEN;
}

char *SADD(Set *set, char *element) {
  int index = set_calc(element);
  if (set->buckets[index] != NULL) {
    set->buckets[index]->element = element;
    return element;
  }
  Node_set *newNode = (Node_set *)malloc(sizeof(Node_set));
  newNode->element = element;
  newNode->next = set->buckets[index];
  set->buckets[index] = newNode;
  return element;
}

char *SREM(Set *set, char *element) {
  int index = set_calc(element);
  Node_set *current = set->buckets[index];
  Node_set *previous = NULL;
  while (current != NULL) {
    if (strcmp(current->element, element) == 0) {
      if (previous != NULL) {
        previous->next = current->next;
      } else {
        set->buckets[index] = current->next;
      }
      char *element = current->element;
      free(current);
      return element;
    }
    previous = current;
    current = current->next;
  }
  return NULL;
}

int SISMEMBER(Set *set, char *element) {
  int index = set_calc(element);
  Node_set *current = set->buckets[index];
  while (current != NULL) {
    if (strcmp(current->element, element) == 0) {
      return 1;
    }
    current = current->next;
  }
  return 0;
}

void write_array(char *filename, Array *array, char *struct_name, char *struct_type) {
  FILE *temp = fopen("temp.txt", "a+");
  FILE *fp = fopen(filename, "r");
  if (fp && temp) {
    char string[MAX_LEN];
    int new_input = 0;
    while (fgets(string, MAX_LEN, fp) != NULL) {
      char new_string[MAX_LEN];
      strcpy(new_string, string);
      char *istr = strtok(string, " ");
      char *second_word = strtok(NULL, " ");
      if (new_input == 0) {
        fprintf(temp, "%s %s ", struct_type, struct_name);
        for (int i = 0; i < MAX_LEN; i++) {
          if (set->buckets[i] != NULL) {
            fprintf(temp, "%s ", set->buckets[i]->element);
          }
        }
        fprintf(temp, "\n");
        new_input = 1;
      }
      if ((strcmp(istr, struct_type) == 0) &&
          (strcmp(second_word, struct_name) == 0)) {
        continue;
      } else {
        fprintf(temp, "%s", new_string);
      }
    }
    remove(filename);
    rename("temp.txt", filename);
  } else {
    ERROR;
  }
  fclose(fp);
  fclose(temp);
}

void free_array(Array *array) {
  if (array == NULL) {
    return;
  }
  free(array->items);
  free(array->capacity);
  free(array->size);
}
/*
// Добавление элемента в конец массива
void append(Array* array, int item) {
    // Проверяем, есть ли достаточно места в массиве
    if (array->size < array->capacity) {
        array->items[array->size++] = item;
    }
    else {
        // Если места нет, увеличиваем емкость массива вдвое
        array->capacity *= 2;
        array->items = (int*)realloc(array->items, array->capacity * sizeof(int));
           array->items[array->size++] = item;
    }
}

// Вставка элемента в указанную позицию массива
void insert(Array* array, int item, int index) {
    // Проверяем, есть ли достаточно места в массиве
    if (array->size < array->capacity) {
        // Сдвигаем все элементы после указанной позиции на одну позицию вправо
        for (int i = array->size; i > index; i--) {
            array->items[i] = array->items[i - 1];
        }
        array->items[index] = item;
        array->size++;
    }
    else {
        // Если места нет, увеличиваем емкость массива вдвое
        array->capacity *= 2;
        array->items = (int*)realloc(array->items, array->capacity * sizeof(int));
        // Сдвигаем все элементы после указанной позиции на одну позицию вправо
        for (int i = array->size; i > index; i--) {
            array->items[i] = array->items[i - 1];
        }
        array->items[index] = item;
        array->size++;
    }
}

// Удаление элемента из массива по указанному индексу
void removeAt(Array* array, int index) {
    // Сдвигаем все элементы после указанной позиции на одну позицию влево
    for (int i = index; i < array->size - 1; i++) {
        array->items[i] = array->items[i + 1];
    }
    array->size--;
}

// Получение элемента массива по указанному индексу
int get(Array* array, int index) {
    return array->items[index];
}

// Изменение элемента массива по указанному индексу
void set(Array* array, int item, int index) {
    array->items[index] = item;
}

// Функция для поиска элемента в массиве
int search(Array* array, int item) {
    for (int i = 0; i < array->size; i++) { // Проходим по всем элементам массива
        if (array->items[i] == item) {  // Если элемент равен искомому элементу, то возвращаем его индекс
            return i;
        }
    }
    return -1;  // Если элемент не найден, то возвращаем -1
}

// Очистка массива
void clear(Array* array) {
    free(array->items);
    array->size = 0;
    array->capacity = 0;
}

// Вывод элементов массива
void print(Array* array) {
    for (int i = 0; i < array->size; i++) {
        printf("%d ", array->items[i]);
    }
    printf("\n");
}

int main() {
    Array array;
    initArray(&array, 3);

    append(&array, 10);
    append(&array, 20);
    append(&array, 30);
    print(&array);

    insert(&array, 15, 1);
    print(&array);

    removeAt(&array, 2);
    print(&array);

    set(&array, 25, 1);
    print(&array);

    printf("Index of 25: %d\n", search(&array, 25));
    printf("Value at index 2: %d\n", get(&array, 2));

    clear(&array);
    print(&array);
    return 0;
}
*/