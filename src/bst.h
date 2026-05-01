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

/*
 G k й минимальный элемент
 Если k <= 0 возвращает 0 и выставляет errno EINVAL
 Если tree == NULL или k > bstSize(tree) возвращает 0 и выставляет errno ERANGE
 Если не хватило памяти на внутренний итератор возвращает 0 и выставляет errno ENOMEM
*/
int bstKthMin(BST* tree, int k);


#endif
