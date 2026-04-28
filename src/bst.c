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

/* D Удаление */

static BSTNode* findMinNode(BSTNode* node)
{
    if (node == NULL) {
        return NULL;
    }

    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

static BSTNode* deleteNodeRecursive(BSTNode* node, int value, bool* deleted)
{
    if (node == NULL) {
        return NULL;
    }

    if (value < node->value) {
        node->left = deleteNodeRecursive(node->left, value, deleted);
        return node;
    }

    if (value > node->value) {
        node->right = deleteNodeRecursive(node->right, value, deleted);
        return node;
    }

    *deleted = true;

    if (node->left == NULL && node->right == NULL) {
        free(node);
        return NULL;
    }

    if (node->left == NULL) {
        BSTNode* right = node->right;
        free(node);
        return right;
    }

    if (node->right == NULL) {
        BSTNode* left = node->left;
        free(node);
        return left;
    }

    BSTNode* successor = findMinNode(node->right);
    node->value = successor->value;

    bool dummyDeleted = false;
    node->right = deleteNodeRecursive(node->right, successor->value, &dummyDeleted);
    return node;
}

void bstDelete(BST* tree, int value)
{
    if (tree == NULL) {
        return;
    }

    bool deleted = false;
    tree->root = deleteNodeRecursive(tree->root, value, &deleted);
    if (deleted) {
        tree->size--;
    }
}

int main(){
  return 0;
}
