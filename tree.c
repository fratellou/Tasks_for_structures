#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

// This function creates a new tree node with the given key
Node_tree* createNode(int key) {
  Node_tree* newNode = (Node_tree*)malloc(sizeof(Node_tree));
  newNode->key = key;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

// This function inserts a new node with the given key into the tree
Node_tree* TADD(Node_tree* root, int key) {
  // If the tree is empty, create a new node and return it
  if (root == NULL) {
    return createNode(key);
  }
  if (key < root->key) {
    root->left = TADD(root->left, key);
  } else {
    root->right = TADD(root->right, key);
  }
  return root;
}
