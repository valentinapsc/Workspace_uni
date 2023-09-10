#include <stdio.h>
//#include "prototipi.h"
//#include "strutture.h"

#define INPUTFILE "configurazioni.txt"
#define OUTPUTFILEX "vittorie_X.txt"
#define OUTPUTFILEO "vittorie_O.txt"
int main(){
    struct elemento *inizio = NULL;

    load_matches_from_file(INPUTFILE, &inizio);
    print_list(inizio);

    printf ("Rimuovo i casi di pareggio\n");
    remove_tied(&inizio);
    print_list(inizio);

    write_winners_on_file(OUTPUTFILEX, inizio, 'X');
    write_winners_on_file(OUTPUTFILEO, inizio, 'O');

    freeLista(inizio);
    inizio = NULL;

    return 0;
}