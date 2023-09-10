#ifndef HEADER
#define HEADER

void load_players_from_file(const char *NomeFile, struct Giocatore **inizio);
void appendInList(struct Giocatore **inizio, struct Giocatore tmp);

void print_player (struct Giocatore g);
void print_list (struct Giocatore *inizio);

void expels(struct Giocatore **inizio);
int compute_points(int *valori, int n);

struct Giocatore *the_winner_is(struct Giocatore *inizio);

void write_ranking_on_file(const char *NomeFile, struct Giocatore *inizio);
int contaLista(struct Giocatore *inizio);

void GestisciErrore(int err);
void freeList(struct Giocatore *inizio);

#endif