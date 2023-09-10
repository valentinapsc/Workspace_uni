#include <stdio.h>
#include <stdlib.h>
#include "prototipi.h"
#include "strutture.h"

void load_matches_from_file(const char *NomeFile, struct elemento **inizio)
{
    FILE *fp;
    fp = fopen(NomeFile, "r");
    if (fp == NULL)
        gestisciErrore(ERRFILE);

    char tmpString[255];
    struct elemento tmp;
    while (fscanf(fp, "%s", tmpString) == 1)
    {
        int err = 0;

        err = fill_camp(&tmp, tmpString);
        gestisciErrore(err);

        tmp.vincitore = the_winner_is(tmp.campo);
        tmp.punteggio = match_score(tmp);
        tmp.prossimo = NULL;

        insert_in_list(inizio, tmp);
    }

    fclose(fp);
}

int fill_camp(struct elemento *tmp, char *tmpString)
{
    int i=0;
    int j=0;

    while (tmpString[LATOCAMPO*i + j] != '\0')
    {
        if (j==LATOCAMPO)
        {
            j=0;
            i++;
        }

        if (tmpString[LATOCAMPO*i + j] != 'X' && tmpString[LATOCAMPO*i + j] != 'O' && tmpString[LATOCAMPO*i + j] != '@')
            return ERRFORMAT;
        tmp->campo[i][j] = tmpString[LATOCAMPO*i + j];
        j++;
    }

    if (i != LATOCAMPO && j != LATOCAMPO)
        return ERRFORMAT;
    else
        return OK;
}

char the_winner_is(char campo[LATOCAMPO][LATOCAMPO])
{
    for (int i=0; i<LATOCAMPO; i++)
    {
        for (int j=0; j<LATOCAMPO; j++)
        {
            if (campo[i][j] != '@')
            {
                //Controllo se la vittoria è stata fatta con tre elementi orizzontali
                if (j>1 && (campo[i][j] == campo[i][j-1] && campo[i][j] == campo[i][j-2]))
                    return campo[i][j];
                //Controllo se la vittoria è stata fatta con tre elementi verticali
                if (i>1 && (campo[i][j] == campo[i-1][j] && campo[i][j] == campo[i-2][j]))
                    return campo[i][j];
                //Controllo se la vittoria è stata fatta con tre elementi sulla diagonale principale
                if (i>1 && j>1 && i==j && (campo[i][j] == campo[i-1][j-1] && campo[i][j] == campo[i-2][j-2]))
                    return campo[i][j];
                //Controllo se la vittoria è stata fatta con tre sulla diagonale secondaria
                if (i>1 && j+2<LATOCAMPO && (campo[i][j] == campo[i-1][j+1] && campo[i][j] == campo[i-2][j+2]))
                    return campo[i][j];
            }
        }
    }

    return 'P';
}

int match_score(struct elemento nodo)
{
    char winner = nodo.vincitore;
    if (winner == 'P')
    {
        return 0;
    } else {
        //FREE_POSITIONS RICORSIVO
        return 3 + free_positions(nodo.campo, LATOCAMPO, LATOCAMPO);
        //FREE_POSITIONS NON RICORSIVO
        //return 3 + free_positions(nodo.campo);
    }
}

//FREE_POSITIONS RICORSIVO
int free_positions(char campo[LATOCAMPO][LATOCAMPO], int r, int c)
{
    int punteggio = 0;
    for (int i=0; i<c; i++)
    {
        if (campo[0][i] == '@')
            punteggio++;
    }

    if(r == 0)
        return punteggio;
    return free_positions(campo+1, r-1, c) + punteggio;

}

/*
//FREE_POSITIONS NON RICORSIVO
int free_positions(char campo[LATOCAMPO][LATOCAMPO])
{
    int numPos = 0;

    for (int i=0; i<LATOCAMPO; i++)
    {
        for (int j=0; j<LATOCAMPO; j++)
        {
            if (campo[i][j] == '@')
            {
                numPos = numPos + 1;
            }
        }
    }

    return numPos;
}
*/

void insert_in_list(struct elemento **inizio, struct elemento tmp)
{
    struct elemento *nuovo = malloc(sizeof(struct elemento));
    if (nuovo == NULL)
        gestisciErrore(ERRMEM);
    
    *nuovo = tmp;

    struct elemento *precedente = NULL;
    struct elemento *cursore = *inizio;

    while (cursore != NULL)
    {
        precedente = cursore;
        cursore = cursore->prossimo;
    }

    if (precedente == NULL)
        *inizio = nuovo;
    else
        precedente->prossimo = nuovo;
}

void print_list(struct elemento *inizio)
{
    if (inizio == NULL)
    {
        return;
    }

    print_match(inizio);
    print_list(inizio->prossimo);
    return;
}

void print_match(struct elemento *inizio)
{
    if (inizio->vincitore == 'P')
    {
        printf ("Pareggio\n");
    } else {
        printf ("Vincitore: %c\n", inizio->vincitore);
        printf ("Punteggio: %d\n", inizio->punteggio);
    }

    printf("Campo:\n");
    print_matrix(inizio->campo);
    printf ("\n");
}

void print_matrix(char matrice[LATOCAMPO][LATOCAMPO])
{
    for (int i=0; i<LATOCAMPO; i++)
    {
        for (int j=0; j<LATOCAMPO; j++)
        {
            if (matrice[i][j] == '@')
                printf ("| ");
            else
                printf ("|%c", matrice[i][j]);
        }
        printf ("|\n");
    }
}

void remove_tied (struct elemento **inizio)
{
    struct elemento *precedente = NULL;
    struct elemento *cursore = *inizio;

    while (cursore != NULL)
    {
        if (cursore->vincitore == 'P')
        {
            struct elemento *tmp = cursore->prossimo;
            free(cursore);
            if (precedente == NULL)
                *inizio = tmp;
            else
                precedente->prossimo = tmp;
            cursore = tmp;
        } else {
            precedente = cursore;
            cursore = cursore->prossimo;
        }
    }
}

void write_winners_on_file(const char *NomeFile, struct elemento *inizio, char player)
{
    FILE *fp;
    fp = fopen(NomeFile, "w");
    if (fp == NULL)
        gestisciErrore(ERRFILE);

    int scritti = 0;
    while (inizio != NULL)
    {
        if (inizio->vincitore == player)
        {
            if (scritti != 0)
                fprintf(fp, "\n");
            for (int i=0; i<LATOCAMPO; i++)
            {
                for (int j=0; j<LATOCAMPO; j++)
                {
                    fprintf(fp, "%c", inizio->campo[i][j]);
                }
            }
            scritti++;
        }

        inizio = inizio->prossimo;
    }

    fclose(fp);
}

void freeLista(struct elemento *inizio)
{
    while (inizio != NULL)
    {
        struct elemento *tmp = inizio->prossimo;
        free(inizio);
        inizio = tmp;
    }
}

void gestisciErrore(int err)
{
    switch (err)
    {
        case OK:
            break;
        case ERRFILE:
            printf ("Errore in apertura file\n");
            exit(-1);
            break;
        case ERRFORMAT:
            printf ("File mal formattato\n");
            exit(-1);
            break;
        case ERRMEM:
            printf ("Errore in allocazione memoria\n");
            exit(-1);
            break;
        default:
            printf ("Codice errore non riconosciuto. Codice: %d\n", err);
            exit(-1);
            break;
    }
}