#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void deallocate(Node** head) {
    Node* current = *head;
    while (current != NULL) {
        Node* tmp = current;
        current = current->next;
        free(tmp);
    }
    *head = NULL;
}

void insert_end(Node** head, int value) {
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(1);
    }
    new_node->next = NULL;
    new_node->data = value;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void serialize(Node* head) {
    FILE* file = fopen("list.txt", "w");
    if (file == NULL) {
        exit(1);
    }

    for (Node* current = head; current != NULL; current = current->next) {
        fprintf(file, "%d -> ", current->data);
    }

    fclose(file);
}

void deserialize(Node** head) {
    FILE* file = fopen("list.txt", "r");

    if (file == NULL) {
        exit(2);
    }

    int val;
    
    while (fscanf(file, "%d, ", &val) > 0) {
        insert_end(head, val);
    }
    fclose(file);
}

int main(int argc, char* argv[]) {
    Node* head = NULL;

     insert_end(&head, -2);
     insert_end(&head, 11);
     insert_end(&head, 22);

     serialize(head);
    //deserialize(&head);

    for (Node* current = head; current != NULL; current = current->next) {
        printf("%d\n", current->data);
    }
    printf("NULL");

    deallocate(&head);

    return 0;
}