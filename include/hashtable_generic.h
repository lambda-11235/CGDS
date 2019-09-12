
#include <stdbool.h>
#include <stdlib.h>

#include "generic.h"


// This is the type of the vector elements
#ifndef TYPE
#error "Expected macro TYPE to be defined"
#endif

// This is an abbreviation of the type name.
// The vector will be declared as `struct hashtable_TYPE_ABBREV`.
#ifndef TYPE_ABBREV
#error "Expected macro TYPE_ABBREV to be defined"
#endif


#define HT_NODE GEN1(ht_node, TYPE_ABBREV)
struct HT_NODE {
    struct HT_NODE *prev;
    struct HT_NODE *next;

    struct HT_NODE *chain;
    TYPE elem;
};


#define HASHTABLE GEN1(hashtable, TYPE_ABBREV)
struct HASHTABLE {
    size_t size;
    size_t capacity;

    struct HT_NODE *head;
    struct HT_NODE *tail;
    struct HT_NODE **nodes;
};


int METH(HASHTABLE, init)(struct HASHTABLE *ht, size_t init_capacity);
int METH(HASHTABLE, free)(struct HASHTABLE *ht);

/**
 * Looks up the element using COMPARE on `key`.
 * If the element exists, then it is stored in `elem` if `elem` is non-null and
 * true is returned, otherwise `elem` is left unmodified and false is returned.
 */
bool METH(HASHTABLE, lookup)(struct HASHTABLE *ht, TYPE key, TYPE *elem);

/**
 * Inserts `elem` into the tree.
 */
int METH(HASHTABLE, insert)(struct HASHTABLE *ht, TYPE elem);

/**
 * Deletes the element matched using COMPARE on `key`.
 * If the element exists, then it is stored in `elem` if `elem` is non-null and
 * true is returned, otherwise `elem` is left unmodified and false is returned.
 */
bool METH(HASHTABLE, delete)(struct HASHTABLE *ht, TYPE key, TYPE *elem);


#undef HASHTABLE
#undef HT_NODE

