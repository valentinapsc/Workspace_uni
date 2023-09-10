#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;

node* create_node(int data) {
    node* new_node = (node*)malloc(sizeof(node));

    if (new_node == NULL) {
        perror("Errore durante l'allocazione di memoria");
        exit(EXIT_FAILURE);
    }

    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_node(node** head, int data) {
    node* new_node = create_node(data);

    if (*head == NULL) {
        *head = new_node;
    } else {
        node* tmp = *head;

        while (tmp->next != NULL) {
            tmp = tmp->next;
        }

        tmp->next = new_node;
    }
}

void remove_occurrences(node** head, int key) {
    node* current = *head;
    node* prev = NULL;

    while (current != NULL) {
        if (current->data == key) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }

            node* tmp = current;
            current = current->next;
            free(tmp);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

int count_occurrences(node* head, int key) {
    int count = 0;
    node* current = head;

    while (current != NULL) {
        if (current->data == key) {
            count++;
        }
        current = current->next;
    }

    return count;
}

void print_list(node* head) {
    node* current = head;

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(node* head) {
    node* current = head;

    while (current != NULL) {
        node* tmp = current;
        current = current->next;
        free(tmp);
    }
}

int main() {
    node* l1 = NULL;
    node* l2 = NULL;

    int num;

    printf("Inserire nodi per L1 (0 per terminare):\n");
    while (1) {
        scanf("%d", &num);
        if (num == 0) {
            break;
        }

        insert_node(&l1, num);
    }

    printf("L1: ");
    print_list(l1);

    int count = count_occurrences(l1, 2);
    remove_occurrences(&l1, 2);

    insert_node(&l2, count);

    printf("L1 dopo: ");
    print_list(l1);
    printf("L2: ");
    print_list(l2);

    free_list(l1);
    free_list(l2);

    return 0;
}
