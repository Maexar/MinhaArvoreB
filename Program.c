#include "superBiblioteca.h"

void printTree(BTreeNode *node, int level) {
    int i;
    for (i = 0; i < node->n; i++) {
        if (!node->leaf) {
            printTree(node->children[i], level + 1);
        }
        for (int j = 0; j < level; j++) {
            printf("   ");
        }
        printf("%d\n", node->keys[i]);
    }
    if (!node->leaf) {
        printTree(node->children[i], level + 1);
    }
}

int main() {
    BTree *tree = createTree();
    int choice, key;
    
    while (1) {
        printf("\n1. Inserir\n2. Buscar\n3. Remover\n4. Imprimir Arvore\n5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite a chave a ser inserida: ");
                scanf("%d", &key);
                insert(tree, key);
                printf("Chave %d inserida.\n", key);
                break;
            case 2:
                printf("Digite a chave a ser buscada: ");
                scanf("%d", &key);
                if (search(tree->root, key) != NULL) {
                    printf("Chave %d encontrada.\n", key);
                } else {
                    printf("Chave %d nao encontrada.\n", key);
                }
                break;
            case 3:
                printf("Digite a chave a ser removida: ");
                scanf("%d", &key);
                removeKey(tree, key);
                printf("Chave %d removida.\n", key);
                break;
            case 4:
                printf("Arvore B:\n");
                printTree(tree->root, 0);
                break;
            case 5:
                exit(0);
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }

    return 0;
}

