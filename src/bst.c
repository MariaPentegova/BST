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

/* H Итератор */

static bool iteratorEnsureCapacity(Iterator* it)
{
    if (it->top < it->capacity) {
        return true;
    }

    size_t newCapacity = (it->capacity == 0) ? 8 : it->capacity * 2;
    BSTNode** newStack = (BSTNode**)realloc(it->stack, newCapacity * sizeof(BSTNode*));
    if (newStack == NULL) {
        return false;
    }

    it->stack = newStack;
    it->capacity = newCapacity;
    return true;
}

static bool iteratorPush(Iterator* it, BSTNode* node)
{
    if (!iteratorEnsureCapacity(it)) {
        return false;
    }

    it->stack[it->top++] = node;
    return true;
}

static BSTNode* iteratorPopNode(Iterator* it)
{
    if (it == NULL || it->top == 0) {
        return NULL;
    }

    return it->stack[--it->top];
}

static bool iteratorPushLeftBranch(Iterator* it, BSTNode* node)
{
    while (node != NULL) {
        if (!iteratorPush(it, node)) {
            return false;
        }
        node = node->left;
    }
    return true;
}

Iterator* iteratorInit(BST* tree)
{
    Iterator* it = (Iterator*)malloc(sizeof(Iterator));
    if (it == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    it->stack = NULL;
    it->top = 0;
    it->capacity = 0;
    it->failed = false;

    if (tree != NULL) {
        if (!iteratorPushLeftBranch(it, tree->root)) {
            free(it->stack);
            free(it);
            errno = ENOMEM;
            return NULL;
        }
    }

    return it;
}

bool iteratorHasNext(Iterator* it)
{
    return it != NULL && !it->failed && it->top > 0;
}

int iteratorNext(Iterator* it)
{
    if (it == NULL || it->failed || !iteratorHasNext(it)) {
        errno = ERANGE;
        return 0;
    }

    BSTNode* node = iteratorPopNode(it);
    int result = node->value;

    errno = 0;
    if (!iteratorPushLeftBranch(it, node->right)) {
        it->failed = true;
        errno = ENOMEM;
    }

    return result;
}

void iteratorFree(Iterator* it)
{
    if (it == NULL) {
        return;
    }

    free(it->stack);
    free(it);
}

int main(){
  return 0;
}
