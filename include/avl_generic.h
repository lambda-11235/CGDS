
#include <stdbool.h>
#include <stdlib.h>

#include "generic.h"


// This is the type of the vector elements
#ifndef TYPE
#error "Expected macro TYPE to be defined"
#endif

// This is an abbreviation of the type name.
// The vector will be declared as `struct avl_TYPE_ABBREV`.
// Defaults to TYPE, and should only be used for pointers.
#ifndef TYPE_ABBREV
#define TYPE_ABBREV TYPE
#endif


#define AVL_NODE GEN1(avl_node, TYPE_ABBREV)
struct AVL_NODE {
    TYPE elem;

    char balance;
    struct AVL_NODE *left;
    struct AVL_NODE *right;
};


#define AVL GEN1(avl, TYPE_ABBREV)
struct AVL {
    size_t size;
    struct AVL_NODE *root;
};


int METH(AVL, init)(struct AVL *avl);
int METH(AVL, free)(struct AVL *avl);

/**
 * Looks up the element using COMPARE on `key`.
 * If the element exists, then it is stored in `elem` if `elem` is non-null and
 * true is returned, otherwise `elem` is left unmodified and false is returned.
 */
bool METH(AVL, lookup)(struct AVL *avl, TYPE key, TYPE *elem);

/**
 * Inserts `elem` into the tree.
 */
int METH(AVL, insert)(struct AVL *avl, TYPE elem);

/**
 * Deletes the element matched using COMPARE on `key`.
 * If the element exists, then it is stored in `elem` if `elem` is non-null and
 * true is returned, otherwise `elem` is left unmodified and false is returned.
 */
bool METH(AVL, delete)(struct AVL *avl, TYPE key, TYPE *elem);


#undef AVL
#undef AVL_NODE
