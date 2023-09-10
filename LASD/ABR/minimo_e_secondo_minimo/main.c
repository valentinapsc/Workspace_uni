/*
Dato un ABR, trovare il minimo ed il secondo minimo del sottoalbero radicato in
k, e poi rimuovere il secondo minimo mantenendo le proprietà di ABR
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int data;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

treeNode *create_node(int data) {
    treeNode *new_node = (treeNode *)malloc(sizeof(treeNode));

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

treeNode *insert_node(treeNode *root, int data) {
    if (data <= 0) {
        printf("Il valore deve essere positivo. Inserimento annullato.\n");
        return root;
    }

    if (root == NULL) {
        return create_node(data);
    }

    if (data == root->data) {
        printf("Il valore esiste gia' nell'ABR. Inserimento annullato.\n");
        return root;
    }

    if (data < root->data) {
        if (root->left == NULL) {
            root->left = create_node(data);
        } else {
            root->left = insert_node(root->left, data);
        }
    } else {
        if (root->right == NULL) {
            root->right = create_node(data);
        } else {
            root->right = insert_node(root->right, data);
        }
    }

    return root;
}

treeNode *find_min(treeNode *root) {
    if (root == NULL) return NULL;
    if (root->left == NULL) return root;

    return find_min(root->left);
}

treeNode* find_second_min(treeNode* root, int k) {
    if (root == NULL || root->data == k) return NULL;

    if (root->data < k) {
        return find_second_min(root->right, k);
    }

    treeNode* secondMin = find_second_min(root->left, k);
    if (secondMin == NULL || root->data < secondMin->data) {
        secondMin = root;
    }

    return secondMin;
}

treeNode* delete(treeNode* root, int data) {
    if (root == NULL) return NULL;

    if (root->data < data) {
        root->right = delete(root->right, data);

    } else if (root->data > data) {
        root->left = delete(root->left, data);

    } else {
        if (root->left == NULL) {
            treeNode* temp = root->right;
            free(root);
            return temp;

        } else if (root->right == NULL) {
            treeNode* temp = root->left;
            free(root);
            return temp;
        }

        treeNode* min = find_min(root->right);
        root->data = min->data;
        root->right = delete(root->right, min->data);
    }

    return root;
}

void print_in_order(treeNode *tree) {
    if (tree == NULL) return;

    print_in_order(tree->left);
    printf("%d ", tree->data);
    print_in_order(tree->right);
}

int main() {
    treeNode* root = NULL;
    int data;
    int k;

    // Inserimento degli elementi dell'ABR da tastiera
    printf("Inserisci gli elementi dell'ABR (-1 per terminare):\n");
    while (1) {
        scanf("%d", &data);
        if (data == -1) {
            break;
        }
        root = insert_node(root, data);
    }

    // Inserisci il nodo radice del sottoalbero
    printf("Inserisci il nodo radice del sottoalbero: ");
    scanf("%d", &k);

    // Stampa il minimo e il secondo minimo
    printf("Minimo: %d\n", find_min(root)->data);

    // Trova il secondo minimo
    treeNode* secondMin = find_second_min(root, k);

    if (secondMin == NULL) {
        printf("Nessun secondo minimo trovato nel sottoalbero radicato in %d\n", k);
        return 0;
    }

    printf("Secondo minimo: %d\n", secondMin->data);

    // Rimuovi il secondo minimo
    root = delete(root, secondMin->data);

    // Stampa l'ABR aggiornato
    printf("ABR dopo la rimozione del secondo minimo: ");
    print_in_order(root);
    printf("\n");

    return 0;
}