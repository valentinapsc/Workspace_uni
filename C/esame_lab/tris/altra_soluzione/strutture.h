#ifndef STRUTTURE
#define STRUTTURE

#define LATOCAMPO 3
struct elemento {
    char campo[LATOCAMPO][LATOCAMPO];
    char vincitore;
    int punteggio;
    struct elemento *prossimo;
};

#endif