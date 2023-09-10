#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // per la funzione toupper

typedef struct {
    char codice[10];   // Codice dello studente
    char nome[50];     // Nome dello studente
    char cognome[50];  // Cognome dello studente
} Studente;            // Struttura dati per contenere i dati di uno studente

typedef struct nodo {
    Studente studente;  // Contiene i dati dello studente
    struct nodo* next;  // Puntatore al nodo successivo
} Nodo;                 // Struttura dati per contenere i dati di uno studente

typedef struct {
    Nodo* testa;  // Puntatore al primo nodo
    Nodo* coda;   // Puntatore all'ultimo nodo
} Elenco;         // Struttura dati per contenere gli studenti

void initElenco(Elenco* elenco) {
    elenco->testa = NULL;
    elenco->coda = NULL;
}

// Inserisce uno studente in coda (politica FIFO)
// uso un punatatore ad elenco perchè devo modificare la coda e la testa dell'elenco (passato per riferimento)
// non passo studente per riferimento perchè non devo modificarlo (passato per valore)
void enqueue(Elenco* elenco, Studente studente) {
    Nodo* nuovoNodo = (Nodo*)malloc(sizeof(Nodo)); // Alloca un nuovo nodo per la lista (in memoria heap) perchè la lista è dinamica (non so quanti nodi ci saranno) 

    if(nuovoNodo == NULL){
        perror("");
        return;
    }

    nuovoNodo->studente = studente; // Copia lo studente nel campo studente della struct nodo
    nuovoNodo->next = NULL; // Il nuovo nodo non punta a nessun altro nodo

    // Se la coda è vuota, il nuovo nodo è sia la testa che la coda
    if (elenco->coda == NULL) {
        elenco->testa = nuovoNodo;
        elenco->coda = nuovoNodo;
    } else { // il nuovo nodo viene inserito in coda
        elenco->coda->next = nuovoNodo; // Il nodo in coda punta al nuovo nodo
        elenco->coda = nuovoNodo; // Il nuovo nodo diventa la coda
    }
}

// Carica gli studenti da un file di testo
void load_students_from_file(Elenco* elenco, const char* nomefile) {
    FILE* file = fopen(nomefile, "r");

    if (file == NULL) {
        printf("Errore nell'apertura del file %s\n", nomefile);
        return;
    }

    char buffer[100]; // Buffer per leggere le righe del file (ogni riga può contenere al massimo 100 caratteri)
    while (fgets(buffer, sizeof(buffer), file) != NULL) { // Legge una riga del file e la salva nel buffer 

        // Rimuove il carattere di nuova linea (\n) dalla stringa letta dal file (fgets legge anche il carattere di nuova linea)
        buffer[strcspn(buffer, "\n")] = '\0'; 

        Studente studente;
        strcpy(studente.codice, buffer); 

        fgets(buffer, sizeof(buffer), file); // Legge la riga successiva
        buffer[strcspn(buffer, "\n")] = '\0'; // Rimuove il carattere di nuova linea (\n), strcspn restituisce la posizione del carattere \n e lo sostituisce con \0
        strcpy(studente.nome, buffer); // Copia il nome nel campo nome della struct studente

        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(studente.cognome, buffer);

        enqueue(elenco, studente);
    }
    fclose(file);
}

/*
    Scrive gli studenti su un file di testo
    Gli studenti scritti sono quelli il cui cognome inizia con una lettera compresa tra start_letter e stop_letter
*/
void write_students_on_file(Elenco* elenco, const char* nomefile, char start_letter, char stop_letter) {
    FILE* file = fopen(nomefile, "w");

    if (file == NULL) {
        printf("Errore nell'apertura del file %s\n", nomefile);
        return;
    }

    Nodo* nodoCorrente = elenco->testa; // Puntatore al nodo corrente (parte dalla testa)

    while (nodoCorrente != NULL) { // Scorre la lista
        char primaLettera = nodoCorrente->studente.cognome[0]; // Prende la prima lettera del cognome del nodo corrente

        // Verifica se la prima lettera rientra nell'intervallo specificato, sia maiuscola che minuscola
        if ((primaLettera >= start_letter && primaLettera <= stop_letter) ||
            (primaLettera >= toupper(start_letter) && primaLettera <= toupper(stop_letter))) {
            fprintf(file, "%s\n%s\n%s\n", nodoCorrente->studente.codice, nodoCorrente->studente.nome, nodoCorrente->studente.cognome);
        }
        nodoCorrente = nodoCorrente->next;
    }
    // tolower

    fclose(file);
}

int main() {
    Elenco elenco; // Lista di studenti

    initElenco(&elenco); // lo passo per riferimento perchè devo modificare l'elenco
    load_students_from_file(&elenco, "iscritti.txt");

    Elenco gruppo1, gruppo2, gruppo3;

    initElenco(&gruppo1);
    initElenco(&gruppo2);
    initElenco(&gruppo3);

    // Suddivisione degli studenti nei gruppi
Nodo* nodoCorrente = elenco.testa;

while (nodoCorrente != NULL) {
    char primaLettera = nodoCorrente->studente.cognome[0]; // Prende la prima lettera del cognome
    
    // Inserisce lo studente nel gruppo corretto
    if ((primaLettera >= 'a' && primaLettera <= 'g') || (primaLettera >= 'A' && primaLettera <= 'G')) {
        enqueue(&gruppo1, nodoCorrente->studente);

    } else if ((primaLettera >= 'h' && primaLettera <= 'p') || (primaLettera >= 'H' && primaLettera <= 'P')) {
        enqueue(&gruppo2, nodoCorrente->studente);

    } else if ((primaLettera >= 'q' && primaLettera <= 'z') || (primaLettera >= 'Q' && primaLettera <= 'Z')) {
        enqueue(&gruppo3, nodoCorrente->studente);
    }
    nodoCorrente = nodoCorrente->next;
    }

    write_students_on_file(&gruppo1, "gruppo1.txt", 'a', 'g');
    write_students_on_file(&gruppo2, "gruppo2.txt", 'h', 'p');
    write_students_on_file(&gruppo3, "gruppo3.txt", 'q', 'z');

    return 0;
}