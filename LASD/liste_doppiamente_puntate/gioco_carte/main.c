/*
Si implementi in linguaggio C un menù di scelta multipla per la simulazione di
un gioco che funzioni nel modo seguente:

1. Il gioco si svolge tra tre giocatori 
2. Ogni giocatore ha una lista di 5
numeri con valore compreso tra 1 e 10
3. Esiste inoltre una lista "monte" di 5 numeri piu' un "numero speciale" di
seguito spiegato

4. Ad ogni turno si gioca come segue:
 1. Si confrontano i valori in testa alle liste dei giocatori.
 2. Vince il giocatore che ha il numero maggiore
 3. Perde il giocatore che il numero minore
 4. Si pesca un num dalla testa del monte e si aggiunge in fondo alla lista
perdente
 5. Si sposta il num del giocatore vincente nel monte in posizione random.
 6. Vince il giocatore che svuota per primo la lista
 7. Se il giocatore i pesca il num speciale, i rimuove dai suoi numeri il minimo
(1 valore) che si inserisce nel monte. Il num speciale puo' essere usato una
sola volta e non va reinserito nel monte
 8. Casi speciali: vincono/perdono contemporaneamente piu' giocatori: si
sorteggia chi vince/perde il turno.

Si implementi un menu' che implementi

1. Il caricamento delle liste dei tre giocatori piu' la lista mone modo casuale.
2. Permette di evidenziare la situazione iniziale, e descriva ciò che succede ad
ogni turno
3. Mostri il giocatore vincente
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PLAYERS 3
#define NUM_NUMBERS 5
#define MAX_VALUE 10
#define NUM_SPECIAL 1

typedef struct {
    int numbers[NUM_NUMBERS];
} Player;

typedef struct {
    int numbers[NUM_NUMBERS + NUM_SPECIAL];
    int special_used;
} Monte;

void generateRandomNumbers(int* numbers, int num_elements, int max_value) {
    for (int i = 0; i < num_elements; i++) {
        numbers[i] = rand() % max_value + 1;
    }
}

void initializePlayers(Player* players, int num_players) {
    for (int i = 0; i < num_players; i++) {
        generateRandomNumbers(players[i].numbers, NUM_NUMBERS, MAX_VALUE);
    }
}

void initializeMonte(Monte* monte) {
    generateRandomNumbers(monte->numbers, NUM_NUMBERS, MAX_VALUE);
    monte->special_used = 0;
}

int findMinIndex(int* array, int num_elements) {
    int min_index = 0;
    for (int i = 1; i < num_elements; i++) {
        if (array[i] < array[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}

int findMaxIndex(int* array, int num_elements) {
    int max_index = 0;
    for (int i = 1; i < num_elements; i++) {
        if (array[i] > array[max_index]) {
            max_index = i;
        }
    }
    return max_index;
}

void shiftArrayRight(int* array, int start_index, int end_index) {
    for (int i = end_index; i > start_index; i--) {
        array[i] = array[i - 1];
    }
}

void shiftArrayLeft(int* array, int start_index, int end_index) {
    for (int i = start_index; i < end_index - 1; i++) {
        array[i] = array[i + 1];
    }
}

void playTurn(Player* players, Monte* monte, int num_players) {
    int min_index = findMinIndex(players[0].numbers, num_players);
    int max_index = findMaxIndex(players[0].numbers, num_players);

    if (players[min_index].numbers[0] == NUM_SPECIAL && monte->special_used == 0) {
        shiftArrayLeft(players[min_index].numbers, 0, NUM_NUMBERS);
        shiftArrayRight(monte->numbers, 0, NUM_NUMBERS);
        monte->numbers[0] = 1;
        monte->special_used = 1;
    } else {
        int number = players[max_index].numbers[0];
        shiftArrayLeft(players[max_index].numbers, 0, NUM_NUMBERS);
        shiftArrayRight(monte->numbers, 0, NUM_NUMBERS);
        monte->numbers[0] = number;
    }
}

int checkWinner(Player* players, int num_players) {
    for (int i = 0; i < num_players; i++) {
        if (players[i].numbers[0] == 0) {
            return i;
        }
    }
    return -1;
}

void printPlayers(Player* players, int num_players) {
    for (int i = 0; i < num_players; i++) {
        printf("Player %d: ", i + 1);
        for (int j = 0; j < NUM_NUMBERS; j++) {
            printf("%d ", players[i].numbers[j]);
        }
        printf("\n");
    }
}

void printMonte(Monte* monte) {
    printf("Monte: ");
    for (int i = 0; i < NUM_NUMBERS + NUM_SPECIAL; i++) {
        printf("%d ", monte->numbers[i]);
    }
    printf("\n");
}

int main() {
    srand(time(0));

    Player players[NUM_PLAYERS];
    Monte monte;

    initializePlayers(players, NUM_PLAYERS);
    initializeMonte(&monte);

    int turn = 1;
    int winner = -1;
    int choice;

    while (winner == -1) {
        printf("1. stampa i giocatori e il monte\n");
        printf("2. Gioca un turno\n");
        printf("3. Esci\n");
        printf("Inserire la scelta: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printPlayers(players, NUM_PLAYERS);
                printMonte(&monte);
                break;
            case 2:
                printf("Turno %d\n", turn);
                playTurn(players, &monte, NUM_PLAYERS);
                winner = checkWinner(players, NUM_PLAYERS);
                turn++;
                break;
            case 3:
                printf("Uscita...\n");
                return 0;
            default:
                printf("Scelta invalida. Riprovare.\n");
        }

        printf("\n");
    }

    printf("Il giocatore %d vince!\n", winner + 1);

    return 0;
}