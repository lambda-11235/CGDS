
#include <string.h>

// This is the type of the vector elements
#ifndef TYPE
#error "Expected macro TYPE to be defined"
#endif

// This is an abbreviation of the type name.
// The vector will be declared as `struct hashtable_TYPE_ABBREV`.
// Defaults to TYPE, and should only be used for pointers.
#ifndef TYPE_ABBREV
#define TYPE_ABBREV TYPE
#endif

// EQUAL(a, b) should be true if a and b are equal.
// Note that defining EQUAL as (a.x == b.x) and ignoring other members is
// acceptable. In fact, it's the preferred way to implement maps.
#ifndef EQUAL
#error "Expected macro EQUAL to be defined"
#endif

// A hash function for TYPE. Must return a size_t.
// If EQUAL(a, b), then we must have HASH(a) == HASH(b).
#ifndef HASH
#error "Expected macro HASH to be defined"
#endif


#define HT_NODE GEN1(ht_node, TYPE_ABBREV)
#define HASHTABLE GEN1(hashtable, TYPE_ABBREV)


int METH(HASHTABLE, init)(struct HASHTABLE *ht, size_t init_capacity) {
    ht->size = 0;
    ht->capacity = init_capacity;

    ht->head = NULL;
    ht->tail = NULL;

    ht->nodes = calloc(ht->capacity, sizeof(struct HT_NODE*));
    if (ht->nodes == NULL)
        return 1;

    memset(ht->nodes, 0, ht->capacity*sizeof(struct HT_NODE*));

    return 0;
}


int METH(HASHTABLE, free)(struct HASHTABLE *ht) {
    struct HT_NODE *node = ht->head;

    while (node != NULL) {
        struct HT_NODE *old = node;
        node = node->next;
        free(old);
    }

    free(ht->nodes);

    return 0;
}


// Double indirection allows for modification of cell link.
static inline struct HT_NODE **METH(HASHTABLE, get_cell)(struct HASHTABLE *ht, TYPE key) {
    return &ht->nodes[HASH(key)%ht->capacity];
}

// Double indirection allows for modification of node link.
static struct HT_NODE **METH(HASHTABLE, lookup_node)(struct HASHTABLE *ht, TYPE key) {
    struct HT_NODE **node = METH(HASHTABLE, get_cell)(ht, key);

    while (*node != NULL) {
        if (EQUAL((*node)->elem, key))
            break;
        else
            node = &(*node)->chain;
    }

    return node;
}


bool METH(HASHTABLE, lookup)(struct HASHTABLE *ht, TYPE key, TYPE *elem) {
    struct HT_NODE *node = *METH(HASHTABLE, lookup_node)(ht, key);

    if (node != NULL) {
        if (elem != NULL)
            *elem = node->elem;

        return true;
    } else {
        return false;
    }
}


static struct HT_NODE *METH(HASHTABLE, new_node)(TYPE elem) {
    struct HT_NODE *node = malloc(sizeof(struct HT_NODE));

    if (node == NULL)
        return NULL;

    node->prev = NULL;
    node->next = NULL;
    node->chain = NULL;

    node->elem = elem;

    return node;
}

static void METH(HASHTABLE, insert_node)(struct HASHTABLE *ht, struct HT_NODE *node) {
    struct HT_NODE **cell = METH(HASHTABLE, get_cell)(ht, node->elem);
    node->chain = *cell;
    *cell = node;

    node->prev = NULL;
    node->next = NULL;

    if (ht->head == NULL) {
        ht->head = node;
        ht->tail = node;
    } else {
        ht->tail->next = node;
        node->prev = ht->tail;
        ht->tail = node;
    }
}

static int METH(HASHTABLE, recapacity)(struct HASHTABLE *ht, size_t new_cap) {
    struct HT_NODE *node = ht->head;
    ht->capacity = new_cap;
    struct HT_NODE **new_nodes = realloc(ht->nodes, ht->capacity*sizeof(struct HT_NODE*));

    if (ht->nodes == NULL)
        return 1;
    else
        ht->nodes = new_nodes;

    ht->head = NULL;
    ht->tail = NULL;
    memset(ht->nodes, 0, ht->capacity*sizeof(struct HT_NODE*));

    while (node != NULL) {
        struct HT_NODE *old = node;
        node = node->next;
        METH(HASHTABLE, insert_node)(ht, old);
    }

    return 0;
}


int METH(HASHTABLE, insert)(struct HASHTABLE *ht, TYPE elem) {
    struct HT_NODE *node = *METH(HASHTABLE, lookup_node)(ht, elem);

    if (node != NULL) {
        node->elem = elem;
    } else {
        if (ht->size == ht->capacity) {
            if (METH(HASHTABLE, recapacity(ht, 2*ht->capacity)) != 0)
                return 1;
        }

        node = METH(HASHTABLE, new_node)(elem);
        if (node == NULL)
            return 1;

        METH(HASHTABLE, insert_node)(ht, node);

        ht->size++;
    }

    return 0;
}


bool METH(HASHTABLE, delete)(struct HASHTABLE *ht, TYPE key, TYPE *elem) {
    struct HT_NODE **node_ptr = METH(HASHTABLE, lookup_node)(ht, key);
    struct HT_NODE *node = *node_ptr;

    if (node == NULL)
        return false;

    if (elem != NULL)
        *elem = node->elem;

    *node_ptr = node->chain;

    if (ht->head == node)
        ht->head = node->next;

    if (ht->tail == node)
        ht->tail = node->prev;

    if (node->prev != NULL)
        node->prev->next = node->next;

    if (node->next != NULL)
        node->next->prev = node->prev;

    free(node);

    return true;
}


#undef HASHTABLE
#undef HT_NODE

