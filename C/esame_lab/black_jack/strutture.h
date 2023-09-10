#ifndef STRUTTURE
#define STRUTTURE

#define LOGSTRING 32

struct Giocatore {
    char nome[LOGSTRING];
    int n;
    int *valori;
    struct Giocatore *prossimo;
};

#endif