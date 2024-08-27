#ifndef BUSCA_H
#define BUSCA_H

#include "superBiblioteca.h"

BTreeNode* search(BTreeNode *node, int key) {
    int i = 0;
    while (i < node->n && key > node->keys[i]) {
        i++;
    }

    if (i < node->n && key == node->keys[i]) {
        return node; // Chave encontrada
    }

    if (node->leaf) {
        return NULL; // Chave não encontrada
    }

    return search(node->children[i], key); // Recorre para o filho apropriado
}


#endif