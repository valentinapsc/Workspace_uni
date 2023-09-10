#include <stdio.h>
#include <stdlib.h>

struct elemento {
    int inf;
    struct elemento *next;
};

void raddoppia_dispari_consecutivi(struct elemento *lista) {
    if (lista == NULL || lista->next == NULL) {
        return; // caso base: la lista è vuota o ha un solo elemento
    }
    
    if (lista->inf % 2 != 0 && lista->inf == lista->next->inf) {
        // caso ricorsivo: raddoppia gli elementi dispari consecutivi uguali
        lista->inf *= 2;
        lista->next = lista->next->next;
        raddoppia_dispari_consecutivi(lista);
    } else {
        // caso ricorsivo: passa al successivo elemento della lista
        raddoppia_dispari_consecutivi(lista->next);
    }
}

struct elemento *createelemento(int elem) {
    // alloco il nuovo nodo
    // controllo se è stato allocato
    // nel caso imposto i valori

    struct elemento *nodo = (struct elemento *)malloc(sizeof(struct elemento));
    if (nodo != NULL) {
        nodo->next = NULL;
        nodo->inf = elem;
    }
    return nodo;
}

// prende in input la testa e il nodo da inserire
struct elemento *addInHead(struct elemento *head, struct elemento *nodo) {
    // se ho passato un nodo non allocato, allora non inserirò il nodo,
    // restituisco quindi la testa cosi come è stata passata in input
    if (nodo == NULL) return head;

    // altrimenti il successivo del nuovo, sara la testa
    nodo->next = head;

    // restituisco il nuovo nodo
    return nodo;
}

void displayList(struct elemento *head) {
    struct elemento *tmp;

    if (head == NULL) {
        printf(" nessun elemento trovato nella lista.");
        exit(-1);
    } else {
        tmp = head;
        while (tmp != NULL) {
            printf("%d-> ",
                   tmp->inf);  // stampa l'elemento del nodo corrente
            tmp = tmp->next;    // scorre la posizione del nodo
        }
        printf("NULL");
    }
}

int main() {
    struct elemento *head = NULL;
    int nElem, dato, choice;

    // la variabile nElem viene inserita tramite tastiera dall'utente
    printf("specificare  il numero di elementi da inserire: ");
    scanf("%d", &nElem);

    for (int i = 0; i < nElem; i++) {
        printf("inserisci elemento %d: ", i);
        scanf("%d", &dato);
        printf("\n");

        head = addInHead(head, createelemento(dato));
    }

    printf("\n");
    displayList(head);
    printf("\n\n");
    
    raddoppia_dispari_consecutivi(head);
    
     printf("\n");
    displayList(head);
    printf("\n\n");
    
    return 0;
}