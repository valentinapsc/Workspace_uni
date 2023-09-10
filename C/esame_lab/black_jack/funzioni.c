#include <stdio.h>
#include <stdlib.h>

#include "header.h"
#include "strutture.h"

#define OK 1
#define ERRFILE 5
#define ERRALLOC 10

// PUNTO 1
void load_players_from_file(const char *NomeFile, struct Giocatore **inizio) {
    // apro il file
    FILE *fp = NULL;
    fp = fopen(NomeFile, "r");
    if (fp == NULL) GestisciErrore(ERRFILE);

    char vuoto[255];       // per leggere "a vuoto" i semi delle carte
    struct Giocatore tmp;  // nodo temporaneo
    while (fscanf(fp, "%s %d", tmp.nome, &tmp.n) == 2) {
        tmp.valori = malloc(tmp.n * sizeof(int));  // alloco il vettori di valori
        if (tmp.valori == NULL) GestisciErrore(ERRALLOC);
        for (int i = 0; i < tmp.n; i++) {
            fscanf(fp, "%d %s", &tmp.valori[i], vuoto);
        }
        tmp.prossimo = NULL;

        // inserisco nodo nella lista
        appendInList(inizio, tmp);
    }

    fclose(fp);
}

void appendInList(struct Giocatore **inizio, struct Giocatore tmp) {
    struct Giocatore *nuovo = malloc(sizeof(struct Giocatore));
    if (nuovo == NULL) GestisciErrore(ERRALLOC);

    struct Giocatore *cursore = *inizio;
    struct Giocatore *precedente = NULL;

    *nuovo = tmp;

    while (cursore != NULL) {
        precedente = cursore;
        cursore = cursore->prossimo;
    }

    if (precedente == NULL) {
        *inizio = nuovo;
    } else {
        precedente->prossimo = nuovo;
    }
}

// PUNTO 2
void print_player(struct Giocatore g) {
    printf("Nome Giocatore: \"%s\"\n", g.nome);
    printf("Numero valori array: %d\n", g.n);
    printf("Valori: ");
    for (int i = 0; i < g.n; i++) {
        printf("%d ", g.valori[i]);
    }
    printf("\n\n");
}

void print_list(struct Giocatore *inizio) {
    if (inizio == NULL) return;

    printf(" -> ");
    print_player(*inizio);
    print_list(inizio->prossimo);
}

// PUNTO 3
#define MAX 21
void expels(struct Giocatore **inizio) {
    struct Giocatore *cursore = *inizio;
    struct Giocatore *precedente = NULL;
    while (cursore != NULL) {
        if (compute_points(cursore->valori, cursore->n) > MAX) {
            struct Giocatore *tmp = cursore->prossimo;

            free(cursore->valori);
            free(cursore);

            if (precedente == NULL)
                *inizio = tmp;
            else
                precedente->prossimo = tmp;

            cursore = tmp;
        } else {
            precedente = cursore;
            cursore = cursore->prossimo;
        }
    }
}

int compute_points(int *valori, int n) {
    int val;
    if (valori[0] > 10)  // se il valore è 11, 12 o 13, allora il punteggio è 10
        val = 10;
    else
        val = valori[0];

    if (n == 1) return val;

    return val + compute_points(valori + 1, n - 1);
}

// PUNTO 4
struct Giocatore *the_winner_is(struct Giocatore *inizio) {
    struct Giocatore *massimoPuntatore = NULL;
    int massimoPunteggio = -1;

    while (inizio != NULL) {
        int tmp = compute_points(inizio->valori, inizio->n);
        if (tmp > massimoPunteggio) {
            massimoPuntatore = inizio;  // aggiorna il puntatore in modo da
                                        // avere quello al nuovo "massimo"
            massimoPunteggio = tmp;  // aggiorna il punteggio
        }

        inizio = inizio->prossimo;
    }

    return massimoPuntatore;
}

// PUNTO 5
void write_ranking_on_file(const char *NomeFile, struct Giocatore *inizio) {
    // Apro il file
    FILE *fp = NULL;
    fp = fopen(NomeFile, "w");
    if (fp == NULL) GestisciErrore(ERRFILE);

    // Numero di nodi della lista
    int nLista = contaLista(inizio);

    // creo un array di flag (inizializzati a 0) con corrispondenza biunivoca
    // agli elementi della lista
    int *flag = calloc(nLista, sizeof(int));

    // Dovrò scrivere nLista elementi
    for (int i = 0; i < nLista; i++) {
        struct Giocatore *cursore =
            inizio;  // Per tornare sempre all'inizio della lista
        struct Giocatore *massimo = NULL;
        int punteggioCursore =
            0;  //è il punteggio del valore attualmente considerato
        int punteggioMassimo = -1;
        int j = 0;  // per scorrere l'array di flag
        int index_massimo = 0;
        while (cursore != NULL)  // scorro la lista
        {
            punteggioCursore = compute_points(
                cursore->valori, cursore->n);  // calcolo il punteggio
            // se il punteggio considerato è maggiore di quello "massimo" e non
            // ho già scritto il valore allora aggiorna punteggio "massimo",
            // salva l'indirizzo al nodo "massimo" e salva l'indice dei flag
            if (punteggioCursore > punteggioMassimo && flag[j] == 0) {
                punteggioMassimo = punteggioCursore;
                massimo = cursore;
                index_massimo = j;
            }
            j++;

            cursore = cursore->prossimo;
        }

        // avrò come nodo massimo proprio quello che sto cercando e lo scrivo.
        // Aggiorno il rispettivo indice
        flag[index_massimo] = 1;
        fprintf(fp, "%s %d\n", massimo->nome, punteggioMassimo);
    }

    free(flag);

    fclose(fp);
}

int contaLista(struct Giocatore *inizio) {
    int nLista = 0;

    while (inizio != NULL)  // Conto il numero di nodi
    {
        nLista = nLista + 1;
        inizio = inizio->prossimo;
    }

    return nLista;
}

// ALTRE FUNZIONI
void GestisciErrore(int err) {
    switch (err) {
        case OK:
            printf("OK\n");
            break;
        case ERRFILE:
            printf("Errore in apertura file\n");
            exit(-1);
            break;
        case ERRALLOC:
            printf("Errore in allocazione memoria\n");
            exit(-1);
            break;
        default:
            printf("Codice errore non riconosciuto. Codice: %d\n", err);
            exit(-1);
            break;
    }
}

void freeList(struct Giocatore *inizio) {
    while (inizio != NULL) {
        free(inizio->valori);
        struct Giocatore *tmp =
            inizio->prossimo;  // per non perdere il successivo nodo della lista
        free(inizio);
        inizio = tmp;
    }
}