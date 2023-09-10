/*
Realizzare un menù a scelta multipla che permetta:
1. Creare un ABR di interi (senza valori uguali e tutti positivi);
2. Aggiungere un nodo ad un ABR;
3. Cercare un valore nell'ABR;
4. Cercare il minimo nell'ABR;
5. Cancellare un nodo dall'ABR;
6. Stampare gli elementi dell'ABR con una visita in ordine (post e pre).
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int data;
    struct treeNode *left;
    struct treeNode *right;
} TreeNode;

TreeNode *createNode(int data) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

TreeNode* insertNode(TreeNode* root, int data) {
    if (data <= 0) {
        printf("Il valore deve essere positivo. Inserimento annullato.\n");
        return root;
    }

    if (root == NULL) {
        return createNode(data);
    }

    if (data == root->data) {
        printf("Il valore esiste gia' nell'ABR. Inserimento annullato.\n");
        return root;
    }

    if (data < root->data) {
        if (root->left == NULL) {
            root->left = createNode(data);
        } else {
            root->left = insertNode(root->left, data);
        }
    } else {
        if (root->right == NULL) {
            root->right = createNode(data);
        } else {
            root->right = insertNode(root->right, data);
        }
    }

    return root;
}

TreeNode *searchNode(TreeNode *root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return searchNode(root->left, data);
    } else {
        return searchNode(root->right, data);
    }
}

TreeNode *findMinNode(TreeNode *root) {
    if (root == NULL || root->left == NULL) {
        return root;
    }

    return findMinNode(root->left);
}

TreeNode *findParent(TreeNode *root, int data) {
    if (root == NULL || (root->left != NULL && root->left->data == data) ||
        (root->right != NULL && root->right->data == data)) {
        return root;
    }

    if (data < root->data) {
        return findParent(root->left, data);
    } else {
        return findParent(root->right, data);
    }
}

TreeNode *deleteNode(TreeNode *root, int data) {
    if (root == NULL) {
        printf("Il nodo da eliminare non esiste nell'ABR. Eliminazione annullata.\n");
        return root;
    }

    TreeNode *parent = findParent(root, data); // Trova il padre del nodo da eliminare con una ricerca lineare così da evitare di fare due ricerche

    if (parent == NULL) {
        printf("Il nodo da eliminare non esiste nell'ABR. Eliminazione annullata.\n");
        return root;
    }

    TreeNode *nodeToDelete = NULL; // Nodo da eliminare (inizializzato a NULL per evitare un warning)

    if (parent->left != NULL && parent->left->data == data) {
        nodeToDelete = parent->left;
    } else {
        nodeToDelete = parent->right;
    }

    if (nodeToDelete->left == NULL && nodeToDelete->right == NULL) {
        // Caso 1: Il nodo da eliminare è una foglia, mi serve sapere il padre anche se è una foglia perché devo impostare il puntatore a NULL
        if (nodeToDelete == parent->left) { // Se il nodo da eliminare è il figlio sinistro
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(nodeToDelete);

    } else if (nodeToDelete->left != NULL && nodeToDelete->right != NULL) {
        // Caso 2: Il nodo da eliminare ha due figli, devo trovare il successore e sostituire il valore del nodo da eliminare con quello del successore
        TreeNode *successor = findMinNode(nodeToDelete->right);
        int successorData = successor->data;

        root = deleteNode(root, successorData);
        nodeToDelete->data = successorData;

    } else {
        // Caso 3: Il nodo da eliminare ha un solo figlio (sinistro o destro), devo sostituire il nodo da eliminare con il suo unico figlio
        TreeNode *child = (nodeToDelete->left != NULL) ? nodeToDelete->left : nodeToDelete->right;
        
        if (nodeToDelete == parent->left) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(nodeToDelete);
    }

    printf("Nodo eliminato.\n");
    return root;
}

void printInOrder(TreeNode *root) {
    if (root == NULL) {
        return;
    }

    printInOrder(root->left);
    printf("%d ", root->data);
    printInOrder(root->right);
}

void printPostOrder(TreeNode *root) {
    if (root == NULL) {
        return;
    }

    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d ", root->data);
}

void printPreOrder(TreeNode *root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->data);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void freeTree(TreeNode *root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    TreeNode *root = NULL;
    int choice;
    int value;

    do {
        printf("\nMenu:\n");
        printf("1. Creare un ABR di interi\n");
        printf("2. Aggiungere un nodo\n");
        printf("3. Cercare un valore\n");
        printf("4. Cercare il minimo\n");
        printf("5. Cancellare un nodo\n");
        printf("6. Stampare gli elementi con una visita in ordine\n");
        printf("0. Uscire\n");
        printf("Scelta: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("Uscita dal programma.\n");
                break;
            case 1:
                if (root != NULL) {
                    printf("L'ABR esiste gia'. Creazione annullata.\n");
                } else {
                    int n;
                    printf("Inserire il numero di nodi dell'ABR: ");
                    scanf("%d", &n);

                    if (n <= 0) {
                        printf("Il numero di nodi deve essere positivo.\n");
                        break;
                    }

                    printf("Inserire i valori dei nodi:\n");
                    for (int i = 0; i < n; i++) {
                        scanf("%d", &value);
                        if (value <= 0) {
                            printf(
                                "Il valore deve essere positivo. Inserimento annullato.\n");
                            break;
                        }
                        root = insertNode(root, value);
                    }

                    printf("ABR creato.\n");
                }
                break;
            case 2:
                if (root == NULL) {
                    printf("L'ABR non esiste. Aggiunta annullata.\n");
                } else {
                    printf("Inserire il valore del nodo da aggiungere: ");
                    scanf("%d", &value);

                    root = insertNode(root, value);
                    printf("Nodo aggiunto.\n");
                }
                break;
            case 3:
                if (root == NULL) {
                    printf("L'ABR non esiste. Ricerca annullata.\n");
                } else {
                    printf("Inserire il valore da cercare: ");
                    scanf("%d", &value);

                    TreeNode *result = searchNode(root, value);

                    if (result != NULL) {
                        printf("Il valore %d e' presente nell'ABR.\n", value);
                    } else {
                        printf("Il valore %d non e' presente nell'ABR.\n",
                               value);
                    }
                }
                break;
            case 4:
                if (root == NULL) {
                    printf("L'ABR non esiste. Ricerca annullata.\n");
                } else {
                    TreeNode *minNode = findMinNode(root);

                    if (minNode != NULL) {
                        printf("Il valore minimo nell'ABR e': %d\n",
                               minNode->data);
                    } else {
                        printf("L'ABR e' vuoto.\n");
                    }
                }
            case 5:
                if (root == NULL) {
                    printf("L'ABR non esiste. Cancellazione annullata.\n");
                } else {
                    printf("Inserire il valore del nodo da eliminare: ");
                    scanf("%d", &value);

                    root = deleteNode(root, value);
                }
                break;
            case 6:
                if (root == NULL) {
                    printf("L'ABR non esiste. Stampa annullata.\n");
                } else {
                    int printChoice;
                    printf("Scegli la modalita' di stampa:\n");
                    printf("1. InOrder\n");
                    printf("2. PostOrder\n");
                    printf("3. PreOrder\n");
                    printf("Scelta: ");
                    scanf("%d", &printChoice);

                    switch (printChoice) {
                        case 1:
                            printf(
                                "Elementi dell'ABR con una visita in InOrder: ");
                            printInOrder(root);
                            printf("\n");
                            break;
                        case 2:
                            printf(
                                "Elementi dell'ABR con una visita in PostOrder: ");
                            printPostOrder(root);
                            printf("\n");
                            break;
                        case 3:
                            printf(
                                "Elementi dell'ABR con una visita in PreOrder: ");
                            printPreOrder(root);
                            printf("\n");
                            break;
                        default:
                            printf("Scelta non valida. Riprovare.\n");
                            break;
                    }
                }
                break;

            default:
                printf("Scelta non valida. Riprovare.\n");
        }
    } while (choice != 0);

    freeTree(root);

    return 0;
}