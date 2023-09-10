#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Dichiarazioni di costanti e tipi */
#define LUNGLOC 20
struct localita {
    char nome[LUNGLOC + 1];
    char codice;
    struct localita *next;
};

typedef struct localita Localita;
typedef Localita *ListaLocalita;

/* Restituisce il codice corrispondente alla tempertura temp. */
char tempCod(int temp) {
    char cod;

    if (temp < 20)
        cod = 'f';
    else if (temp <= 30)
        cod = 't';
    else
        cod = 'c';
    return cod;
}

ListaLocalita leggiLocalita(char *nomefile) {
    FILE *fp;
    ListaLocalita aux, lista = NULL;

    int temp;
    char nome[LUNGLOC + 1];

    if ((fp = fopen(nomefile, "r")) == NULL) {
        printf("Errore in apertura in lettura del file %s\n", nomefile);
        exit(1);
    }

    while (fscanf(fp, "%20s%d", nome, &temp) == 2) {
        aux = malloc(sizeof(Localita));
        strcpy(aux->nome, nome);
        aux->codice = tempCod(temp);
        aux->next = lista;
        lista = aux;
    }

    fclose(fp);

    return lista;
}

/* Stampa sul file *fp le localita in lista il cui codice di temperatura e`
pari a codice.*/
void stampaLocalitaConCodice(FILE *fp, ListaLocalita lista, char codice)
{
    while (lista != NULL) {
        if (lista->codice == codice)
            fprintf(fp, "%-20s %c\n", lista->nome, codice);
        lista = lista->next;
    }
}

void cancellaLista(ListaLocalita *plis) {
    ListaLocalita aux;

    while (*plis != NULL) {
        aux = *plis;
        *plis = (*plis)->next;
        free(aux);
    }
}

void stampaLocalita(char *nomefile, ListaLocalita lista) {
    FILE *fp;

    if ((fp = fopen(nomefile, "w")) == NULL) {
        printf("Errore in apertura in scrittura del file %s\n", nomefile);
        exit(1);
    }

    stampaLocalitaConCodice(fp, lista, 'c');
    stampaLocalitaConCodice(fp, lista, 't');
    stampaLocalitaConCodice(fp, lista, 'f');

    fclose(fp);

    cancellaLista(&lista);
}

int main(void) {
    char nomefile[256];
    ListaLocalita lista;

    printf("Immetti il nome del file di input con le localita: ");
    scanf("%s", nomefile);

    lista = leggiLocalita(nomefile);
    printf("Immetti il nome del file di output: ");
    scanf("%s", nomefile);

    stampaLocalita(nomefile, lista);

    return 0;
}