#include <stdio.h>
#include <stdlib.h>

typedef struct btree {
    int key;
    struct btree *left;
    struct btree *right;
} btree;

btree* createNode(int key) {
    btree *newNode = (btree*)malloc(sizeof(btree));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

btree* mergeTrees(btree *t1, btree *t2) {
    if (t1 == NULL)
        return t2;
    if (t2 == NULL)
        return t1;

    btree *mergedTree = createNode(0);
    mergedTree->left = mergeTrees(t1, t2->left);
    mergedTree->key = t2->key;

    return mergedTree;
}

void printInorder(btree *root) {
    if (root != NULL) {
        printInorder(root->left);
        printf("%d ", root->key);
        printInorder(root->right);
    }
}

void freeTree(btree *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    btree *root1 = createNode(1);
    root1->left = createNode(2);
    root1->right = createNode(3);

    btree *root2 = createNode(4);
    root2->left = createNode(5);
    root2->right = createNode(6);

    btree *mergedTree = mergeTrees(root1, root2);
    printf("Inorder traversal of root1: ");
    printInorder(root1);
    printf("\n");

    printf("Inorder traversal of root2: ");
    printInorder(root2);
    printf("\n");

    printf("Inorder traversal of the merged tree: ");
    printInorder(mergedTree);
    printf("\n");

    freeTree(mergedTree);

    return 0;
}
