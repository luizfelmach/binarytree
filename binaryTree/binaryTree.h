#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <vector.h>

typedef struct _binaryTree *BinaryTree;

typedef void (*binaryTreeDestroyFn)(void *);
typedef int (*binaryTreeCompareFn)(void *, void *);

BinaryTree binaryTree(binaryTreeCompareFn compare, binaryTreeDestroyFn destroy);
void       binaryTreeDestroy(BinaryTree bt);

void  binaryTreeSet(BinaryTree bt, void *data);
void *binaryTreeGet(BinaryTree bt, void *data);
void *binaryTreePop(BinaryTree bt, void *data);
int   binaryTreeEmpty(BinaryTree bt);

void *binaryTreeMax(BinaryTree bt);
void *binaryTreeMaxPop(BinaryTree bt);
void *binaryTreeMin(BinaryTree bt);
void *binaryTreeMinPop(BinaryTree bt);

void binaryTreeTraversalIn(BinaryTree bt, Vector traversal);
void binaryTreeTraversalPre(BinaryTree bt, Vector traversal);
void binaryTreeTraversalPost(BinaryTree bt, Vector traversal);
void binaryTreeTraversalLevel(BinaryTree bt, Vector traversal);

void binaryTreeTraversalInRecursive(BinaryTree bt, Vector traversal);
void binaryTreeTraversalPreRecursive(BinaryTree bt, Vector traversal);
void binaryTreeTraversalPostRecursive(BinaryTree bt, Vector traversal);

#endif