
#include <assert.h>
#include <stdio.h>

#include "vector_common.h"


int main(int argc, char *argv[])
{
    struct vector_int vec;
    int x, y, i;

    assert(!vector_int_init(&vec));

    for (x = 0; x < 100; x++)
        assert(!vector_int_push(&vec, x));

    assert(vec.length == 100);

    for (i = 0; i < 100; i++)
        assert(i == *vector_int_index(&vec, i));

    i = 65;
    x = 1345;
    y = x;
    assert(!vector_int_insert(&vec, i, x));
    assert(y == *vector_int_index(&vec, i));
    assert(!vector_int_delete(&vec, i, &x));
    assert(x == y);
    assert(!vector_int_insert(&vec, i, x));
    assert(y == *vector_int_index(&vec, i));
    assert(!vector_int_delete(&vec, i, NULL));

    for (i = 0; i < 100; i++) {
        assert(!vector_int_pop(&vec, &x));
        assert(100 - i - 1 == x);
    }

    assert(!vector_int_push(&vec, x));
    assert(!vector_int_pop(&vec, NULL));

    assert(vec.length == 0);

    assert(!vector_int_free(&vec));

    return 0;
}
