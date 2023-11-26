#ifndef TREE_H
#define TREE_H

#include <stdio.h>

typedef struct Node_tree {
  int key;
  struct Node_tree* left;
  struct Node_tree* right;
} Node_tree;

Node_tree* createNode(int key);
Node_tree* TADD(Node_tree* root, int key);
void freeTree(Node_tree* root);

#endif