#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void initElenco(Elenco *elenco){
    elenco->head = NULL;
    elenco->tail = NULL;
}

void enqueue(Elenco *elenco, Studente studente){
    Nodo *newnode = (Nodo *)malloc(sizeof(Nodo));

    newnode->studente = studente;
    newnode->next = NULL;

    if(elenco->tail == NULL){
	elenco->head = newnode;
	elenco->tail = newnode;
    } else {
	elenco->tail->next = newnode;
	elenco->tail = newnode;
    }
}

void load_students_from_file(Elenco *elenco, const char *filename){
    FILE *file = fopen(filename, "r");

    if(file == NULL){
	perror("");
	return;
    }

    char buffer[50];

    while(fgets(buffer, sizeof(buffer), file) != NULL){
	buffer[strcspn(buffer, "\n")] = '\0';

	Studente studente;

	strcpy(studente.matricola, buffer);

	fgets(buffer, sizeof(buffer), file);
	buffer[strcspn(buffer, "\n")] = '\0';
	strcpy(studente.nome, buffer);

	fgets(buffer, sizeof(buffer), file);
	buffer[strcspn(buffer, "\n")] = '\0';
	strcpy(studente.cognome, buffer);

	enqueue(elenco, studente);
    }

    fclose(file);
}

void write_students_on_file(Elenco *elenco, const char *filename, char start_letter, char stop_letter){
    FILE *file = fopen(filename, "w");

    if(file == NULL){
	perror("");
	return;
    }

    Nodo *nodocorrente = elenco->head;

    while(nodocorrente != NULL){
	char first_letter = nodocorrente->studente.cognome[0];

	if((first_letter >= start_letter && first_letter <= stop_letter) ||
	(first_letter >= toupper(start_letter) && first_letter <= toupper(stop_letter))){
	    fprintf(file, "%s\n%s\n%s\n", nodocorrente->studente.matricola, nodocorrente->studente.nome, nodocorrente->studente.cognome);
	}
	nodocorrente = nodocorrente->next;
    }
    fclose(file);
}




