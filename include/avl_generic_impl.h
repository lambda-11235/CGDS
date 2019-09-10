
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

#define AVL_NODE GEN1(avl_node, TYPE_ABBREV)
#define AVL GEN1(avl, TYPE_ABBREV)


/* transforms
**   top-> node
**        /    \
**       A      B
**             / \
**            C   D
** to
**   top-> B
**        / \
**    node   D
**   /    \
**  A      C
*/
static void METH(AVL, rotate_left)(struct AVL_NODE **top, struct AVL_NODE *node) {
    *top = node->right;

    struct AVL_NODE *tmp = (*top)->left;
    (*top)->left = node;
    node->right = tmp;

    // Recalculate balance
    node->balance += (*top)->balance > 0 ? -2 : -1;
    (*top)->balance += node->balance < 0 ? -2 : -1;
}

/* transforms
**   top-> node
**        /    \
**       A      B
**      / \
**     C   D
** to
**   top-> A
**        / \
**       C   node
**          /    \
**         D      B
*/
static void METH(AVL, rotate_right)(struct AVL_NODE **top, struct AVL_NODE *node) {
    *top = node->left;

    struct AVL_NODE *tmp = (*top)->right;
    (*top)->right = node;
    node->left = tmp;

    // Recalculate balance
    node->balance += (*top)->balance < 0 ? 2 : 1;
    (*top)->balance += node->balance > 0 ? 2 : 1;
}


static void METH(AVL, rebalance)(struct AVL_NODE **top, struct AVL_NODE *node) {
    if (node->balance == -2) {
        if (node->left->balance == 1) {
            METH(AVL, rotate_left)(&node->left, node->left);
            METH(AVL, rotate_right)(top, node);
        } else {
            METH(AVL, rotate_right)(top, node);
        }
    } else if (node->balance == 2) {
        if (node->right->balance == -1) {
            METH(AVL, rotate_right)(&node->right, node->right);
            METH(AVL, rotate_left)(top, node);
        } else {
            METH(AVL, rotate_left)(top, node);
        }
    }
}


int METH(AVL, init)(struct AVL *avl) {
    avl->size = 0;
    avl->root = NULL;

    return 0;
}


static int METH(AVL, free_node)(struct AVL_NODE *node) {
    if (node == NULL)
        return 0;

    if (METH(AVL, free_node)(node->left) != 0)
        return 1;

    if (METH(AVL, free_node)(node->right) != 0)
        return 1;

    free(node);

    return 0;
}

int METH(AVL, free)(struct AVL *avl) {
    return METH(AVL, free_node)(avl->root);
}


bool METH(AVL, lookup)(struct AVL *avl, TYPE key, TYPE *elem) {
    struct AVL_NODE *node = avl->root;

    while (node != NULL) {
        int comp = COMPARE(key, node->elem);

        if (comp == 0) {
            if (elem != NULL)
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


static inline struct AVL_NODE *METH(AVL, new_node)(TYPE elem) {
    struct AVL_NODE *node = malloc(sizeof(struct AVL_NODE));

    if (node == NULL)
        return NULL;

    node->elem = elem;
    node->balance = 0;
    node->left = NULL;
    node->right = NULL;

    return node;
}

static int METH(AVL, insert_node)(struct AVL_NODE **top, struct AVL_NODE *node, TYPE elem) {
    int comp = COMPARE(elem, node->elem);

    // Add node and calculate new balance factor
    if (comp == 0) {
        node->elem = elem;
    } else if (comp < 0) {
        if (node->left == NULL) {
            node->left = METH(AVL, new_node)(elem);

            if (node->left == NULL)
                return 1;

            node->balance--;
        } else {
            char old_bal = node->left->balance;

            if (METH(AVL, insert_node)(&node->left, node->left, elem) != 0)
                return 1;

            // The idea here is that is the left didn't balance, then it must
            // have deepened.
            if (node->left->balance != old_bal && node->left->balance != 0)
                node->balance--;
        }
    } else {
        if (node->right == NULL) {
            node->right = METH(AVL, new_node)(elem);

            if (node->right == NULL)
                return 1;

            node->balance++;
        } else {
            char old_bal = node->right->balance;

            if (METH(AVL, insert_node)(&node->right, node->right, elem) != 0)
                return 1;

            // The idea here is that is the right didn't balance, then it must
            // have deepened.
            if (node->right->balance != old_bal && node->right->balance != 0)
                node->balance++;
        }
    }

    METH(AVL, rebalance)(top, node);

    return 0;
}

int METH(AVL, insert)(struct AVL *avl, TYPE elem) {
    if (avl->root == NULL) {
        avl->root = METH(AVL, new_node)(elem);
        avl->size++;
        return 0;
    } else if (METH(AVL, insert_node)(&avl->root, avl->root, elem) == 0) {
        avl->size++;
        return 0;
    } else {
        return 1;
    }
}


/**
 * Deletes the left-most node and returns a pointer to it in `left`.
 */
static void METH(AVL, delete_left)(struct AVL_NODE **top, struct AVL_NODE *node, struct AVL_NODE **left) {
    if (node->left == NULL) {
        *left = node;
        *top = node->right;
    } else {
        struct AVL_NODE *old_node = node->left;

        METH(AVL, delete_left)(&node->left, node->left, left);

        // The idea here is that that there are two cases.
        // 1. If the node pointer changed, then the child was deleted.
        // 2. If the node balanced, then it must have become shallower.
        if (old_node != node->left || node->left->balance == 0)
            node->balance++;

        METH(AVL, rebalance)(top, node);
    }
}

static bool METH(AVL, delete_node)(struct AVL_NODE **top, struct AVL_NODE *node, TYPE key, TYPE *elem) {
    if (node == NULL)
        return false;

    int comp = COMPARE(key, node->elem);

    // Remove node and calculate new balance factor
    if (comp == 0) {
        if (elem != NULL)
            *elem = node->elem;

        if (node->left == NULL) {
            *top = node->right;
        } else if (node->right == NULL) {
            *top = node->left;
        } else {
            if (node->right->left == NULL) {
                // Simple case: replace with right node
                node->right->left = node->left;
                *top = node->right;

                (*top)->balance = node->balance - 1;
            } else {
                // More complicated case: replace with left-most node of right
                // subtree.
                char old_bal = node->right->balance;

                METH(AVL, delete_left)(NULL, node->right, top);
                (*top)->left = node->left;
                (*top)->right = node->right;
                (*top)->balance = node->balance;

                if (old_bal != (*top)->right->balance && (*top)->right->balance == 0)
                    (*top)->balance--;
            }

            free(node);
        }
    } else if (comp < 0) {
        if (node->left == NULL) {
            return false;
        } else {
            char old_bal = node->left->balance;

            if (!METH(AVL, delete_node)(&node->left, node->left, key, elem))
                return false;

            // The idea here is that that there are two cases.
            // 1. If the node pointer is NULL, then the child was deleted.
            // 2. If the node balanced, then it must have become shallower.
            if (node->left == NULL || (old_bal != node->left->balance && node->left->balance == 0))
                node->balance++;
        }
    } else {
        if (node->right == NULL) {
            return false;
        } else {
            char old_bal = node->right->balance;

            if (!METH(AVL, delete_node)(&node->right, node->right, key, elem))
                return false;

            // The idea here is that that there are two cases.
            // 1. If the node pointer is NULL, then the child was deleted.
            // 2. If the node balanced, then it must have become shallower.
            if (node->right == NULL || (old_bal != node->right->balance && node->right->balance == 0))
                node->balance--;
        }
    }

    if (*top != NULL)
        METH(AVL, rebalance)(top, *top);

    return true;
}

bool METH(AVL, delete)(struct AVL *avl, TYPE key, TYPE *elem) {
    return METH(AVL, delete_node)(&avl->root, avl->root, key, elem);
}
