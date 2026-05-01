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

/* H Итератор inorder без рекурсии */
Iterator* iteratorInit(BST* tree);
bool iteratorHasNext(Iterator* it);

/*
 Если итератор исчерпан или it == NULL возвращает 0 и выставляет errno ERANGE
 Если во время продвижения не хватило памяти возвращает текущий элемент
 Выставляет errno ENOMEM и переводит итератор в состояние failed
 После этого дальнейшее использование итератора не допускается
 iteratorHasNext(it) вернет false
*/
int iteratorNext(Iterator* it);

void iteratorFree(Iterator* it);


#endif
