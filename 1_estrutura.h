#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#define D 2

typedef struct BTreeNode {
    int n;                     // Número de chaves no nó
    int keys[2 * D];           // Armazena as chaves
    struct BTreeNode *children[2 * D + 1]; // Ponteiros para os filhos
    int leaf;                  // 1 se for folha, 0 se não for
} BTreeNode;

typedef struct BTree {
    BTreeNode *root;
} BTree;

BTree* createTree();
BTreeNode* createNode(int leaf);
void insert(BTree *tree, int key);
void insertNonFull(BTreeNode *node, int key);
void splitChild(BTreeNode *parent, int i, BTreeNode *child);
BTreeNode* search(BTreeNode *node, int key);
void removeKey(BTree *tree, int key);


#endif