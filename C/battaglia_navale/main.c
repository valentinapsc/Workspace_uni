#include <stdio.h>
#include <stdlib.h>

void stampaPosizione(int, int);
int stampaAffondata(char);
void inseriscinave(int, int, int);

char campo[6][6];

int a, b, verso, colpi;
int i;
int controllo;

int main() {
    colpi = 0;
    int i, j;
    controllo = 0;

    for (i = 0; i < 6; i++)
        for (j = 0; j < 6; j++) campo[i][j] = '0';

    int riga, col;
    int pos[4];  // pos 0 = alto   pos 1 = basso   pos 2 = destra   pos 3 =  sinistra

    printf("inserisci riga ");
    scanf("%d", &riga);
    printf("inserisci colonna ");
    scanf("%d", &col);

    for (i = 0; i < 4; i++) pos[i] = 0;

    if ((riga - 2) >= 0) {
        pos[0] = 1;
        printf("0: inserisci verso l'alto\n");
    }

    if ((riga + 2) <= 5) {
        pos[1] = 1;
        printf("1: inserisci verso il basso\n");
    }

    if ((col - 2) >= 0) {
        pos[2] = 1;
        printf("2: inserisci verso sinistra\n");
    }

    if ((col + 2) <= 5) {
        pos[3] = 1;
        printf("3: inserisci verso destra\n");
    }
    scanf("%d", &verso);
    // inserisci le navi
    inseriscinave(riga, col, verso);
    printf("nave inserita\n chiama il tuo amico\n");
    while (1) {
        if (controllo == 1) break;
        printf("inserisci riga ");
        scanf("%d", &riga);

        printf("inserisci colonna ");
        scanf("%d", &col);
        colpi = colpi + 1;
        printf("hai sparato il tuo %d colpo\n\n", colpi);
        stampaPosizione(riga, col);
        // stampaAffondata('a');
    }

    system("PAUSE");
}

void inseriscinave(int riga, int colonna, int verso) {
    campo[riga][colonna] = 'a';
    switch (verso) {
        case 0:
            campo[riga - 1][colonna] = 'a';
            campo[riga - 2][colonna] = 'a';
            break;
        case 1:
            campo[riga + 1][colonna] = 'a';
            campo[riga + 2][colonna] = 'a';
            break;
        case 2:
            campo[riga][colonna - 1] = 'a';
            campo[riga][colonna - 2] = 'a';
            break;
        case 3:
            campo[riga][colonna + 1] = 'a';
            campo[riga][colonna + 2] = 'a';
            break;
    }
}

void stampaPosizione(int riga, int colonna) {
    int posizione;
    char nave;

    if (riga < 0 || riga > 5 || colonna < 0 || colonna > 5) {
        printf("le coordinate (%d, %d) non sono valide\n", riga, colonna);
        return;
    }

    if (campo[riga][colonna] == '0')
        printf("in (%d, %d) c'e' acqua\n", riga, colonna);
    else if (campo[riga][colonna] == '*')
        printf("in (%d, %d) c'e' una nave gia' colpita\n", riga, colonna);
    else {
        nave = campo[riga][colonna];
        printf("in (%d, %d) c'e' la nave %c : colpito\n", riga, colonna,
               nave);
        campo[riga][colonna] = '*';
        controllo = stampaAffondata(nave);
    }
}

int stampaAffondata(char nave) {
    int a, b;
    for (a = 0; a < 6; a++)
        for (b = 0; b < 6; b++)
            if (campo[a][b] == nave) {
                printf("nave %c non affondata\n", nave);
                return 0;
            }

    printf("nave %c affondata \n", nave);

    for (a = 0; a < 6; a++)
        for (b = 0; b < 6; b++)

            if (campo[a][b] != '0' && campo[a][b] != '*') {
                printf("ci sono ancora altre navi\n");
                return 0;
            }
    printf("partita terminata\n");

    return 1;
}