
#include "assert.h"
#include <stdio.h>


struct map_tuple {
    int key;
    int value;
};

#define TYPE struct map_tuple
#define TYPE_ABBREV int_int
#define COMPARE(x, y) ((x).key - (y).key)
#include "avl_generic.h"
#include "avl_generic_impl.h"
#undef COMPARE
#undef TYPE_ABBREV
#undef TYPE


size_t check_balance_factors(struct avl_node_int_int *node) {
    if (node == NULL)
        return 0;

    int left_height = check_balance_factors(node->left);
    int right_height = check_balance_factors(node->right);

    printf("elem = {%d, %d}, balance = %d, left_height = %d, right_height = %d\n",
        node->elem.key, node->elem.value, node->balance, left_height, right_height);
    fflush(stdout);

    assert(node->balance == right_height - left_height);
    assert(-2 < node->balance && node->balance < 2);

    return left_height > right_height ? left_height+1 : right_height+1;
}


int main(void) {
    struct avl_int_int map;
    int key;
    struct map_tuple tuple;

    avl_int_int_init(&map);


    for (key = 0; key < 100; key++) {
        assert(!avl_int_int_insert(&map, (struct map_tuple) {key, 100 - key - 1}));
        check_balance_factors(map.root);
    }

    for (key = 0; key < 100; key++) {
        printf("key = %d\n", key);
        avl_int_int_lookup(&map, (struct map_tuple) {key, 0}, &tuple);
        printf("value = %d\n", tuple.value);
        assert(tuple.value == 100 - key - 1);

        check_balance_factors(map.root);
    }


    for (key = 0; key < 100; key++) {
        assert(!avl_int_int_insert(&map, (struct map_tuple) {key, key}));
        check_balance_factors(map.root);
    }

    for (key = 0; key < 100; key++) {
        printf("key = %d\n", key);
        avl_int_int_lookup(&map, (struct map_tuple) {key, 0}, &tuple);
        printf("value = %d\n", tuple.value);
        assert(tuple.value == key);

        check_balance_factors(map.root);
    }

    for (key = 0; key < 100; key++) {
        printf("key = %d\n", key);
        avl_int_int_lookup(&map, (struct map_tuple) {key, 0}, NULL);

        check_balance_factors(map.root);
    }

    for (key = 0; key < 100; key++) {
        printf("key = %d\n", key);
        assert(avl_int_int_delete(&map, (struct map_tuple) {key, 0}, &tuple));
        printf("value = %d\n", tuple.value);
        assert(tuple.value == key);

        check_balance_factors(map.root);

        for (int i = 0; i < key+1; i++) {
            printf("i = %d\n", i);
            assert(!avl_int_int_lookup(&map, (struct map_tuple) {key, 0}, NULL));
        }

        for (int i = key+1; i < 100; i++) {
            printf("i = %d\n", i);
            avl_int_int_lookup(&map, (struct map_tuple) {key, 0}, &tuple);
            printf("value = %d\n", tuple.value);
            assert(tuple.value == key);
        }
    }


    avl_int_int_free(&map);

    return 0;
}
