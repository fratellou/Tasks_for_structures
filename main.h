#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

#include "array.h"
#include "hash.h"
#include "queue.h"
#include "set.h"
#include "stack.h"
#include "tree.h"

void quest1();
void quest2();
void quest3();
void quest4();
void quest5();
void quest6();
int isBalanced(char *sequence);
bool match(Array *sequence, Array *template);
int isBST(Node_tree *node, int min, int max);
int isBinarySearchTree(Node_tree *root);
void bfs(int N, int startX, int startY, int targetX, int targetY);
int isIsomorphic(char *a, char *b);

#endif