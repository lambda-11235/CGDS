

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

// Establishes a partial ordering over TYPE.
// COMPARE(a, b) < 0 if a < b
// COMPARE(a, b) = 0 if a == b
// COMPARE(a, b) > 0 if a > b
// Note that defining COMPARE as (a.x - b.x) and ignoring other members is
// acceptable. In fact, it's the preferred way to implement maps. Compare must
// also be bounded by the int type.
#ifndef COMPARE
#error "Expected macro COMPARE to be defined"
#endif

#define AVL_NODE GEN1(avl_node, TYPE)
#define AVL GEN1(avl, TYPE)


// transforms
//   top-> node
//        /    \
//       A      B
//             / \
//            C   D
// to
//   top-> B
//        / \
//    node   D
//   /    \
//  A      C
static void rotate_left(struct AVL_NODE **top, struct AVL_NODE *node) {
    *top = node->right;

    struct AVL_NODE *tmp = (*top)->left;
    (*top)->left = node;
    node->right = tmp;

    // TODO: Recalc balance
}

// transforms
//   top-> node
//        /    \
//       A      B
//      / \
//     C   D
// to
//   top-> A
//        / \
//       C   node
//          /    \
//         D      B
static void rotate_right(struct AVL_NODE **top, struct AVL_NODE *node) {
    *top = node->left;

    struct AVL_NODE *tmp = (*top)->right;
    (*top)->right = node;
    node->left = tmp;

    // TODO: Recalc balance
}


int METH(AVL, init)(struct AVL *avl) {
    avl->size = 0;
    avl->root = NULL;

    return 0;
}


static int free_node(struct AVL_NODE *node) {
    if (node->left != NULL) {
        if (free_node(node->left) != 0)
            return 1;
    }

    if (node->right != NULL) {
        if (free_node(node->right) != 0)
            return 1;
    }

    free(node);

    return 0;
}

int METH(AVL, free)(struct AVL *avl) {
    return free_node(avl->root);
}


bool METH(AVL, lookup)(struct AVL *avl, TYPE key, TYPE *elem) {
    struct AVL_NODE *node = avl->root;

    while (node != NULL) {
        int comp = COMPARE(key, node->elem);

        if (comp == 0) {
                *elem = node->elem;
                return true;
        } else if (comp < 0) {
                node = node->left;
        } else {
                node = node->right;
        }
    }

    return false;
}


static inline struct AVL_NODE *new_node(TYPE elem) {
    struct AVL_NODE *node = malloc(sizeof(struct AVL_NODE));

    if (node == NULL)
        return NULL;

    node->elem = elem;
    node->elem = NULL;
    node->elem = NULL;

    return node;
}

static int insert_node(struct AVL_NODE **top, struct AVL_NODE *node, TYPE elem) {
    int comp = COMPARE(key, node->elem);

    // Add node and calculate new balance factor
    if (comp == 0) {
        node->elem = elem;
    } else if (comp < 0) {
        if (node->left == NULL) {
            node->left = new_node(elem);

            if (node->left == NULL)
                return 1;

            node->balance--;
        } else if (insert_node(&node->left, node->left, elem) == 0) {
            // The idea here is that is the left didn't balance, then it must
            // have deepened.
            if (node->left->balance != 0)
                node->balance--;
        } else {
            return 1;
        }
    }
    } else {
        if (node->right == NULL) {
            node->right = new_node(elem);

            if (node->right == NULL)
                return 1;

            node->balance++;
        } else if (insert_node(&node->right, node->right, elem) == 0) {
            // The idea here is that is the right didn't balance, then it must
            // have deepened.
            if (node->right->balance != 0)
                node->balance++;
        } else {
            return 1;
        }
    }

    // Rebalance
    if (node->balance == -2) {
        if (node->left->balance == -1) {
            // TODO
        } else if (node->left->balance == 1) {
            // TODO
        }
    } else if (node->balance == 2) {
        if (node->right->balance == -1) {
            // TODO
        } else if (node->right->balance == 1) {
            // TODO
        }
    }

    return 0;
}

int METH(AVL, insert)(struct AVL *avl, TYPE elem) {
    if (insert_node(&avl->root, avl->root) == 0) {
        avl->size++;
        return 0;
    } else {
        return 1;
    }
}


bool METH(AVL, delete)(struct AVL *avl, TYPE key, TYPE *elem);
    return 0;
}
