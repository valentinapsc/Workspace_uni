#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node *next;
};

typedef struct Node *typeList;

//stampa di una lista di lunghezza generica

void displayList(typeList head) {
    typeList temp;

    temp = head;
    while (temp != NULL) {
        printf("%d-> ", (*temp).val);
        temp = (*temp).next;
    }

    printf("NULL");
    printf("\n");
}

/*
  aggiunta di un elemento in testa alla lista
*/

void insertHead(typeList *head, int elem) {
    typeList temp;

    temp = malloc(sizeof(struct Node));
    (*temp).val = elem;
    (*temp).next = *head;

    *head = temp;
}

int main() {
    FILE *fptr;
    int res;
    int elem;

    typeList head;

    /* apre il file */
    fptr = fopen("lista.txt", "r");
    if (fptr == NULL) {
        perror("");
        exit(1);
    }

    /* inizializza la lista */
    head = NULL;

    /* legge fino alla fine del file */
    while (1) {
        res = fscanf(fptr, "%d", &elem);
        if (res != 1) break;

        insertHead(&head, elem);
    }

    fclose(fptr);

    displayList(head);

    return 0;
}
