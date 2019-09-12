
#include "assert.h"
#include <stdio.h>


struct map_tuple {
    int key;
    int value;
};

#define TYPE struct map_tuple
#define TYPE_ABBREV int_int
#define EQUAL(x, y) ((x).key == (y).key)
#define HASH(x) (x.key)
#include "hashtable_generic.h"
#include "hashtable_generic_impl.h"
#undef HASH
#undef EQUAL
#undef TYPE_ABBREV
#undef TYPE


int main(void) {
    struct hashtable_int_int map;
    int key;
    struct map_tuple tuple;

    hashtable_int_int_init(&map, 8);


    for (key = 0; key < 100; key++) {
        assert(!hashtable_int_int_insert(&map, (struct map_tuple) {key, 100 - key - 1}));
    }

    for (key = 0; key < 100; key++) {
        printf("key = %d\n", key);
        hashtable_int_int_lookup(&map, (struct map_tuple) {key, 0}, &tuple);
        printf("value = %d\n", tuple.value);
        assert(tuple.value == 100 - key - 1);
    }


    for (key = 0; key < 100; key++) {
        assert(!hashtable_int_int_insert(&map, (struct map_tuple) {key, key}));
    }

    for (key = 0; key < 100; key++) {
        printf("key = %d\n", key);
        hashtable_int_int_lookup(&map, (struct map_tuple) {key, 0}, &tuple);
        printf("value = %d\n", tuple.value);
        assert(tuple.value == key);
    }

    for (key = 0; key < 100; key++) {
        printf("key = %d\n", key);
        hashtable_int_int_lookup(&map, (struct map_tuple) {key, 0}, NULL);
    }

    for (key = 0; key < 100; key++) {
        printf("key = %d\n", key);
        assert(hashtable_int_int_delete(&map, (struct map_tuple) {key, 0}, &tuple));
        printf("value = %d\n", tuple.value);
        assert(tuple.value == key);

        for (int i = 0; i < key+1; i++) {
            printf("i = %d\n", i);
            assert(!hashtable_int_int_lookup(&map, (struct map_tuple) {key, 0}, NULL));
        }

        for (int i = key+1; i < 100; i++) {
            printf("i = %d\n", i);
            hashtable_int_int_lookup(&map, (struct map_tuple) {key, 0}, &tuple);
            printf("value = %d\n", tuple.value);
            assert(tuple.value == key);
        }
    }


    hashtable_int_int_free(&map);

    return 0;
}

