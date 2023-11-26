#include "main.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

int main() {
#ifdef QUEST1
  quest1();
#endif
#ifdef QUEST2
  quest2();
#endif
#ifdef QUEST3
  quest3();
#endif
#ifdef QUEST4
  quest4();
#endif
#ifdef QUEST5
  quest5();
#endif
#ifdef QUEST6
  quest6();
#endif

  return 0;
}

void quest1() {
  char sequence[MAX_LEN];
  printf("Enter a sequence of brackets: ");
  scanf("%254s", sequence);

  if (isBalanced(sequence)) {
    printf("The brackets are balanced\n");
  } else {
    printf("The brackets are not balanced\n");
  }
}

// Function to check if a given sequence of brackets is correct
int isBalanced(char *sequence) {
  Stack stack = {NULL, 0};

  for (int i = 0; sequence[i] != '\0'; i++) {
    if (sequence[i] == '(' || sequence[i] == '{' || sequence[i] == '[') {
      SPUSH(&stack, sequence[i]);
    } else if (sequence[i] == ')' || sequence[i] == '}' || sequence[i] == ']') {
      if (stack.size == 0) {
        return 0;  // If the stack is empty, the sequence is incorrect
      }
      char top = SPOP(&stack);
      if ((top == '(' && sequence[i] != ')') ||
          (top == '{' && sequence[i] != '}') ||
          (top == '[' && sequence[i] != ']')) {
        return 0;
      }
    }
  }

  if (stack.size == 0) {
    return 1;  // If the stack is empty, the sequence is correct
  }
  return 0;  // If the stack is not empty, the sequence is incorrect
}

void quest2() {
  Set *set1 = createSet(MAX_LEN);
  Set *set2 = createSet(MAX_LEN);

  SADD(set1, "apple");
  SADD(set1, "banana");
  SADD(set1, "orange");

  SADD(set2, "banana");
  SADD(set2, "grape");
  SADD(set2, "watermelon");

  printf("Set 1: ");
  printSet(set1);

  printf("Set 2: ");
  printSet(set2);

  printf("Union set: ");
  Set *unionSet = SUNION(set1, set2);
  printSet(unionSet);

  printf("Intersection set: ");
  Set *intersectionSet = SINTER(set1, set2);
  printSet(intersectionSet);

  printf("Difference set: ");
  Set *differenceSet = SDIFF(set1, set2);
  printSet(differenceSet);

  printf("'banana' in set1: ");
  if (SISMEMBER(set1, "banana"))
    printf("TRUE\n");
  else
    printf("FALSE\n");
  printf("'banana' in set1 after removal: ");
  SREM(set1, "banana");
  if (SISMEMBER(set1, "banana"))
    printf("TRUE\n");
  else
    printf("FALSE\n");
  SREM(set2, "watermelon");

  printf("Set 1 after removal: ");
  printSet(set1);

  printf("Set 2 after removal: ");
  printSet(set2);

  freeSet(unionSet);
  freeSet(intersectionSet);
  freeSet(differenceSet);
  freeSet(set1);
  freeSet(set2);
}

void quest3() {
  const char *sequence1 = "meow@stud.nstu.ru";
  const char *pattern1 = "*nstu.ru";
  printf("Sequence: %s\nPattern: %s\nMatch: %s\n", sequence1, pattern1,
         matchPattern(sequence1, pattern1) ? "true" : "false");

  const char *sequence2 = "hello";
  const char *pattern2 = "h?lo";
  printf("Sequence: %s\nPattern: %s\nMatch: %s\n", sequence2, pattern2,
         matchPattern(sequence2, pattern2) ? "true" : "false");
}

int matchPattern(const char *sequence, const char *pattern) {
  while (*sequence != '\0' && *pattern != '\0') {
    if (*pattern == '*') {
      // Проверка для случая "*"
      // Пропускаем "*", сравниваем оставшуюся часть шаблона и
      // последовательности
      while (*pattern == '*') pattern++;
      while (*sequence != '\0' && !matchPattern(sequence, pattern)) sequence++;
    } else if (*pattern == '?' || *sequence == *pattern) {
      // Проверка для случая "?" или совпадения символов
      sequence++;
      pattern++;
    } else {
      // Если символы не совпадают
      return 0;
    }
  }

  // Если достигнут конец и шаблон и последовательность одновременно, то
  // совпадение
  return *sequence == '\0' && *pattern == '\0';
}

void quest4() {
  Node_tree *root = NULL;
  int numNodes, key;

  printf("Enter the number of nodes in the tree: ");
  scanf("%d", &numNodes);

  printf("Enter the values for each node: ");
  for (int i = 0; i < numNodes; i++) {
    scanf("%d", &key);
    root = TADD(root, key);
  }

  int BST = isBinarySearchTree(root);
  if (BST) {
    printf("The tree is a BST\n");
  } else {
    printf("The tree is not a BST\n");
  }
  freeTree(root);
}

int isBST(Node_tree *node, int min, int max) {
  // Пустое дерево считается валидным BST
  if (node == NULL) {
    return 1;
  }

  // Проверяем, что значение текущего узла находится в допустимом интервале
  if (node->key < min || node->key > max) {
    return 0;
  }

  // Рекурсивно проверяем левое и правое поддерево
  return isBST(node->left, min, node->key - 1) &&
         isBST(node->right, node->key + 1, max);
}

// Функция для проверки, является ли дерево BST
int isBinarySearchTree(Node_tree *root) {
  // Указываем начальные значения границ для проверки
  int min = INT_MIN;
  int max = INT_MAX;

  // Рекурсивно вызываем функцию isBST для корневого узла
  return isBST(root, min, max);
}

void quest5() {
  int N = 4;
  int startX = 0;
  int startY = 3;
  int targetX = 2;
  int targetY = 0;

  bfs(N, startX, startY, targetX, targetY);
}

void bfs(int N, int startX, int startY, int targetX, int targetY) {
  // Создаем шахматную доску размером NxN
  int board[N][N];

  // Инициализируем доску значением -1, чтобы отслеживать пустые клетки
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      board[i][j] = -1;
    }
  }

  // Создаем очередь для обхода
  Queue queue;
  queue.head = NULL;
  queue.tail = NULL;
  queue.size = 0;

  // Добавляем стартовую клетку в очередь
  QPUSH(&queue, startX * N + startY);
  board[startX][startY] = 0;

  // Возможные шаги коня
  const int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
  const int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

  while (queue.size > 0) {
    // Получаем текущую клетку из очереди
    int current = queue.head->data;
    QPOP(&queue);

    // Разделяем координаты текущей клетки
    int x = current / N;
    int y = current % N;

    // Проверяем, является ли текущая клетка целевой
    if (x == targetX && y == targetY) {
      break;
    }

    // Перебираем все возможные шаги коня
    for (int i = 0; i < 8; i++) {
      int newX = x + dx[i];
      int newY = y + dy[i];

      // Проверяем, что новые координаты входят в границы доски
      if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
        // Проверяем, что клетка еще не посещена
        if (board[newX][newY] == -1) {
          // Увеличиваем расстояние до новой клетки
          board[newX][newY] = board[x][y] + 1;

          // Добавляем новую клетку в очередь
          QPUSH(&queue, newX * N + newY);
        }
      }
    }
  }

  // Восстанавливаем путь обратно от целевой клетки
  int path[N * N][2];
  int pathIndex = 0;

  int x = targetX;
  int y = targetY;
  path[pathIndex][0] = x;
  path[pathIndex][1] = y;
  pathIndex++;

  while (x != startX || y != startY) {
    // Перебираем все возможные шаги коня
    for (int i = 0; i < 8; i++) {
      int newX = x + dx[i];
      int newY = y + dy[i];

      // Проверяем, что новые координаты входят в границы доски
      if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
        // Проверяем, что расстояние от текущей клетки до новой клетки меньше на
        // 1
        if (board[newX][newY] == board[x][y] - 1) {
          x = newX;
          y = newY;

          path[pathIndex][0] = x;
          path[pathIndex][1] = y;
          pathIndex++;

          break;
        }
      }
    }
  }

  // Выводим путь
  for (int i = pathIndex - 1; i >= 0; i--) {
    printf("(%d, %d)", path[i][0] + 1, path[i][1] + 1);
    if (i > 0) {
      printf(" -> ");
    }
  }
  freeQueue(&queue);
}

void quest6() {
  HashTable *hashTable = createHashTable(10);

  HSET(hashTable, "name", "John");
  HSET(hashTable, "age", "25");
  HSET(hashTable, "city", "New York");

  printf("Hash Table Contents:\n");
  printHashTable(hashTable);
  freeHashTable(hashTable);
}
