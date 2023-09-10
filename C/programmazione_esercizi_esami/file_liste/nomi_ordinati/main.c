#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 128
#define ERRFOPEN -1
#define ERRMEM -2
#define ERRFORMAT -3
#define OK 0

struct Persona {
    char nome[MAXLEN];
    char cognome[MAXLEN];
};

void error_handler(int err) {
    switch (err) {
        case ERRFOPEN:
            printf("Errore apertura file!\n");
            break;
        case ERRMEM:
            printf("errore di memoria!\n");
            break;
        case ERRFORMAT:
            printf("errore di formato nel file!\n");
            break;
        case OK:
            printf("operazione eseguita con successo!\n");
            break;
        default:
            printf("errore sconosciuto!\n");
    }
}

int get_cleaned_line(char str[], int maxlen, FILE* file_handler) {
    int len = -1;

    if (fgets(str, maxlen, file_handler) != NULL) {
        len = 0;
        
        while (str[len] != '\0') len++;
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
            len--;
        }
    }
    return len;
}

void print_v(struct Persona* v, int n) {
    for (int i = 0; i < n; i++)
        printf("nome: \"%s\"; cognome: \"%s\"\n", v[i].nome, v[i].cognome);
}

int read_file(char filename[], struct Persona** v, int* n) {
    FILE* fin = fopen(filename, "r");
    if (fin == NULL) return ERRFOPEN;

    char line[MAXLEN];
    int linelen = 1;
    *n = 0;

    while (linelen > 0) {
        linelen = get_cleaned_line(line, MAXLEN, fin);
        if (linelen > 0) {
            // inserisco il contenuto della linea in una nuova struct
            struct Persona nuova;
            int i = 0;
            // prendo il nome
            while (i < linelen && line[i] != ' ') {
                nuova.nome[i] = line[i];
                i++;
            }

            // aggiungo il terminatore
            nuova.nome[i] = '\0';

            // prendo il cognome
            i++;  // parto dal carattere successivo allo spazio
            int j = 0;
            while (i < linelen) {
                nuova.cognome[j] = line[i];
                j++;
                i++;
            }
            // aggiungo il terminatore
            nuova.cognome[j] = '\0';

            // se l'acquisizione da file è andata a buon fine, rialloco l'array
            struct Persona* tmp = realloc(*v, (*n + 1) * sizeof(struct Persona));
            if (tmp == NULL) return ERRMEM;
            // se la riallocazione è andata a buon fine,
            // sovrascrivo il puntatore v col nuovo array
            *v = tmp;
            // inserisco il nuovo elemento in ultima posizione
            (*v)[*n] = nuova;
            (*n)++;
        }
    }

    fclose(fin);
    return OK;
}

void selection_sort(struct Persona* v, int n) {
    for (int i = 0; i < n - 1; i++) {
        int idx_min = i;

        for (int j = i + 1; j < n; j++) {
            // se il cognome viene alfabeticamente prima
            if (strcmp(v[j].cognome, v[idx_min].cognome) < 0) idx_min = j;
            // se i due cognomi sono ugali
            else if (strcmp(v[j].cognome, v[idx_min].cognome) == 0) {
                // ma il  nome viene alfabetiamente prima
                if (strcmp(v[j].nome, v[idx_min].nome) < 0) idx_min = j;
            }
        }
        // pongo la persona idx_min nella posizione giusta
        struct Persona tmp = v[i];
        v[i] = v[idx_min];
        v[idx_min] = tmp;
    }
}

int write_file(char filename[], struct Persona* v, int n) {
    FILE* fout = fopen("nomi_ordinati.txt", "w");

    if (fout == NULL) return ERRFOPEN;
    for (int i = 0; i < n; i++)
        fprintf(fout, "%s %s\n", v[i].nome, v[i].cognome);

    fclose(fout);
    return OK;
}

int main() {
    struct Persona* v = NULL;
    int n = 0;

    int err = read_file("nomi.txt", &v, &n);
    printf("lettura file...");
    error_handler(err);
    printf("\n");

    print_v(v, n);
    selection_sort(v, n);

    printf("\n");
    printf("dopo l'ordinamento:\n");
    printf("\n");

    print_v(v, n);
    err = write_file("nomi_ordinati.txt", v, n);
    printf("\n");

    printf("scrittura file...");
    error_handler(err);

    return 0;
}