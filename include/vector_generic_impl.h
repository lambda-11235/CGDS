
#include <string.h>


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

#define INIT_CAPACITY 8


static inline int METH(VECTOR, realloc)(struct VECTOR *vec) {
    void *data = realloc(vec->data, vec->capacity*sizeof(TYPE));

    if (data == NULL) {
        return 1;
    } else {
        vec->data = data;
        return 0;
    }
}


int METH(VECTOR, init)(struct VECTOR *vec) {
    vec->length = 0;
    vec->capacity = INIT_CAPACITY;

    vec->data = calloc(vec->capacity, sizeof(TYPE));

    if (vec->data == NULL)
        return 1;
    else
        return 0;
}


int METH(VECTOR, free)(struct VECTOR *vec) {
    free(vec->data);

    return 0;
}


int METH(VECTOR, push)(struct VECTOR *vec, TYPE elem) {
    if (vec->length == vec->capacity) {
        vec->capacity *= 2;
        if(METH(VECTOR, realloc)(vec) != 0)
            return 1;
    }

    vec->data[vec->length] = elem;
    vec->length++;

    return 0;
}


int METH(VECTOR, pop)(struct VECTOR *vec, TYPE *elem) {
    if (vec->length < vec->capacity/4 && vec->capacity > INIT_CAPACITY) {
        vec->capacity /= 2;
        if(METH(VECTOR, realloc)(vec) != 0)
            return 1;
    }

    vec->length--;

    if (elem != NULL)
        *elem = vec->data[vec->length];

    return 0;
}


int METH(VECTOR, insert)(struct VECTOR *vec, size_t idx, TYPE elem) {
    if (vec->length == vec->capacity) {
        vec->capacity *= 2;
        if(METH(VECTOR, realloc)(vec) != 0)
            return 1;
    }

    TYPE append = elem;
    TYPE tmp;

    for (; idx < vec->length; idx++) {
        tmp = vec->data[idx];
        vec->data[idx] = append;
        append = tmp;
    }

    vec->data[vec->length] = append;
    vec->length++;

    return 0;
}


int METH(VECTOR, delete)(struct VECTOR *vec, size_t idx, TYPE *elem) {
    if (vec->length < vec->capacity/4 && vec->capacity > INIT_CAPACITY) {
        vec->capacity /= 2;
        if(METH(VECTOR, realloc)(vec) != 0)
            return 1;
    }

    if (elem != NULL)
        *elem = vec->data[idx];

    for (size_t i = idx + 1; i < vec->length; i++)
        vec->data[i - 1] = vec->data[i];

    vec->length--;

    return 0;
}
