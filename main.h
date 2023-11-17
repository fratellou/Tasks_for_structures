#ifndef MAIN_H
#define MAIN_H

void quest1();
void quest2();
void quest3();
void quest4();
void quest5();
void quest6();
int isBalanced(char *sequence);
int isIsomorphic(char *a, char *b);
int subsetSumFromSet(Set *set, Node_set **buckets, int target, int currentIndex,
                     int currentSet[], int currentSum);
Array findLargestSubarray(Array arr);
int maxSumCircularArray(Array *arr);
int min(int a, int b);
int max(int a, int b);
int isBST(Node_tree *node, int min, int max);
int isBinarySearchTree(Node_tree *root);
void bfs(int N, int startX, int startY, int targetX, int targetY);

#endif