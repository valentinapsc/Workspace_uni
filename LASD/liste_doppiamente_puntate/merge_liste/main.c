/*
(struct già data) avendo due liste l1 e l2  doppiamente puntate non circolari e
ordinate fare una funzione che ne fa il merge creando una terza lista l3 ancora
ordinata
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct el {
    struct el* prev;
    int inf;
    struct el* next;
}El;

El* newNode(int data) {
    El* newEl = (El*)malloc(sizeof(El));
    newEl->prev = NULL;
    newEl->inf = data;
    newEl->next = NULL;
    return newEl;
}

El* mergeLists(El* L1, El* L2) {
    if (L1 == NULL)
        return L2;
    if (L2 == NULL)
        return L1;

    // se l'elemento della prima lista è minore o uguale all'elemento della seconda lista
    if (L1->inf <= L2->inf) {
        L1->next = mergeLists(L1->next, L2); // richiamo ricorsivamente la funzione passando come primo parametro la coda della prima lista e come secondo parametro la seconda lista
        L1->next->prev = L1; // il puntatore al nodo precedente del nodo successivo del nodo corrente della prima lista punta al nodo corrente
        L1->prev = NULL; // il puntatore al nodo precedente del nodo corrente della prima lista punta a NULL
        return L1;
    } else {
    // se l'elemento della seconda lista è minore dell'elemento della prima lista 
        L2->next = mergeLists(L1, L2->next);
        L2->next->prev = L2;
        L2->prev = NULL;
        return L2;
    }
}

void freeList(El* head) {
    El* current = head;
    while (current != NULL) {
        El* temp = current;
        current = current->next;
        free(temp);
    }
}

int insert(El** head) {
    int input;
    int prevElement = -1;

    while (1) {
        scanf("%d", &input);
        if (input < 0)
            break;
        if (input < prevElement) {
            printf("Errore: la lista non e' ordinata.\n");
            freeList(*head);
            return 0;
        }
        El* newEl = newNode(input);
        if (*head == NULL) {
            *head = newEl;
        } else {
            El* current = *head;
            while (current->next != NULL)
                current = current->next;
            current->next = newEl;
            newEl->prev = current;
        }
        prevElement = input;
    }
    return 1;
}

void printList(El* head) {
    El* current = head;
    while (current != NULL) {
        printf("%d ", current->inf);
        current = current->next;
    }
    printf("\n");
}

int main() {
    El* L1 = NULL;
    El* L2 = NULL;

    printf("Inserisci gli elementi per la lista L1 (termina con un valore negativo):\n");
    if (!insert(&L1))
        return 0;

    printf("Inserisci gli elementi per la lista L2 (termina con un valore negativo):\n");
    if (!insert(&L2))
        return 0;

    El* L3 = mergeLists(L1, L2);

    printf("Lista L3 ordinata: ");
    printList(L3);

    freeList(L3);
    return 0;
}