#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct BSTNode {
    int value;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

typedef struct BST {
    BSTNode* root;
    size_t size;
} BST;

typedef struct Iterator {
    BSTNode** stack;
    size_t top;
    size_t capacity;
    bool failed;
} Iterator;

BST* bstCreate(void);
void bstFree(BST* tree);

/* true если вставили false если уже был или не хватило памяти */
bool bstInsert(BST* tree, int value);

bool bstContains(BST* tree, int value);
size_t bstSize(BST* tree);

/* D Удаление */
void bstDelete(BST* tree, int value);

#endif
