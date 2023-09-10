#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *pf;

    int  *  const p;

    // fopen restituisce un puntatore a FILE.
    // apro il file voti.txt in modalità lettura "r"
    // inserisco il puntatore restituito da fopen in pf
    pf = fopen("voti.txt", "r");

    // controllo se pf è null
    // dato che se lo fosse allora il file non è stato aperto correttamente
    if (pf == NULL) {
        printf("errore file.");
        return -1;
    }

    // dichiaro una stringa
    // può essere fatto anche nel modo classico e non dinamicamente
    char *nome = (char *)malloc(sizeof(char) * 100);

    // stesso discorso per questo array di stringhe
    // l'ho allocato dinamicamente pensando fosse questo l'errore
    char **nomi = (char **)malloc(sizeof(char *) * 100);
    for (int i = 0; i < 100; i++) {
        nomi[i] = (char *)malloc(sizeof(char) * 100);
    }

    // array parallelo a nomi
    // ovvero voti[i] contiene il voto del tizio a nomi[i]
    int voti[100] = {0};

    // contatore dei nomi inseriti
    int Nnomi = 0;

    int index;
    while (fscanf(pf, "%s", nome) != EOF) {
        index = -1;

        // cerco l'indice dell'array <nomi> dove <nome> è uguale a <nome[i]>
        for (int i = 0; i < 100; i++) {
            if (strcmp(nome, nomi[i]) == 0) {
                // trovato l'indice lo metto in <index>
                // poi col break fermo il for tanto l'indice l'ho trovato, inutile scorrerlo tutto
                index = i;
                break;
            }
        }

        // se <index> è -1 significa che non è stato trovato nessun indice, ovvero il <nome>
        // non è presente nell'array <nomi>
        // e quindi glielo inserisco. Poi incremento di uno il voto del nuovo tizio
        // che si trova all'indice <voti[Nnomi]>, all'indice Nnome si trova anche il nome del tizio nell'array <nomi>
        if (index == -1) {
            strcpy(nomi[Nnomi], nome);
            voti[Nnomi] = voti[Nnomi] + 1;
            Nnomi++;
        } else {
            // altrimenti, ho  trovato l'indice, allora incremento di uno il voto del tizio, stesso discorso di prima
            voti[index] = voti[index] + 1;
        }
    }

    int max = voti[0];
    printf("Eletti:\n");

    // trovo il massimo valore presente in <voti>
    for (int i = 1; i < Nnomi; i++) {
        if (max < voti[i]) {
            max = voti[i];
        }
    }

    // cerco gli indici dell'array <voti> dove il valore è uguale a max
    // cosi facendo stampo poi il nome a quell'indice di tutti i tizi che hanno quel numero di voti
    for (int i = 0; i < Nnomi; i++) {
        if (voti[i] == max) {
            printf("%s\n", nomi[i]);
        }
    }
    printf("voto massimo %d", max);
}