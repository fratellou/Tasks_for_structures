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
  Array *sequence1 = createArray(MAX_LEN);
  sequence1->data = "meow@stud.nstu.ru";
  sequence1->size = strlen(sequence1->data);

  Array *template1 = createArray(MAX_LEN);
  template1->data = "*@stud.nstu.ru";
  template1->size = strlen(template1->data);

  Array *sequence2 = createArray(MAX_LEN);
  sequence2->data = "hello";
  sequence2->size = strlen(sequence2->data);

  Array *template2 = createArray(MAX_LEN);
  template2->data = "h?lo";
  template2->size = strlen(template2->data);

  if (match(sequence1, template1)) {
    printf("Sequence 1 matches the template\n");
  } else {
    printf("Sequence 1 does not match the template\n");
  }

  if (match(sequence2, template2)) {
    printf("Sequence 2 matches the template\n");
  } else {
    printf("Sequence 2 does not match the template\n");
  }

  free(sequence1->data);
  free(sequence1);
  free(template1->data);
  free(template1);
  free(sequence2->data);
  free(sequence2);
  free(template2->data);
  free(template2);
}

// Function to check if a sequence matches a template
bool match(Array *sequence, Array *template) {
  int seqLen = sequence->size;
  int templateLen = template->size;

  int dp[seqLen + 1][templateLen + 1];
  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1;

  for (int j = 1; j <= templateLen; j++) {
    if (template->data[j - 1] == '*') {
      dp[0][j] = dp[0][j - 1];
    }
  }

  for (int i = 1; i <= seqLen; i++) {
    for (int j = 1; j <= templateLen; j++) {
      if (template->data[j - 1] == sequence->data[i - 1] ||
          template->data[j - 1] == '?') {
        dp[i][j] = dp[i - 1][j - 1];
      } else if (template->data[j - 1] == '*') {
        dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
      }
    }
  }

  return dp[seqLen][templateLen];
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
  // An empty tree is considered valid BST
  if (node == NULL) {
    return 1;
  }

  // Check that the value of the current node is in the acceptable range
  if (node->key < min || node->key > max) {
    return 0;
  }

  return isBST(node->left, min, node->key - 1) &&
         isBST(node->right, node->key + 1, max);
}

// Function to check whether the tree is BST
int isBinarySearchTree(Node_tree *root) {
  int min = INT_MIN;
  int max = INT_MAX;

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
  int board[N][N];

  // Initialize the board with the value -1 to keep track of empty cells
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      board[i][j] = -1;
    }
  }

  // Creating a queue for crawling
  Queue queue;
  queue.head = NULL;
  queue.tail = NULL;
  queue.size = 0;

  // Adding the starting cell to the queue
  QPUSH(&queue, startX * N + startY);
  board[startX][startY] = 0;

  // Possible steps of the horse
  const int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
  const int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

  while (queue.size > 0) {
    // Getting the current cell from the queue
    int current = queue.head->data;
    QPOP(&queue);

    // We divide the coordinates of the current cell
    int x = current / N;
    int y = current % N;

    // Check if the current cell is the target cell
    if (x == targetX && y == targetY) {
      break;
    }

    // We go through all the possible steps of the horse
    for (int i = 0; i < 8; i++) {
      int newX = x + dx[i];
      int newY = y + dy[i];

      // We check that the new coordinates are included in the boundaries of the
      // board
      if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
        // We check that the cell has not been visited yet
        if (board[newX][newY] == -1) {
          // Increasing the distance to the new cell
          board[newX][newY] = board[x][y] + 1;

          // Adding a new cell to the queue
          QPUSH(&queue, newX * N + newY);
        }
      }
    }
  }

  // Restoring the path back from the target cell
  int path[N * N][2];
  int pathIndex = 0;

  int x = targetX;
  int y = targetY;
  path[pathIndex][0] = x;
  path[pathIndex][1] = y;
  pathIndex++;

  while (x != startX || y != startY) {
    // We go through all the possible steps of the horse
    for (int i = 0; i < 8; i++) {
      int newX = x + dx[i];
      int newY = y + dy[i];

      // We check that the new coordinates are included in the boundaries of the
      // board
      if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
        // Check that the distance from the current cell to the new cell is less
        // by 1
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

  // Output the path
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
