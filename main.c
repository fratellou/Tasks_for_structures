#include "main.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "hash.h"
#include "queue.h"
#include "set.h"
#include "stack.h"
#include "tree.h"
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
  scanf("%s", sequence);

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
  int len;
  printf("Enter the length of the set: ");
  scanf("%d", &len);

  int target;
  printf("Enter the required amount: ");
  scanf("%d", &target);

  Set *mySet = createSet(len);

  for (int i = 0; i < len; i++) {
    int elem;
    scanf("%d", &elem);
    SADD(mySet, elem);
  }

  int currentSet[MAX_LEN] = {0};

  if (!subsetSumFromSet(mySet, mySet->buckets, target, 0, currentSet, 0)) {
    printf("Subset with the required sum is not found\n");
  }
}

int subsetSumFromSet(Set *set, Node_set **buckets, int target, int currentIndex,
                     int currentSet[], int currentSum) {
  if (currentSum == target) {
    printf("{");
    for (int i = 0; i < currentIndex; i++) {
      printf("%d ", currentSet[i]);
    }
    printf("}\n");
    return 1;
  }
  if (currentSum > target || currentIndex >= set->size) {
    return 0;
  }

  for (Node_set *node = buckets[currentIndex]; node != NULL;
       node = node->next) {
    int element = node->element;

    if (currentSum + element <= target) {
      currentSet[currentIndex] = element;
      if (subsetSumFromSet(set, buckets, target, currentIndex + 1, currentSet,
                           currentSum + element))
        return 1;
    }
  }
  return 0;
}

void quest3() {
  Array *arr = createArray(10);
  ARADD(arr, 4);
  ARADD(arr, -7);
  ARADD(arr, 1);
  ARADD(arr, 5);
  ARADD(arr, -4);
  ARADD(arr, 0);
  ARADD(arr, -3);
  ARADD(arr, 2);
  ARADD(arr, 4);
  ARADD(arr, 1);

  int maxSum = maxSumCircularArray(arr);
  printf("Maximum sum of a subarray in the circular array is: %d\n", maxSum);
}

int max(int a, int b) { return (a > b) ? a : b; }

int min(int a, int b) { return (a < b) ? a : b; }
// Function to find the maximum sum subarray in a circular array
int maxSumCircularArray(Array *arr) {
  int maxSum = arr->data[0];
  int currMax = arr->data[0];
  int totalSum = arr->data[0];
  int minSum = arr->data[0];
  int currMin = arr->data[0];

  // Find maximum sum subarray in the array using Kadane's algorithm
  for (int i = 1; i < arr->size; i++) {
    currMax = max(arr->data[i], currMax + arr->data[i]);
    maxSum = max(maxSum, currMax);

    currMin = min(arr->data[i], currMin + arr->data[i]);
    minSum = min(minSum, currMin);

    totalSum += arr->data[i];
  }

  // If the total sum is equal to the minimum sum, return the maximum sum
  if (totalSum - minSum == 0) {
    return maxSum;
  }

  // Return the maximum of the maximum sum subarray and the difference
  // between the total sum and the minimum sum subarray
  return max(maxSum, totalSum - minSum);
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

  int isBST = isBinarySearchTree(root);
  if (isBST) {
    printf("The tree is a BST\n");
  } else {
    printf("The tree is not a BST\n");
  }
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
  int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
  int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

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
}

void quest6() {
  char str1[MAX_LEN];
  printf("Enter a first string: ");
  scanf("%s", str1);

  char str2[MAX_LEN];
  printf("Enter a second string: ");
  scanf("%s", str2);

  if (isIsomorphic(str1, str2))
    printf("Strings are isomorphic\n");
  else
    printf("Strings are not isomorphic\n");
}

int isIsomorphic(char *a, char *b) {
  int len_a = strlen(a);
  int len_b = strlen(b);

  if (len_a != len_b) {
    return 0;  // Strings of different lengths cannot be isomorphic
  }

  HashTable *a_to_b = createHashTable(
      len_a);  // Hash table for storing characters from string a
  HashTable *b_to_a = createHashTable(
      len_b);  // Hash table for storing characters from string b

  for (int i = 0; i < len_a; i++) {
    char ch_a = a[i];
    char ch_b = b[i];

    char *elem_a_to_b = HGET(a_to_b, &ch_a);
    char *elem_b_to_a = HGET(b_to_a, &ch_b);

    if ((elem_a_to_b != NULL && *elem_a_to_b != ch_b) ||
        (elem_b_to_a != NULL && *elem_b_to_a != ch_a)) {
      return 0;  // A character mismatch was found
    }

    HSET(a_to_b, &ch_a, &ch_b);
    HSET(b_to_a, &ch_b, &ch_a);
  }

  return 1;  // Strings are isomorphic
}
