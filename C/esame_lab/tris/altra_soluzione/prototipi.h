#ifndef PROTOTIPI
#define PROTOTIPI

//#include "strutture.h"
#define LATOCAMPO 3
#define OK 1
#define ERRFILE 2
#define ERRFORMAT 3
#define ERRMEM 4

struct elemento;

void load_matches_from_file(const char *NomeFile, struct elemento **inizio);
int fill_camp(struct elemento *tmp, char *tmpString);
char the_winner_is(char campo[LATOCAMPO][LATOCAMPO]);
int match_score(struct elemento nodo);
//FREE_POSITIONS RICORSIVO
int free_positions(char campo[LATOCAMPO][LATOCAMPO], int r, int c);
//FREE_POSITIONS NON RICORSIVO
//int free_positions(char campo[LATOCAMPO][LATOCAMPO]);
void insert_in_list(struct elemento **inizio, struct elemento tmp);

void print_list(struct elemento *inizio);
void print_match(struct elemento *inizio);
void print_matrix(char matrice[LATOCAMPO][LATOCAMPO]);

void remove_tied (struct elemento **inizio);

void write_winners_on_file(const char *NomeFile, struct elemento *inizio, char player);
void freeLista(struct elemento *inizio);
void gestisciErrore(int err);

#endif