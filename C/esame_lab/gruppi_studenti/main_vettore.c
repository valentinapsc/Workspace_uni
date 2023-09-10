/*
Divide gli studenti in 3 gruppi diversi in base al range di lettere
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char matricola[10];     // matricola studente
    char nome[50];          // nome studente
    char cognome[50];       // cognome studente
} Studente;

typedef struct {
    Studente *studenti;  // vettore dinamico di studenti
    int dimensione;      // dimensione del vettore
    int capacita;        // capacita' del vettore
} Elenco;

void initElenco(Elenco *elenco) {
    elenco->studenti = (Studente*)malloc(elenco->capacita * (sizeof(Studente)));
    elenco->capacita = 0;
    elenco->dimensione = 0;
}

void addStudent(Elenco *elenco, Studente studente) {
    if (elenco->dimensione == elenco->capacita){
        elenco->capacita +=1;
        elenco->studenti = (Studente*)realloc(elenco->studenti, elenco->capacita * sizeof(Studente));
    }

    strcpy(elenco->studenti[elenco->dimensione].matricola, studente.matricola);
    strcpy(elenco->studenti[elenco->dimensione].nome, studente.nome);
    strcpy(elenco->studenti[elenco->dimensione].cognome, studente.cognome);

    elenco->dimensione++;
}

void loadStudentsFromFile(Elenco *elenco, const char *filename){
    FILE *file = fopen(filename, "r");

    if (file == NULL){
        perror("");
        return;
    }
    
    char buffer[50]; // Buffer per leggere le righe del file (ogni riga può contenere al massimo 50 caratteri)
    while (fgets(buffer, sizeof(buffer), file) != NULL){
        Studente studente; // dichiaro lo studente

        // Rimuove il carattere di nuova linea (\n) dalla stringa letta dal file (fgets legge anche il carattere di nuova linea)
        buffer[strcspn(buffer, "\n")] = '\0'; // strcspn restituisce la lunghezza della stringa fino al carattere \n e lo sostituisce con \0
        strcpy(studente.matricola, buffer);

        // Legge una riga del file (nome) e la salva nel buffer
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(studente.nome, buffer);

        // Legge una riga del file (cognome) e la salva nel buffer
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(studente.cognome, buffer);

        addStudent(elenco, studente);
    }
    
    fclose(file);
}

void writeStudentOnFile(Elenco *elenco, const char *filename, char start_letter, char stop_letter){
    FILE *file = fopen(filename, "w");

    if (file == NULL){
        perror("");
        return;
    }

    for (int i = 0; i < elenco->dimensione; i++){
        Studente studente = elenco->studenti[i];
        char primaLettera = studente.cognome[0];

        if ((primaLettera >= start_letter && primaLettera <= stop_letter) ||
            (primaLettera >= toupper(start_letter) && primaLettera <= toupper(stop_letter))) {
            fprintf(file, "%s\n%s\n%s\n", studente.matricola, studente.nome, studente.cognome);
        }
    }
    fclose(file);
}

int main(){
    Elenco elenco;

    initElenco(&elenco);

    loadStudentsFromFile(&elenco, "iscritti.txt");

    writeStudentOnFile(&elenco, "gruppo1.txt", 'a', 'g');
    writeStudentOnFile(&elenco, "gruppo2.txt", 'h', 'p');
    writeStudentOnFile(&elenco, "gruppo3.txt", 'q', 'z');

    return 0;
}