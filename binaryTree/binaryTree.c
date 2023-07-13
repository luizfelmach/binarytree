#include <binaryTree.h>
#include <deque.h>

typedef struct BinaryTreeNode {
    void                  *data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
    struct BinaryTreeNode *parent;
} BinaryTreeNode;

BinaryTreeNode *binaryTreeNode(void *data, BinaryTreeNode *parent, BinaryTreeNode *left,
                               BinaryTreeNode *right) {
    BinaryTreeNode *btn = calloc(1, sizeof(BinaryTreeNode));
    btn->data           = data;
    btn->left           = left;
    btn->right          = right;
    btn->parent         = parent;
    return btn;
}

void binaryTreeNodeDestroy(BinaryTreeNode *btn) {
    free(btn);
}

void _nothing(void *x) {
}

struct _binaryTree {
    BinaryTreeNode     *root;
    binaryTreeCompareFn compare;
    binaryTreeDestroyFn destroy;
};

BinaryTree binaryTree(binaryTreeCompareFn compare, binaryTreeDestroyFn destroy) {
    BinaryTree bt = calloc(1, sizeof(struct _binaryTree));
    bt->root      = NULL;
    bt->compare   = compare;
    bt->destroy   = destroy;
    return bt;
}

void _binaryTreeDestroyRecursive(BinaryTree bt, BinaryTreeNode *node) {
    if (node == NULL) return;
    bt->destroy(node->data);
    _binaryTreeDestroyRecursive(bt, node->left);
    _binaryTreeDestroyRecursive(bt, node->right);
    binaryTreeNodeDestroy(node);
}

void binaryTreeDestroy(BinaryTree bt) {
    _binaryTreeDestroyRecursive(bt, bt->root);
    free(bt);
}

BinaryTreeNode *_binaryTreeSetRecursive(BinaryTree bt, BinaryTreeNode *node, void *data) {
    if (!node) {
        return binaryTreeNode(data, node, NULL, NULL);
    }
    if (bt->compare(data, node->data) < 0) {
        node->left = _binaryTreeSetRecursive(bt, node->left, data);
    } else if (bt->compare(data, node->data) > 0) {
        node->right = _binaryTreeSetRecursive(bt, node->right, data);
    } else {
        bt->destroy(node->data);
        node->data = data;
    }
    return node;
}

void binaryTreeSet(BinaryTree bt, void *data) {
    bt->root = _binaryTreeSetRecursive(bt, bt->root, data);
}

void *_binaryTreeGetRecursive(BinaryTree bt, BinaryTreeNode *node, void *data) {
    if (!node) return NULL;
    if (bt->compare(data, node->data) < 0) {
        return _binaryTreeGetRecursive(bt, node->left, data);
    } else if (bt->compare(data, node->data) > 0) {
        return _binaryTreeGetRecursive(bt, node->right, data);
    }
    return node->data;
}

void *binaryTreeGet(BinaryTree bt, void *data) {
    return _binaryTreeGetRecursive(bt, bt->root, data);
}

void *binaryTreePop(BinaryTree bt, void *data) {
    return NULL;
}

int binaryTreeEmpty(BinaryTree bt) {
    return bt->root == NULL;
}

void *_binaryTreeMaxRecursive(BinaryTree bt, BinaryTreeNode *node) {
    if (!node)
        return NULL;
    else
        return node->data;
    return _binaryTreeMaxRecursive(bt, node->right);
}

void *binaryTreeMax(BinaryTree bt) {
    BinaryTreeNode *target = bt->root;
    while (target) {
        if (!target->right) break;
        target = target->right;
    }
    return target->data;
}

void *binaryTreeMaxPop(BinaryTree bt) {
    void           *data   = NULL;
    BinaryTreeNode *target = bt->root;
    BinaryTreeNode *parent = NULL;
    while (target) {
        if (!target->right) {
            break;
        }
        parent = target;
        target = target->right;
    }
    data = target->data;
    if (parent) {
        parent->right = target->left;
    } else {
        bt->root = target->left;
    }
    binaryTreeNodeDestroy(target);
    return data;
}

void *binaryTreeMin(BinaryTree bt) {
    BinaryTreeNode *target = bt->root;
    while (target) {
        if (!target->left) break;
        target = target->left;
    }
    return target->data;
}

void *binaryTreeMinPop(BinaryTree bt) {
    void           *data   = NULL;
    BinaryTreeNode *target = bt->root;
    BinaryTreeNode *parent = NULL;
    while (target) {
        if (!target->left) {
            break;
        }
        parent = target;
        target = target->left;
    }
    data = target->data;
    if (parent) {
        parent->left = target->right;
    } else {
        bt->root = target->right;
    }
    binaryTreeNodeDestroy(target);
    return data;
}

void binaryTreeTraversalIn(BinaryTree bt, Vector traversal) {
    Deque nodes = deque(_nothing);
    // dequePushBack(nodes, bt->root);
    BinaryTreeNode *node = bt->root;
    while (1) {
        while (node) {
            dequePushBack(nodes, node);
            node = node->left;
        }
        if (dequeSize(nodes) == 0)
            break;
        else {
            BinaryTreeNode *btn = dequePopBack(nodes);
            vectorPush(traversal, btn->data);
            node = btn->right;
        }
    }
    dequeDestroy(nodes);
}

void binaryTreeTraversalPre(BinaryTree bt, Vector traversal) {
    Deque nodes = deque(_nothing);
    dequePushBack(nodes, bt->root);
    while (dequeSize(nodes) != 0) {
        BinaryTreeNode *btn = dequePopBack(nodes);
        vectorPush(traversal, btn->data);
        if (btn->right) {
            dequePushBack(nodes, btn->right);
        }
        if (btn->left) {
            dequePushBack(nodes, btn->left);
        }
    }
    dequeDestroy(nodes);
}

void binaryTreeTraversalPost(BinaryTree bt, Vector traversal) {
    Deque q1 = deque(_nothing);
    Deque q2 = deque(_nothing);
    dequePushBack(q1, bt->root);
    while (dequeSize(q1) != 0) {
        BinaryTreeNode *btn = dequePopBack(q1);
        if (btn->left) {
            dequePushBack(q1, btn->left);
        }
        if (btn->right) {
            dequePushBack(q1, btn->right);
        }
        dequePushBack(q2, btn);
    }
    while (dequeSize(q2) != 0) {
        BinaryTreeNode *btn = dequePopBack(q2);
        vectorPush(traversal, btn->data);
    }
    dequeDestroy(q1);
    dequeDestroy(q2);
}

void binaryTreeTraversalLevel(BinaryTree bt, Vector traversal) {
    Deque nodes = deque(_nothing);
    dequePushBack(nodes, bt->root);
    while (dequeSize(nodes) != 0) {
        BinaryTreeNode *btn = dequePopFront(nodes);
        vectorPush(traversal, btn->data);
        if (btn->left) {
            dequePushBack(nodes, btn->left);
        }
        if (btn->right) {
            dequePushBack(nodes, btn->right);
        }
    }
    dequeDestroy(nodes);
}

void _binaryTreeTraversalInRecursive(BinaryTreeNode *node, Vector traversal) {
    if (!node) return;
    _binaryTreeTraversalInRecursive(node->left, traversal);
    vectorPush(traversal, node->data);
    _binaryTreeTraversalInRecursive(node->right, traversal);
}

void binaryTreeTraversalInRecursive(BinaryTree bt, Vector traversal) {
    _binaryTreeTraversalInRecursive(bt->root, traversal);
}

void _binaryTreeTraversalPreRecursive(BinaryTreeNode *node, Vector traversal) {
    if (!node) return;
    vectorPush(traversal, node->data);
    _binaryTreeTraversalPreRecursive(node->left, traversal);
    _binaryTreeTraversalPreRecursive(node->right, traversal);
}

void binaryTreeTraversalPreRecursive(BinaryTree bt, Vector traversal) {
    _binaryTreeTraversalPreRecursive(bt->root, traversal);
}

void _binaryTreeTraversalPostRecursive(BinaryTreeNode *node, Vector traversal) {
    if (!node) return;
    _binaryTreeTraversalPostRecursive(node->left, traversal);
    _binaryTreeTraversalPostRecursive(node->right, traversal);
    vectorPush(traversal, node->data);
}

void binaryTreeTraversalPostRecursive(BinaryTree bt, Vector traversal) {
    _binaryTreeTraversalPostRecursive(bt->root, traversal);
}
