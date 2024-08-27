#ifndef INSERIR_H
#define INSERIR_H

#include "superBiblioteca.h"


BTree* createTree() {
    BTree *tree = (BTree*)malloc(sizeof(BTree));
    tree->root = createNode(1); // Inicialmente, a raiz é uma folha
    return tree;
}

BTreeNode* createNode(int leaf) {
    BTreeNode *node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->n = 0;
    node->leaf = leaf;
    for (int i = 0; i < 2 * D + 1; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void insert(BTree *tree, int key) {
    BTreeNode *root = tree->root;

    if (root->n == 2 * D) {
        BTreeNode *newRoot = createNode(0);
        newRoot->children[0] = root;
        splitChild(newRoot, 0, root);
        insertNonFull(newRoot, key);
        tree->root = newRoot;
    } else {
        insertNonFull(root, key);
    }
}

void insertNonFull(BTreeNode *node, int key) {
    int i = node->n - 1;

    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->n += 1;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        if (node->children[i]->n == 2 * D) {
            splitChild(node, i, node->children[i]);

            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

void splitChild(BTreeNode *parent, int i, BTreeNode *child) {
    BTreeNode *newChild = createNode(child->leaf);
    newChild->n = D;

    for (int j = 0; j < D; j++) {
        newChild->keys[j] = child->keys[j + D];
    }

    if (!child->leaf) {
        for (int j = 0; j < D + 1; j++) {
            newChild->children[j] = child->children[j + D];
        }
    }

    child->n = D;

    for (int j = parent->n; j >= i + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }

    parent->children[i + 1] = newChild;

    for (int j = parent->n - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }

    parent->keys[i] = child->keys[D];
    parent->n += 1;
}



#endif