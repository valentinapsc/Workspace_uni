#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char tipo_elemento;

struct coda {  // definisco la struttura pe realizzare la lista
    tipo_elemento valore;
    struct coda *next;
};

struct coda *crea_coda(tipo_elemento *elementi);

void stampa_coda(struct coda *queue);

void stampa_coda_su_file(struct coda *queue);  // identifico il prototipo di funzione per salvare la lista su file

tipo_elemento pop(struct coda **queue);

struct coda *push(struct coda *queue, tipo_elemento t);

int libera_coda(struct coda *queue);

int main(int argc, char *argv[]) {
    struct coda *c1;  // puntatore alla struct coda che verrà passato per creare
                      // la coda e per salvarla su file
    int testa, mem;
    int scelta;
    int decisione;
    char car = '6';

    tipo_elemento elems[5] = {'1', '2', '3', '4', '5'};
    c1 = NULL;

    do {
        printf(
            "\nscegli l'opzione che preferisci\ndigitare zero per uscire\n1-crea "
            "la coda\n2-elimina il primo elemento\n3-inserisci "
            "elemento\n4-libera la memoria\n5-salva la coda su file\n");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                printf("creo la coda...\n");
                c1 = crea_coda(elems);
                stampa_coda(c1);
                break;

            case 2:
                printf("Elimino la testa: ");
                testa = pop(&c1);
                printf("%c\t", testa);
                stampa_coda(c1);
                break;

            case 3:
                printf("inserisco elemento %c ... ", car);
                c1 = push(c1, car);
                stampa_coda(c1);
                break;

            case 4:
                printf("libero la memoria...\n");
                mem = libera_coda(c1);
                printf("bytes di memoria liberati: %d\n", mem);
                break;

            case 5:
                stampa_coda_su_file(c1);  
                // richiamo la funzione per stampare la lista su file
                break;

            default:
                scelta = 0;
                break;
        }
    } while (scelta != 0);

    system("PAUSE");
    return 0;
}

struct coda *crea_coda(tipo_elemento *elementi) {
    struct coda *nuovo, *precedente, *primo;
    int index;

    if (elementi == NULL) return NULL;

    primo = nuovo = precedente = malloc(sizeof(struct coda));
    nuovo->valore = elementi[0];
    nuovo->next = NULL;

    for (index = 1; index < 5; index++) {
        precedente = nuovo;
        nuovo = malloc(sizeof(struct coda));
        memset(nuovo, 0, sizeof(struct coda));
        nuovo->valore = elementi[index];
        precedente->next = nuovo;
    }

    return primo;
}

void stampa_coda(struct coda *queue) {
    while (queue != NULL) {
        printf("valore: %c\t", queue->valore);
        queue = queue->next;
    }
    //  printf("\b \n");
}

void stampa_coda_su_file(struct coda *queue){
    FILE *fp;

    fp = fopen("LISTA.txt", "rw");
    if (fp == NULL) {
        printf("impossibile aprire il file");
        return;
    } else
        while (queue != NULL) {
            fprintf(fp, "%c\t", queue->valore);
            queue = queue->next;
        }
    fclose(fp);
}

tipo_elemento pop(struct coda **queue) {
    struct coda *q1;
    tipo_elemento elem;

    q1 = *queue;
    elem = q1->valore;
    *queue = (*queue)->next;
    free(q1);
    return elem;
}

struct coda *push(struct coda *queue, tipo_elemento t) {
    struct coda *prev, *first;

    first = queue;
    while (queue) {
        prev = queue;
        queue = queue->next;
    }
    prev->next = malloc(sizeof(struct coda));
    memset(prev->next, 0, sizeof(struct coda));

    if (prev->next == NULL) {
        perror("non c'è abbastanza memoria");
        return queue;
    } else {
        prev->next->valore = t;
        prev->next->next = NULL;
    }
    return first;
}

int libera_coda(struct coda *queue) {
    struct coda *q1;
    int bytes = 0;
    while (queue) {
        q1 = queue;
        queue = queue->next;
        free(q1);

        q1 = NULL;
        bytes += sizeof(struct coda);
    }
    return bytes;
}