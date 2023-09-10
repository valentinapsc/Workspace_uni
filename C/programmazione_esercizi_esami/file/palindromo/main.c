#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE } bool;

bool palindromo(FILE* file) {
    int count = 0;
    char inizio, fine;
    rewind(file);
    
    /*Leggo un carattere all'inizio del file*/
    while ((inizio = fgetc(file)) != EOF) {
        count++;
        /*Mi sposto alla fine del file*/
        fseek(file, -count * sizeof(char), SEEK_END);
        /*a questo punto count e' stato
         incrementato, quindi non leggero'
         EOF come primo carattere alla prima
         lettura*/

        /* Leggo un carattere */
        fine = fgetc(file);
        if (inizio != fine) {
            return FALSE;
        }
        /*
        Mi riposiziono all'inizio del file
         N.B. count e' gia stato incrementato
        */
        fseek(file, count * sizeof(char), SEEK_SET);
        /*quando mi riposiziono all'inizio
        o alla fine del file devo usare
        un contatore per sapere quanti
        caratteri saltare*/
    }
    return TRUE;
}
int main() {
    FILE* f;
    if ((f = fopen("palindromo.txt", "r")) == NULL) {
        puts("Non e' possibile aprire il file");
        exit(1);
    }
    if (palindromo(f)) {
        printf("Testo palindromo\n");
    } else {
        printf("Testo non palindromo\n");
        fclose(f);
    }
}
