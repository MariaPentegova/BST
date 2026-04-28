#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "bst.h"

static BSTNode* bstNodeCreate(int value)
{
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    if (node == NULL) {
        return NULL;
    }

    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BST* bstCreate(void)
{
    BST* tree = (BST*)malloc(sizeof(BST));
    if (tree == NULL) {
        return NULL;
    }

    tree->root = NULL;
    tree->size = 0;
    return tree;
}

static void bstNodeFreeRecursive(BSTNode* node)
{
    if (node == NULL) {
        return;
    }

    bstNodeFreeRecursive(node->left);
    bstNodeFreeRecursive(node->right);
    free(node);
}

void bstFree(BST* tree)
{
    if (tree == NULL) {
        return;
    }

    bstNodeFreeRecursive(tree->root);
    free(tree);
}

size_t bstSize(BST* tree)
{
    return tree == NULL ? 0 : tree->size;
}

bool bstContains(BST* tree, int value)
{
    if (tree == NULL) {
        return false;
    }

    BSTNode* cur = tree->root;
    while (cur != NULL) {
        if (value < cur->value) {
            cur = cur->left;
        } else if (value > cur->value) {
            cur = cur->right;
        } else {
            return true;
        }
    }

    return false;
}

bool bstInsert(BST* tree, int value)
{
    if (tree == NULL) {
        return false;
    }

    BSTNode** cur = &tree->root;
    while (*cur != NULL) {
        if (value < (*cur)->value) {
            cur = &(*cur)->left;
        } else if (value > (*cur)->value) {
            cur = &(*cur)->right;
        } else {
            return false;
        }
    }

    *cur = bstNodeCreate(value);
    if (*cur == NULL) {
        errno = ENOMEM;
        return false;
    }

    tree->size++;
    return true;
}

/* F Проверка корректности BST */

static bool isValidNode(BSTNode* node, long long minAllowed, long long maxAllowed)
{
    if (node == NULL) {
        return true;
    }

    if ((long long)node->value <= minAllowed || (long long)node->value >= maxAllowed) {
        return false;
    }

    return isValidNode(node->left, minAllowed, node->value)
        && isValidNode(node->right, node->value, maxAllowed);
}

bool bstIsValid(BST* tree)
{
    if (tree == NULL) {
        return true;
    }

    return isValidNode(tree->root, LLONG_MIN, LLONG_MAX);
}

int main(){
  return 0;
}
