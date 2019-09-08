
#include <stdlib.h>

#include "generic.h"


// This is the type of the vector elements
#ifndef TYPE
#error "Expected macro TYPE to be defined"
#endif

// This is an abbreviation of the type name.
// The vector will be declared as `struct vector_TYPE_ABBREV`.
// Defaults to TYPE, and should only be used for pointers.
#ifndef TYPE_ABBREV
#error "Expected macro TYPE_ABBREV to be defined"
#endif

#define VECTOR GEN1(vector, TYPE_ABBREV)
struct VECTOR {
    size_t length;
    size_t capacity;

    TYPE *data;
};


int METH(VECTOR, init)(struct VECTOR *vec);
int METH(VECTOR, free)(struct VECTOR *vec);

/**
 * Returns a pointer to the element indexed by `idx`.
 */
static inline TYPE *METH(VECTOR, index)(struct VECTOR *vec, size_t idx) {
    return &vec->data[idx];
}

/**
 * Copies `elem` onto the end of the vector.
 */
int METH(VECTOR, push)(struct VECTOR *vec, TYPE elem);

/**
 * Removes the element at the end of the vector, and copies it into the memory
 * pointed to by `elem`.
 *
 * If `elem` is NULL no copying occurs.
 */
int METH(VECTOR, pop)(struct VECTOR *vec, TYPE *elem);

/**
 * Inserts the element `elem` into index `idx`.
 */
int METH(VECTOR, insert)(struct VECTOR *vec, size_t idx, TYPE elem);

/**
 * Deletes the element indexed by `idx`.
 *
 * If `elem` is not NULL, then the deleted element is first copied into the
 * pointed to memory.
 */
int METH(VECTOR, delete)(struct VECTOR *vec, size_t idx, TYPE *elem);

#undef VECTOR
