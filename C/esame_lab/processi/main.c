#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definizione della struttura dati GestoreProcessi
typedef struct {
    char nome[65];      // Nome del processo
    int deadline_gg;    // Giorno di deadline
    int deadline_mm;    // Mese di deadline
    int deadline_aaaa;  // Anno di deadline
} Processo;

typedef struct {
    Processo** array;  // Array di puntatori a Processo
    int size;          // Numero di elementi presenti nell'array
    // int capacity;      // Numero di elementi massimi che l'array può contenere
} GestoreProcessi;

// Funzione di inizializzazione del GestoreProcessi
void init(GestoreProcessi* gestoreprocessi) {
    gestoreprocessi->array = NULL;
    gestoreprocessi->size = 0;
    // gestoreprocessi->capacity = 10;
}

// Funzione per ottenere il numero di elementi presenti nel GestoreProcessi
int len(GestoreProcessi* gestoreprocessi) { 
    return gestoreprocessi->size; 
}

// Funzione per verificare se il GestoreProcessi è vuoto
int is_empty(GestoreProcessi* gestoreprocessi) {
    return gestoreprocessi->size == 0;
}

// Funzione per inserire un processo nel GestoreProcessi con politica FIFO
void insert(GestoreProcessi* gestoreprocessi, Processo processo) {
    if (gestoreprocessi->size == 0) {  // se il gestore è vuoto
        gestoreprocessi->array = (Processo**)malloc(sizeof(Processo*));  // alloco la memoria per il primo processo
    } else {  // se il gestore non è vuoto
        gestoreprocessi->array = (Processo**)realloc( gestoreprocessi->array, (gestoreprocessi->size + 1) * sizeof(Processo*));

        if (gestoreprocessi->array == NULL) {
            // Gestione dell'errore di allocazione
            perror("");
            return;
        }
    } // rialloco la memoria per il nuovo processo

    /* 
    * per le allocazioni ho utilizzato il doppio puntatore perchè il puntatore
    * a puntatore mi permette di allocare la memoria per un array di puntatori,
    */

    Processo* nuovo_processo = (Processo*)malloc(sizeof(Processo));

    if (nuovo_processo == NULL){
        perror("");
        return;
    }

    strcpy(nuovo_processo->nome, processo.nome);
    nuovo_processo->deadline_gg = processo.deadline_gg;
    nuovo_processo->deadline_mm = processo.deadline_mm;
    nuovo_processo->deadline_aaaa = processo.deadline_aaaa;

    gestoreprocessi->array[gestoreprocessi->size] = nuovo_processo;
    gestoreprocessi->size++;
}

// Funzione per ottenere il processo con deadline futura più imminente
Processo* next(GestoreProcessi* gestoreprocessi) {
    if (is_empty(gestoreprocessi)) {
        return NULL;
    }

    int min_index = 0;  // Indice del processo con deadline più imminente
    Processo* min_processo = gestoreprocessi->array[min_index];  // Processo più imminente

    for (int i = 1; i < len(gestoreprocessi); i++) {
        Processo* processo = gestoreprocessi->array[i];  // Processo corrente

        if (processo->deadline_aaaa < min_processo->deadline_aaaa ||
            (processo->deadline_aaaa == min_processo->deadline_aaaa &&
             processo->deadline_mm < min_processo->deadline_mm) ||
            (processo->deadline_aaaa == min_processo->deadline_aaaa &&
             processo->deadline_mm == min_processo->deadline_mm &&
             processo->deadline_gg < min_processo->deadline_gg)) {
            min_index = i;  // Aggiorna l'indice del processo con deadline più imminente
        }
    }

    // Rimuovi il processo con deadline più imminente dal GestoreProcessi
    for (int i = min_index; i < gestoreprocessi->size - 1;i++) {  // size - 1 perchè l'ultimo elemento non va spostato
        gestoreprocessi->array[i] = gestoreprocessi->array[i + 1];  // Sposta tutti gli elementi a destra dell'elemento da rimuovere
    }

    gestoreprocessi->size--;

    return min_processo;
}

// Funzione per leggere i dati dei processi da un file
void read_from_file(const char* nomefile, GestoreProcessi* gestoreprocessi) {
    FILE* file = fopen(nomefile, "r");

    if (file == NULL) {
        printf("Impossibile aprire il file.\n");
        return;
    }

    char nome[65];  // Nome del processo
    int gg, mm, aaaa;

    while (fgets(nome, sizeof(nome), file) != NULL) {
        // Rimuovi il carattere di newline dal nome del processo
        nome[strcspn(nome, "\n")] = '\0';  // strcspn restituisce la lunghezza della sottostringa che  non contiene il carattere di newline

        // Leggi la data di deadline
        fscanf(file, "%d %d %d\n", &gg, &mm, &aaaa);
        /* fflush(stdin); */  // Consuma il carattere di newline dopo la data

        // Crea un nuovo processo
        Processo* processo = (Processo*)malloc(sizeof(Processo));  // Alloca la memoria per il nuovo processo

        // Inizializza il processo
        strcpy(processo->nome, nome);
        processo->deadline_gg = gg;
        processo->deadline_mm = mm;
        processo->deadline_aaaa = aaaa;

        // Inserisci il processo nel GestoreProcessi
        insert(gestoreprocessi, *processo);
    }

    fclose(file);
}

/*
* ho una data di scadenza, prendo processi dal gestore processi fin quando non ne
* trovo uno che va bene per la data fornita (ovvero che il giorno, mese ed anno
* siano più piccoli di quelli dati, ma il controllo va fatto ad uno ad uno)

* nel mentre che cerco il primo processo utile, potrei toglierne alcuni non ancora
* scaduti, quindi se li becco li reinserico nella struttura

* prima o poi becco il processo utile, lo trovo e ci faccio una free
*/

void clean(int giorno, int mese, int anno, GestoreProcessi* gestoreprocessi) {
    if (is_empty(gestoreprocessi))
        printf("\nIl gestore dei processi è vuoto!\n");

    int flag = 1;
    // Finché ci sono processi nel gestore e trovo un processo che va bene per la data fornita
    while (flag && !is_empty(gestoreprocessi)) {
        Processo* eliminato = next(gestoreprocessi);

        if (eliminato->deadline_aaaa < anno ||
            (eliminato->deadline_aaaa == anno && eliminato->deadline_mm < mese) ||
            (eliminato->deadline_aaaa == anno && eliminato->deadline_mm == mese && eliminato->deadline_gg < giorno)) {
            free(eliminato);  // Libera la memoria del processo scaduto
        } else {
            flag = 0;  // Ho trovato un processo valido, esco dal ciclo
        }
    }
}

// Funzione per scrivere i processi rimanenti su un file
void write_on_file(const char* nomefile, GestoreProcessi* gestoreprocessi) {
    FILE* file = fopen(nomefile, "w");

    if (file == NULL) {
        printf("Impossibile aprire il file.\n");
        return;
    }

    for (int i = 0; i < gestoreprocessi->size; i++) {
        Processo* processo = gestoreprocessi->array[i];

        fprintf(file, "%s\n%d %d %d\n", processo->nome, processo->deadline_gg, processo->deadline_mm, processo->deadline_aaaa);
    }

    fclose(file);
}

int main() {
    GestoreProcessi gestoreprocessi;
    init(&gestoreprocessi);

    // Punto 2: Leggi i processi dal file 'processi.txt'
    read_from_file("processi.txt", &gestoreprocessi);

    // Punto 4: Visualizza i processi uno alla volta
    int continua = 1;  // Variabile per verificare se l'utente vuole continuare a visualizzare i processi

    for (int i = 0; i < gestoreprocessi.size && continua; i++) {
        Processo* processo = gestoreprocessi.array[i];

        printf("Nome processo: %s\n", processo->nome);
        printf("Deadline: %d/%d/%d\n", processo->deadline_gg, processo->deadline_mm, processo->deadline_aaaa);

        char scelta;  // Scelta dell'utente

        do {
            printf("Desideri continuare? (S/N) ");
            scanf("%c", &scelta);
            getchar();

            switch (scelta) {
                case 'S':
                case 's':
                    break;
                case 'N':
                case 'n':
                    continua = 0;
                    break;
                default:
                    printf("Scelta non valida.\n");
                    scelta = 0;
                    break;
            }

        } while (scelta == 0);
    }

    // Punto 3: Elimina i processi scaduti rispetto alla data odierna
    int giorno, mese, anno;

    printf("Inserisci la data odierna (gg mm aaaa): ");
    scanf("%d %d %d", &giorno, &mese, &anno);

    clean(giorno, mese, anno, &gestoreprocessi);

    // Punto 5: Salva i processi rimanenti nel file 'processi_updated.txt'
    write_on_file("processi_updated.txt", &gestoreprocessi);

    return 0;
}