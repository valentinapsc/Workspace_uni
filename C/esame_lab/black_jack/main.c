#include <stdio.h>
#include <stdlib.h>
#include "strutture.h"
#include "header.h"

#define INPUTFILE "partita.txt"
#define OUTPUTFILE "ranking.txt"

int main(){
    struct Giocatore *inizio = NULL;

    //PUNTO 1
    load_players_from_file(INPUTFILE, &inizio);

    //PUNTO 2
    print_list(inizio);

    //PUNTO 3
    expels(&inizio);

    //PUNTO 4
    struct Giocatore *vincitore = the_winner_is(inizio);
    printf ("Il vincitore è: %s con %d punti!\n", vincitore->nome, compute_points(vincitore->valori, vincitore->n));
    
    //PUNTO 5
    write_ranking_on_file(OUTPUTFILE, inizio);
    printf ("Lista in memoria:\n");
    print_list(inizio);

    freeList(inizio);
    inizio = NULL;

    return 0;
}