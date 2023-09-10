/*
Scrivere una funzione in linguaggio C che preso in input  un albero binario con n elementi valuti in tempo O(n) se l’albero è un ABR.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct treeNode{
    int data;
    struct treeNode *left;
    struct treeNode *right;
}TreeNode;

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL) {
        root = createNode(data);
    } else if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

TreeNode* createABR() {
    TreeNode* root = NULL;
    int data;
    char choice;

    do {
        printf("Inserisci un valore: ");
        scanf("%d", &data);
        root = insert(root, data);

        printf("Vuoi inserire un altro valore? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return root;
}

TreeNode *min(TreeNode *tree) {
    if (tree == NULL) return NULL;
    if (tree->left == NULL) return tree;

    return min(tree->left);
}

TreeNode *max(TreeNode *tree) {
    if (tree == NULL) return NULL;
    if (tree->right == NULL) return tree;

    return max(tree->right);
}

int is_binary_search_tree(TreeNode *tree) {
    if (tree == NULL) return 1;

    TreeNode *max_left_node = max(tree->left);                                // trovo il massimo valore del sottoalbero sinistro
    if (max_left_node != NULL && max_left_node->data > tree->data) return 0; // se il massimo valore è maggiore della radice allora non è un ABR

    TreeNode *min_right_node = min(tree->right);                                // trovo il minimo valore del sottoalbero destro
    if (min_right_node != NULL && min_right_node->data < tree->data) return 0; // se il minimo valore è minore della radice allora non è un ABR

    if (!(is_binary_search_tree(tree->left))) return 0;

    if (!(is_binary_search_tree(tree->right))) return 0;

    return 1;
}

int main(){
    TreeNode *root = createABR();

    if (is_binary_search_tree(root)){
        printf("L'albero e' un ABR\n");
    } else {
        printf("L'albero non e' un ABR\n");
    }
    

    return 0;
}