#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

typedef struct node {
    char campo[SIZE][SIZE];  // Matrice 3x3 che rappresenta il campo di gioco
    char vincitore;          // 'X' o 'O' se c'è un vincitore, 'P' se è un pareggio
    int punteggio;           // Punteggio della partita
    struct node* next;       // Puntatore al nodo successivo
} Node;

Node* loadMatchesFromFile(const char* filename);
char theWinnerIs(char campo[SIZE][SIZE]);
int matchScore(char campo[SIZE][SIZE]);
int freePositions(char campo[SIZE][SIZE]);
void printList(Node* head);
void printMatch(Node* match);
void removeTied(Node** head);
void writeWinnersOnFile(const char* filename, Node* head, char player);

int main() {
    // Carica il file nella lista
    Node* head = loadMatchesFromFile("configurazioni.txt");

    // Stampa la lista
    printf("Lista originale:\n");
    printList(head);

    // Rimuove le partite pareggiate
    removeTied(&head);

    // Stampa la lista senza partite pareggiate
    printf("\nLista senza partite pareggiate:\n");
    printList(head);

    // Salva le configurazioni di vittoria di 'X' nel file "vittorie X.txt"
    writeWinnersOnFile("vittorie X.txt", head, 'X');

    // Salva le configurazioni di vittoria di 'O' nel file "vittorie O.txt"
    writeWinnersOnFile("vittorie O.txt", head, 'O');

    // Dealloca la memoria occupata dalla lista
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

// Carica le partite dal file e le inserisce in una lista
Node* loadMatchesFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Impossibile aprire il file %s.\n", filename);
        exit(1);
    }

    Node* head = NULL; // puntatore al primo nodo della lista mi serve per scorrere la lista
    Node* tail = NULL; // puntatore all'ultimo nodo della lista mi serve per aggiungere un nuovo nodo alla lista

    // Legge il file fino alla fine e carica le partite nella lista
    char line[50]; // stringa che contiene la riga del file corrente
    int idxLine = 0; // indice del carattere corrente della riga

    while (fgets(line, sizeof(line), file) != NULL) { // legge una riga del file e la salva in line
        Node* newNode = (Node*)malloc(sizeof(Node));

        if (newNode == NULL) {
            printf("Errore nell'allocazione della memoria.\n");
            exit(-1);
        }

        // Carica la configurazione della partita nel campo di gioco
        for (int i = 0; i < SIZE; i++) {  // righe

            for (int j = 0; j < SIZE; j++) {  // colonne

                newNode->campo[i][j] = line[idxLine];  // carica il carattere nella matrice
                idxLine++;  // incrementa l'indice della linea perchè si passa al carattere successivo
            }
        }

        idxLine = 0;  // resetta l'indice della linea perchè si passa alla riga successiva del file

        /* Carica la configurazione della partita nel campo di gioco
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                fscanf(file, " %c", &newNode->campo[i][j]);
            }
        }*/

        // Determina il vincitore e il punteggio
        newNode->vincitore = theWinnerIs(newNode->campo);
        printf("post winner\n");
        newNode->punteggio = matchScore(newNode->campo);
        printf("post match scor\n");

        newNode->next = NULL; // il nuovo nodo è l'ultimo della lista, quindi il suo next è NULL

        if (head == NULL) { // se la lista è vuota, il nuovo nodo è sia il primo che l'ultimo
            head = newNode;
            tail = newNode;
        } else { // altrimenti il nuovo nodo è il nuovo ultimo della lista
            tail->next = newNode; // il next dell'ultimo nodo diventa il nuovo nodo
            tail = newNode; // il nuovo nodo diventa l'ultimo nodo
        }
    }

    fclose(file);
    return head; // ritorna il puntatore al primo nodo della lista per poterla scorrere nel main
}

// Determina il vincitore della partita
char theWinnerIs(char campo[SIZE][SIZE]) {
    // Controllo delle righe
    for (int i = 0; i < SIZE; i++) {
        if (campo[i][0] != '@' && campo[i][0] == campo[i][1] &&
            campo[i][0] == campo[i][2]) {
            return campo[i][0];
        }
    }

    // Controllo delle colonne
    for (int j = 0; j < SIZE; j++) {
        if (campo[0][j] != '@' && campo[0][j] == campo[1][j] &&
            campo[0][j] == campo[2][j]) {
            return campo[0][j];
        }
    }

    // Controllo delle diagonali
    if (campo[0][0] != '@' && campo[0][0] == campo[1][1] &&
        campo[0][0] == campo[2][2]) {
        return campo[0][0];
    }

    if (campo[0][2] != '@' && campo[0][2] == campo[1][1] &&
        campo[0][2] == campo[2][0]) {
        return campo[0][2];
    }

    return 'P';  // Pareggio
}

// Determina il punteggio della partita
int matchScore(char campo[SIZE][SIZE]) {
    if (theWinnerIs(campo) == 'P') {
        return 0;
    } else {
        return 3 + freePositions(campo);  // 3 punti per la vittoria + numero di posizioni libere
    }
}

// Determina il numero di posizioni libere nel campo di gioco
int freePositions(char campo[SIZE][SIZE]) {
    int count = 0;  // Contatore delle posizioni libere

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (campo[i][j] == '@') {
                count++;
            }
        }
    }
    return count;
}

// Stampa la lista
void printList(Node* head) {
    if (head == NULL) {
        printf("La lista e' vuota.\n");
        return;
    }

    Node* current = head;

    while (current != NULL) {
        printMatch(current);
        current = current->next;
    }
}

// Stampa una partita
void printMatch(Node* match) {
    printf("Vincitore: %c\n", match->vincitore);
    printf("Punteggio: %d\n", match->punteggio);
    printf("Campo di gioco:\n");

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", match->campo[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

// Rimuove le partite pareggiate dalla lista
void removeTied(Node** head) {
    Node* current = *head;  // Puntatore al nodo corrente
    Node* prev = NULL;      // Puntatore al nodo precedente

    while (current != NULL) {
        if (current->vincitore == 'P') {
            if (prev == NULL) {
                *head = current->next;  // Se il nodo corrente è il primo, il
                                        // nuovo primo è il nodo successivo
            } else {
                prev->next = current->next;  // Altrimenti il nodo successivo
                                             // del nodo precedente è il nodo
                                             // successivo del nodo corrente
            }

            Node* temp = current;  // Dealloca il nodo corrente
            current =
                current->next;  // Il nodo corrente diventa il nodo successivo
            free(temp);
        } else {
            prev = current;  // Il nodo precedente diventa il nodo corrente
            current = current->next;
        }
    }
}

// Salva le configurazioni di vittoria di un giocatore nel file
void writeWinnersOnFile(const char* filename, Node* head, char player) {
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        printf("Impossibile aprire il file %s.\n", filename);
        exit(1);
    }

    Node* current = head;

    while (current != NULL) {
        if (current->vincitore == player) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    fprintf(file, "%c ", current->campo[i][j]);
                }

                fprintf(file, "\n");
            }

            fprintf(file, "\n");
        }

        current = current->next;
    }

    fclose(file);
}