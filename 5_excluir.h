#ifndef EXCLUIR_H
#define EXCLUIR_H

#include "superBiblioteca.h"

void removeKey(BTree *tree, int key) {
    BTreeNode *root = tree->root;

    removeFromNode(root, key);

    if (root->n == 0) {
        BTreeNode *tmp = root;
        if (!root->leaf) {
            root = root->children[0];
        } else {
            root = NULL;
        }
        free(tmp);
        tree->root = root;
    }
}

void removeFromNode(BTreeNode *node, int key) {
    int idx = findKey(node, key);

    if (idx < node->n && node->keys[idx] == key) {
        if (node->leaf) {
            removeFromLeaf(node, idx);
        } else {
            removeFromNonLeaf(node, idx);
        }
    } else {
        if (node->leaf) {
            return;
        }

        int flag = (idx == node->n) ? 1 : 0;

        if (node->children[idx]->n < D) {
            fill(node, idx);
        }

        if (flag && idx > node->n) {
            removeFromNode(node->children[idx - 1], key);
        } else {
            removeFromNode(node->children[idx], key);
        }
    }
}

void removeFromLeaf(BTreeNode *node, int idx) {
    for (int i = idx + 1; i < node->n; i++) {
        node->keys[i - 1] = node->keys[i];
    }
    node->n--;
}

void removeFromNonLeaf(BTreeNode *node, int idx) {
    int key = node->keys[idx];

    if (node->children[idx]->n >= D) {
        int pred = getPredecessor(node, idx);
        node->keys[idx] = pred;
        removeFromNode(node->children[idx], pred);
    } else if (node->children[idx + 1]->n >= D) {
        int succ = getSuccessor(node, idx);
        node->keys[idx] = succ;
        removeFromNode(node->children[idx + 1], succ);
    } else {
        merge(node, idx);
        removeFromNode(node->children[idx], key);
    }
}

void fill(BTreeNode *node, int idx) {
    if (idx != 0 && node->children[idx - 1]->n >= D) {
        borrowFromPrev(node, idx);
    } else if (idx != node->n && node->children[idx + 1]->n >= D) {
        borrowFromNext(node, idx);
    } else {
        if (idx != node->n) {
            merge(node, idx);
        } else {
            merge(node, idx - 1);
        }
    }
}

void borrowFromPrev(BTreeNode *node, int idx) {
    BTreeNode *child = node->children[idx];
    BTreeNode *sibling = node->children[idx - 1];

    for (int i = child->n - 1; i >= 0; i--) {
        child->keys[i + 1] = child->keys[i];
    }

    if (!child->leaf) {
        for (int i = child->n; i >= 0; i--) {
            child->children[i + 1] = child->children[i];
        }
    }

    child->keys[0] = node->keys[idx - 1];

    if (!node->leaf) {
        child->children[0] = sibling->children[sibling->n];
    }

    node->keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}

void borrowFromNext(BTreeNode *node, int idx) {
    BTreeNode *child = node->children[idx];
    BTreeNode *sibling = node->children[idx + 1];

    child->keys[child->n] = node->keys[idx];

    if (!(child->leaf)) {
        child->children[child->n + 1] = sibling->children[0];
    }

    node->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; i++) {
        sibling->keys[i - 1] = sibling->keys[i];
    }

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; i++) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }

    child->n += 1;
    sibling->n -= 1;
}

void merge(BTreeNode *node, int idx) {
    BTreeNode *child = node->children[idx];
    BTreeNode *sibling = node->children[idx + 1];

    child->keys[D - 1] = node->keys[idx];

    for (int i = 0; i < sibling->n; i++) {
        child->keys[i + D] = sibling->keys[i];
    }

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; i++) {
            child->children[i + D] = sibling->children[i];
        }
    }

    for (int i = idx + 1; i < node->n; i++) {
        node->keys[i - 1] = node->keys[i];
    }

    for (int i = idx + 2; i <= node->n; i++) {
        node->children[i - 1] = node->children[i];
    }

    child->n += sibling->n + 1;
    node->n--;

    free(sibling);
}

int getPredecessor(BTreeNode *node, int idx) {
    BTreeNode *current = node->children[idx];
    while (!current->leaf) {
        current = current->children[current->n];
    }
    return current->keys[current->n - 1];
}

int getSuccessor(BTreeNode *node, int idx) {
    BTreeNode *current = node->children[idx + 1];
    while (!current->leaf) {
        current = current->children[0];
    }
    return current->keys[0];
}

int findKey(BTreeNode *node, int key) {
    int idx = 0;
    while (idx < node->n && node->keys[idx] < key) {
        ++idx;
    }
    return idx;
}


#endif