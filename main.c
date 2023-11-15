#include "array.h"
#include "double_set.h"
#include "hash.h"
#include "queue.h"
#include "stack.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

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

    char sequence[100];
    printf("Введите последовательность скобок: ");
    scanf("%s", sequence);

    if (isBalanced(sequence)) {
        printf("Скобки вложены правильно\n");
    }
    else {
        printf("Скобки вложены неправильно\n");
    }

    /*
    // Определение структуры стека
struct Stack {
    char data;
    struct Stack* next;
};

// Функция для создания нового элемента стека
struct Stack* newNode(char data) {
    struct Stack* stackNode = (struct Stack*)malloc(sizeof(struct Stack));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

// Функция для добавления элемента в стек
void push(struct Stack** root, char data) {
    struct Stack* stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

// Функция для удаления элемента из стека и возврата его значения
char pop(struct Stack** root) {
    if (*root == NULL)
        return '\0';
    struct Stack* temp = *root;
    *root = (*root)->next;
    char popped = temp->data;
    free(temp);
    return popped;
}

// Функция для проверки, является ли данная последовательность скобок корректной
int isBalanced(char* sequence) {
    struct Stack* stack = NULL;

    for (int i = 0; sequence[i] != '\0'; i++) {
        if (sequence[i] == '(' || sequence[i] == '{' || sequence[i] == '[') {
            push(&stack, sequence[i]); // Добавляем открывающую скобку в стек
        }
        else if (sequence[i] == ')' || sequence[i] == '}' || sequence[i] == ']') {
            if (stack == NULL) {
                return 0; // Если стек пустой, то последовательность некорректна
            }
            char top = pop(&stack); // Извлекаем последний элемент из стека
            if ((top == '(' && sequence[i] != ')') || (top == '{' && sequence[i] != '}') || (top == '[' && sequence[i] != ']')) {
                return 0; // Если последовательность скобок некорректна, то возвращаем 0
            }
        }
    }

    if (stack == NULL) {
        return 1; // Если стек пустой, то последовательность корректна
    }
    return 0; // Если стек не пустой, то последовательность некорректна
}

    */
    
}

void quest2() {
    /*
    #include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

void subsetSum(int set[], int n, int target, int currentIndex, int currentSet[], int currentSum, bool *foundSubset) {
    if (currentSum == target) {
        printf("{");
        for (int i = 0; i < currentIndex; i++) {
            printf("%d", currentSet[i]);
            if (i != currentIndex - 1) {
                printf(", ");
            }
        }
        printf("}\n");
        *foundSubset = true;
        return;
    }
    if (currentSum > target || currentIndex >= n) {
        return;
    }
    
    // Перебор элементов начиная с текущего индекса
    for (int i = currentIndex; i < n; i++) {
        // Проверка, что сумма текущего подмножества плюс текущий элемент не превышает заданную сумму
        if (currentSum + set[i] <= target) {
            currentSet[currentIndex] = set[i];
            // Рекурсивный вызов функции со следующим индексом и обновленным текущим подмножеством и суммой
            subsetSum(set, n, target, currentIndex + 1, currentSet, currentSum + set[i], foundSubset);
        }
    }
}

void findSubsets(int set[], int n, int target) {
    int currentSet[MAX_SIZE] = {0};
    bool foundSubset = false;
    
    subsetSum(set, n, target, 0, currentSet, 0, &foundSubset);
    
    if (!foundSubset) {
        printf("Подмножество с заданной суммой не найдено\n");
    }
}

int main() {
    int set[] = {4, 10, 5, 1, 3, 7};
    int n = sizeof(set) / sizeof(set[0]);
    int target = 15;
    
    // Сортировка множества по убыванию
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (set[i] < set[j]) {
                int temp = set[i];
                set[i] = set[j];
                set[j] = temp;
            }
        }
    }
    
    findSubsets(set, n, target);
    
    return 0;
}
    */
}

void quest3() {
    /*
    void printSubarray(int arr[], int start, int end) {
    for (int i = start; i <= end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void findLargestSubarray(int arr[], int n) {
    int maxSum = arr[0];
    int currentSum = arr[0];
    int startIndex = 0;
    int endIndex = 0;
    int currentStartIndex = 0;

    for (int i = 1; i < n * 2; i++) {
        int j = i % n;
        
        if (currentSum < 0) {
            currentSum = arr[j];
            currentStartIndex = j;
        } else {
            currentSum += arr[j];
        }

        if (currentSum > maxSum) {
            maxSum = currentSum;
            startIndex = currentStartIndex;
            endIndex = j;
        }
    }

    printf("Подмассив с наибольшей суммой: ");
    printSubarray(arr, startIndex, endIndex);
}

int main() {
    int arr[] = {4, -7, 1, 5, -4, 0, -3, 2, 4, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    findLargestSubarray(arr, n);

    return 0;
}
    */
}

void quest4() {
    /*
    #include <stdbool.h>

// Структура для представления узла дерева 
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Рекурсивная функция для проверки, является ли дерево BST
// node - указатель на текущий узел
// min - минимально допустимое значение (NULL для неограниченности)
// max - максимально допустимое значение (NULL для неограниченности)
// Возвращает true, если дерево является BST, иначе false
bool isBSTUtil(struct Node* node, struct Node* min, struct Node* max)
{
    // Базовый случай: пустое дерево является BST
    if (node == NULL)
        return true;

    // Если значение узла нарушает условия BST, то дерево не является BST
    if ((min != NULL && node->data <= min->data) || (max != NULL && node->data >= max->data))
        return false;

    // Рекурсивно проверяем левое и правое поддерево
    return isBSTUtil(node->left, min, node) && isBSTUtil(node->right, node, max);
}

// Функция для вызова isBSTUtil с корневым узлом
bool isBST(struct Node* root)
{
    return isBSTUtil(root, NULL, NULL);
}
```

Вы можете использовать эту функцию следующим образом:

```c
int main()
{
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));
    root->data = 4;
    
    struct Node* leftChild = (struct Node*)malloc(sizeof(struct Node));
    leftChild->data = 2;
    
    struct Node* rightChild = (struct Node*)malloc(sizeof(struct Node));
    rightChild->data = 6;
    
    root->left = leftChild;
    root->right = rightChild;
    
    bool isBST1 = isBST(root);
    
    if (isBST1)
        printf("Дерево является BST\n");
    else
        printf("Дерево не является BST\n");
    
    return 0;
}
    */
}

void quest5() {
    /*
    typedef struct {
    int x, y;
} Position;

typedef struct Node {
    Position position;
    int steps;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} Queue;

// Функция для создания новой очереди
Queue createQueue() {
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    return q;
}

// Функция для добавления элемента в очередь
void enqueue(Queue* q, Position position, int steps) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->position = position;
    newNode->steps = steps;
    newNode->next = NULL;

    if (q->head == NULL) {
        q->head = newNode;
        q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
}

// Функция для удаления элемента из очереди
Position dequeue(Queue* q, int* steps) {
    if (q->head == NULL) {
        printf("Queue is empty.\n");
        Position emptyPosition;
        emptyPosition.x = -1;
        emptyPosition.y = -1;
        return emptyPosition;
    }

    Node* firstNode = q->head;
    Position position = firstNode->position;
    *steps = firstNode->steps;

    q->head = firstNode->next;
    free(firstNode);

    if (q->head == NULL) {
        q->tail = NULL;
    }

    return position;
}

// Функция для проверки, находится ли позиция в пределах доски
int isInsideBoard(int x, int y, int N) {
    return (x >= 1 && x <= N && y >= 1 && y <= N);
}

// Функция для вычисления кратчайшего пути коня на шахматной доске
void findShortestPath(int N, Position start, Position target) {
    int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
    int visited[N][N];

    // Инициализация матрицы посещений
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            visited[i][j] = 0;
        }
    }

    Queue queue = createQueue();
    enqueue(&queue, start, 0);
    visited[start.x][start.y] = 1;

    while (queue.head != NULL) {
        int steps;
        Position currentPosition = dequeue(&queue, &steps);

        // Если достигли целевой позиции, выводим путь и количество шагов
        if (currentPosition.x == target.x && currentPosition.y == target.y) {
            printf("Path: (%d, %d)", currentPosition.x, currentPosition.y);
            printf(" -> Steps: %d\n", steps);
            return;
        }

        // Перебираем все возможные позиции коня и добавляем их в очередь
        for (int i = 0; i < 8; i++) {
            int nextX = currentPosition.x + dx[i];
            int nextY = currentPosition.y + dy[i];

            if (isInsideBoard(nextX, nextY, N) && !visited[nextX][nextY]) {
                Position nextPosition;
                nextPosition.x = nextX;
                nextPosition.y = nextY;

                enqueue(&queue, nextPosition, steps + 1);
                visited[nextX][nextY] = 1;
            }
        }
    }

    printf("Path does not exist.\n");
}

int main() {
    int N = 4;
    Position start, target;
    start.x = 1;
    start.y = 4;
    target.x = 3;
    target.y = 1;

    findShortestPath(N, start, target);

    return 0;
}
    */
}

void quest6() {
    /*
    #include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isIsomorphic(char* a, char* b) {
    int len_a = strlen(a);
    int len_b = strlen(b);

    if (len_a != len_b) {
        return 0; // Строки разной длины не могут быть изоморфными
    }

    char a_to_b[256] = {0}; // Хэш-таблица для хранения символов из строки a
    char b_to_a[256] = {0}; // Хэш-таблица для хранения символов из строки b

    for (int i = 0; i < len_a; i++) {
        char ch_a = a[i];
        char ch_b = b[i];

        if ((a_to_b[ch_a] != 0 && a_to_b[ch_a] != ch_b) || (b_to_a[ch_b] != 0 && b_to_a[ch_b] != ch_a)) {
            return 0; // Найдено несоответствие символов
        }

        a_to_b[ch_a] = ch_b;
        b_to_a[ch_b] = ch_a;
    }

    return 1; // Строки изоморфны
}

int main() {
    char a[] = "fall";
    char b[] = "redd";
    printf("%d\n", isIsomorphic(a, b));

    char c[] = "mad";
    char d[] = "odd";
    printf("%d\n", isIsomorphic(c, d));

    return 0;
}
    */
}
