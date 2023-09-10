#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 256

int load_sentence_in_memory(char filename[], char FRASI[][MAX_LEN], int* n_frasi) {
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        return -1;
    }

    *n_frasi = 0;
    
    while(fgets(FRASI[*n_frasi], MAX_LEN, fp))
    {
        // pulisci da \n
        int i = 0;
        while(FRASI[*n_frasi][i] !='\0')
        {
            if(FRASI[*n_frasi][i]=='\n')
                FRASI[*n_frasi][i] = '\0';
            i++;
        }
        (*n_frasi)++;
    }

    fclose(fp);
    return 1;
}

//prende la stringa da indovinare e la mostra tramite '*'
void show_phrase(char frase[MAX_LEN], int flags[MAX_LEN]) {
    int i = 0;

    while (frase[i] != '\0') {

        //se la lettera non è stata trovata (controllo con flag) si stampano '*' altrimenti si sostituisce al carattere trovato
        if (flags[i] == 0 && ((frase[i] >= 'A' && frase[i] <= 'Z') || (frase[i] >= 'a' && frase[i] <= 'z')))
            printf("*");
        else
            printf("%c", frase[i]);
        i++;
    }
    printf("\n");
}

char to_lower(char c) {
    if (c >= 'a' && c <= 'z')
        return c;
    else
        return c + 32;
}

//verifica singolarmente se la lettera data dall'utente è presente nella stringa da indovinare
int verifica_se_in_stringa(char fraseDaIndovinare[], char playerLetter, int idxs[]) {
    int n_idxs = 0;
    int i = 0;

    while (fraseDaIndovinare[i] != '\0') {

        if (to_lower(fraseDaIndovinare[i]) == to_lower(playerLetter)) {
            idxs[n_idxs] = i;
            n_idxs++;
        }
        i++;
    }
    return n_idxs; //ritorna quante lettere sono state trovate
}

//confronta la stringa data dall'utente con quella da indovinare
int chek_player_solution(char fraseDaIndovinare[], char playerGuess[]) {
    int corretta = 1;
    int i = 0; //indice per salvare i caratteri uguali consecutivi

    while (fraseDaIndovinare[i] != '\0' && playerGuess[i] != '\0' && to_lower(fraseDaIndovinare[i]) == to_lower(playerGuess[i]))
        i++;

    if (to_lower(fraseDaIndovinare[i]) != to_lower(playerGuess[i])) corretta = 0;

    return corretta;
}

int main() {
    srand(time(NULL));
    char fraseDaIndovinare[100][MAX_LEN];
    int n_frasi;

    load_sentence_in_memory("wordlist.txt", fraseDaIndovinare, &n_frasi);

    int idx_frase_scelta = rand() % 10 + 1;

    int flags[MAX_LEN] = {0};

    int tries = 5;
    int playerChoice = -1;

    printf("\n\n hai 5 possibilita' per indovinare la frase, quando sei pronto premi enter ");
    getchar();

    system("cls");

    while (tries > 0 && playerChoice != 0) {

        show_phrase(fraseDaIndovinare[idx_frase_scelta], flags); //mostra inizialmente '*' se si indovina la lettera si sostituisce

        printf("tentativi residui: %d\n", tries);

        printf("\npuoi inserire:\n1) se vuoi continuare a dare una lettera\n2) se credi di aver capito la frase, ma non penso\n0) se vuoi uscire (raccomandato) \n");
        printf("==> ");
        scanf("%d", &playerChoice);

        //scelta 1
        if (playerChoice == 1) {
            char playerLetter; // lettera inserita dall'utente

            printf("inserisci una lettera\n");
            getchar();
            scanf("%c", &playerLetter);

            int idxs[256];
            int n_idxs = verifica_se_in_stringa(fraseDaIndovinare[idx_frase_scelta], playerLetter, idxs);

            for (int i = 0; i < n_idxs; i++) flags[idxs[i]] = 1; //flag = 1 se la lettera è stata trovata

            if (n_idxs == 0) {
                printf("indovinta un po', lettera sbagliata\n\n");
                tries--;
            }

        //scelta 2
        } else if (playerChoice == 2) {
            char playerGuess[MAX_LEN];

            printf("dai allora, prova a dare la soluzione:\n");
            getchar();
            scanf("%[^\n]s", playerGuess);

            printf("hai inserito \"%s\"\n", playerGuess);

            int vinto = chek_player_solution(fraseDaIndovinare[idx_frase_scelta], playerGuess);
            //una volta confrontata la frase tramite la flag vinto si decide l'esito

            if (vinto == 1) {
                printf("ok, bravo, hai indovintao\n\n");
                playerChoice = 0; //se la frase è giusta si imposta la scelta del giocatore a zero così da far finire il gioco
                
            } else {

                printf("eh no, coglione, hai sbagliato\n\n");
                tries--;
            }

        } else if (playerChoice != 0) {
            printf("scelta sbagliata :/\nripeti e non sbagliare di nuovo\n\n");
        }
    }

    //se arriviamo alla fine dei tentativi rimasti il giocatore ha perso
    if (tries <= 0) printf("hai perso!\n");
    printf("la frase e' %s\n", fraseDaIndovinare[idx_frase_scelta]);
}