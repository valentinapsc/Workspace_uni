#ifndef HEADERS_H
#define HEADERS_H

#define ERRFILE -1
#define OK 0

struct Partita
{
    char vincitore;
    char campo[3][3];
    int punteggio;
    
    
    struct Partita* successivo;
};

void init_partita(struct Partita* p_pa);

int free_positions(char* p_campo, int n);

int match_score(struct Partita p_pa);

char the_winner_is(char campo[3][3]);

void append_in_list(struct  Partita** pp_head, struct Partita ca);

int load_matches_from_file(char filename[], struct Partita** pp_head);

void print_match(struct Partita ca);

void print_list(struct Partita* p_head);

void free_list(struct  Partita* p_head);

void remove_tied(struct Partita** pp_head);

int write_winners_on_file(char filename[], struct  Partita* p_head, char winner);

void err_handler(int err);

#endif

