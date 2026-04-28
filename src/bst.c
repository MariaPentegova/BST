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

/* E Слияние двух деревьев */

BST* bstMerge(BST* tree1, BST* tree2)
{
    BST* result = bstCreate();
    if (result == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    Iterator* it1 = iteratorInit(tree1);
    Iterator* it2 = iteratorInit(tree2);

    if (it1 == NULL || it2 == NULL) {
        iteratorFree(it1);
        iteratorFree(it2);
        bstFree(result);
        errno = ENOMEM;
        return NULL;
    }

    errno = 0;
    while (iteratorHasNext(it1)) {
        int value = iteratorNext(it1);
        if (errno == ENOMEM) {
            iteratorFree(it1);
            iteratorFree(it2);
            bstFree(result);
            return NULL;
        }

        errno = 0;
        if (!bstInsert(result, value)) {
            if (errno == ENOMEM) {
                iteratorFree(it1);
                iteratorFree(it2);
                bstFree(result);
                return NULL;
            }
        }
    }

    errno = 0;
    while (iteratorHasNext(it2)) {
        int value = iteratorNext(it2);
        if (errno == ENOMEM) {
            iteratorFree(it1);
            iteratorFree(it2);
            bstFree(result);
            return NULL;
        }

        errno = 0;
        if (!bstInsert(result, value)) {
            if (errno == ENOMEM) {
                iteratorFree(it1);
                iteratorFree(it2);
                bstFree(result);
                return NULL;
            }
        }
    }

    iteratorFree(it1);
    iteratorFree(it2);
    return result;
}

int main(){
  return 0;
}
