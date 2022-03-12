#include <stdio.h>

typedef struct Node *NODE;

int height(NODE N);
int max(int a, int b);
NODE newNode(int key);
NODE rightRotate(NODE y);
NODE leftRotate(NODE x);
int getBalance(NODE N);
NODE insertTree(NODE node, int key);

int rootKey(NODE root);
int rootCalls(NODE root);
void incrementCalls(NODE root);
NODE rootLeft(NODE root);
NODE rootRight(NODE root);

void freeTree(NODE root);