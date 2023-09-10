#define HEADERS 

typedef struct{
    char matricola[10];
    char nome[50];
    char cognome[50];
}Studente;

typedef struct nodo{
    Studente studente;
    struct nodo *next;
}Nodo;

typedef struct{
    Nodo *head;
    Nodo *tail;
}Elenco;

void initElenco(Elenco *elenco);
void enqueue(Elenco *elenco, Studente studente);
void load_students_from_file(Elenco *elenco, const char *filename);
void write_students_on_file(Elenco *elenco, const char *filename, char start_letter, char stop_letter);
