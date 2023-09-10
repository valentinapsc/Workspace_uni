#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    Elenco elenco;

    initElenco(&elenco);

    load_students_from_file(&elenco,"iscritti.txt");

    Elenco gruppo1, gruppo2, gruppo3;

    initElenco(&gruppo1);
    initElenco(&gruppo2);
    initElenco(&gruppo3);

    Nodo *nodocorrente = elenco.head;

    while(nodocorrente != NULL){
	char first_letter = nodocorrente->studente.cognome[0];

	if((first_letter >= 'a' && first_letter <= 'g') || (first_letter >= 'A' && first_letter <= 'G')){
	    enqueue(&gruppo1, nodocorrente->studente);
	} else if((first_letter >= 'h' && first_letter <= 'p') || (first_letter >= 'H' && first_letter <= 'P')){
	    enqueue(&gruppo2, nodocorrente->studente);
	} else if((first_letter >= 'q' && first_letter <= 'z') || (first_letter >= 'Q' && first_letter <= 'Z')){
	    enqueue(&gruppo3, nodocorrente->studente);
	}
	nodocorrente = nodocorrente->next;
    }

    write_students_on_file(&gruppo1, "gruppo1.txt", 'a', 'g');
    write_students_on_file(&gruppo2, "gruppo2.txt", 'h', 'p');
    write_students_on_file(&gruppo3, "gruppo3.txt", 'q', 'z');

    return 0;
}
