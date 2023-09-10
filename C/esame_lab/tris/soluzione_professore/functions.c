#include "headers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void init_partita(struct Partita* p_pa)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            p_pa->campo[i][j] = 0;
    
    p_pa->punteggio  = 0;
    p_pa->successivo = NULL;
}


int free_positions(char* p_campo, int n)
{
    if (n == 0)
        return 0;
    if (*p_campo == '@')
        return 1 + free_positions(p_campo+1, n-1);
    else
        return free_positions(p_campo+1,n-1);
}

int match_score(struct Partita p_pa)
{
    if(p_pa.vincitore == 'P')
        return 0;
    else
        return 3 + free_positions(p_pa.campo[0], 9);
}

char the_winner_is(char campo[3][3])
{
    
    // controllo righe
    for (int i = 0;  i < 3; i++)
    {
        if (campo[i][0] == campo[i][1] && campo[i][0] == campo[i][2])
            if (campo[i][0] == 'O' || campo[i][0] == 'X')
                return campo[i][0];
    }
    
    // controllo colonne
    for (int i = 0;  i < 3; i++)
    {
        if (campo[0][i] == campo[1][i] && campo[0][i] == campo[2][i])
            if (campo[0][i]== 'O' || campo[0][i] == 'X')
                return campo[0][i];
    }
    
    // controllo diagonale principale
    if (campo[0][0] == campo[1][1] && campo[1][1] == campo[2][2])
        if (campo[0][0]== 'O' || campo[0][0] == 'X')
                return campo[0][0]; 
    
    
    // controllo diagonale secondaria
    if (campo[0][2] == campo[1][1] && campo[1][1] == campo[2][0])
        if (campo[0][2]== 'O' || campo[0][2] == 'X')
                return campo[0][2]; 
    
    return 'P';
}

void append_in_list(struct  Partita** pp_head, struct Partita ca)
{
    if(*pp_head == NULL)
    {
      struct Partita* p_new = malloc(sizeof(struct Partita));
      *p_new                = ca; // copio i valori presi dal file 
                                  // nella nuova struct
      p_new->successivo     = NULL;
      *pp_head              = p_new;
      return;
        
    }
    append_in_list( &( (*pp_head)->successivo ), ca);
    
}


int load_matches_from_file(char filename[], struct Partita** pp_head)
{
  
    FILE* fp = fopen(filename, "r");  
    if (fp == NULL)
      return ERRFILE;

    // creo struttura temporanea
    struct Partita tmp;
    init_partita(&tmp);
    // leggo una tupla di valori dal file
    char line[10];
    while(fscanf(fp,"%s", line) == 1)  
    {
      strncpy(tmp.campo[0],line, 9);
      // calcolo il vincitore
      tmp.vincitore = the_winner_is(tmp.campo);
      // calcolo il punteggio
      tmp.punteggio = match_score(tmp);
      // inserisco il nodo nella lista
      append_in_list(pp_head, tmp);
    }  
    // 3. chiudo il file
    fclose(fp);

    return OK;

}

void print_match(struct Partita ca)
{
    printf("---------\n");
    printf("---------\n");
    if(ca.vincitore == 'P')
        printf("TIED!\n");
    else
        printf("%c WINS!\n", ca.vincitore);
    printf("SCORE: %d\n",ca.punteggio);
    printf("---------\n");
    for(int i = 0; i < 3; i++)
    {    
        for(int j = 0; j < 3; j++)
        {
            if (ca.campo[i][j] != '@')
                printf(" %c ", ca.campo[i][j]);
            else
                printf("   ");
        }
        printf("\n");
     }
    printf("---------\n");
}

void print_list(struct Partita* p_head)
{
    if (p_head == NULL)
        return;
    print_match(*p_head);
    print_list(p_head->successivo);

}

void free_list(struct  Partita* p_head)
{
    struct  Partita* tmp;
    while(p_head != NULL)
    {
        tmp = p_head->successivo;
        free(p_head);
        p_head = tmp;
    
    }

}

void remove_tied(struct Partita** pp_head)
{
    struct Partita* cursore = *pp_head;
    struct Partita* prec    = NULL;
    while(cursore != NULL)
    {
        if(cursore->vincitore == 'P')
        {
            struct Partita* to_del = cursore;
            if (prec == NULL)
                *pp_head = to_del->successivo;
            else
                prec->successivo = to_del->successivo;
            
            cursore = to_del->successivo;
            free(to_del);
        }
        else
        {
            prec    = cursore;
            cursore = cursore->successivo;
           
        }

    }

}

int write_winners_on_file(char filename[], struct  Partita* p_head, char winner)
{
    FILE* fp = fopen(filename, "w"); 
    if(fp == NULL)
        return ERRFILE;

        
    struct Partita* cursore  =  p_head;
    while( cursore !=  NULL )
    {

        if(cursore->vincitore == winner)
        {
           char line[10];
           line[9] = '\0';
           strncpy(line, cursore->campo[0], 9);
           fprintf(fp,"%s\n", line);
            
        }
        cursore = cursore->successivo;
    }


    fclose(fp);
    return OK;
    
}


void err_handler(int err)
{
    switch(err)
    {
        case OK: 
            printf("OK!\n");
        break;
        case ERRFILE: 
            printf("errore nella gestione del file!\n");
            exit(1);    
        default:
            printf("errore non gestito!\n");
            exit(1);
    }

}

