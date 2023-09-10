#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char country[20];
    char capital[20];
    int population;
    int driving_side; // 1:destra 0: sinistra
} node;

typedef struct node1 {
    char country[20];
    char capital[20];
    int population;
    int driving_side; // 1:destra 0: sinistra
    struct node1* next;
} node1;

void addList(node** country, int i) {
    int leftOrRight; /* aggiunge gli elementi alla struct */

    printf("Nome del paese: ");
    scanf("%s", (*country[i]).country);

    printf("\nCapitale: ");
    scanf("%s", (*country[i]).capital);

    printf("\nPopolazione di %s : ", (*country[i]).country);
    scanf("%d", &(*country[i]).population);

    printf("\nLe persone di %s guidano a destra? (Si: 1, No: 0) : ", (*country[i]).country);
    scanf("%d", &leftOrRight);

    if (leftOrRight == 1) {
        (*country[i]).driving_side = 1;
    } else {
        (*country[i]).driving_side = 0;
    }
}

void createFile(node** country, int i) {
    FILE* fp = fopen("countries.txt", "w");
    int j;

    for (j = 0; j < i; j++) { /* scrive gli elementi nel file */
        fprintf(fp, "%s %s %d ", (*country[i]).country, (*country[i]).capital,(*country[i]).population);

        if ((*country[i]).driving_side == 1) {
            fprintf(fp, "Destra");
        } else {
            fprintf(fp, "Sinistra");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void append(node1** head_ref, char country[20], char capital[20], int population, int driving_side) {
    /* 1. alloca il nodo */

    node1* new_node = (node1*)calloc(1, sizeof(node1));
    node1* last = *head_ref; /* usato nello step 5*/

    /* 2. mette nell'elemento  */
    strcpy(new_node->country, country);
    strcpy(new_node->capital, capital);

    new_node->population = population;
    new_node->driving_side = driving_side;

    /* 3. questo nuovo nodo sarà l'ultimo, quindi quello che lo seguirà sarò NULL*/
    new_node->next = NULL;

    /* 4. se la lista è vuota, metti il nuovo nodo come testa */
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    /* 5. altrimenti attraversalo fino all'ultimo nodo */
    while (last->next != NULL) last = last->next;

    /* 6. cambia il campo next dell'ultimo nodo */
    last->next = new_node;
    return;
}

void createList(int count, node1** head) {
    FILE* fp = fopen("countries.txt","r"); 
    /* legge gli elementi dal file con fgets riga per riga e analizza i dati con sscanf*/

    char country[20];
    char capital[20];
    int population;
    int driving_side;
    char d[5];
    int j;
    char temp[100];

    for (j = 0; j < count; j++) {
        fgets(temp, 100, fp); /* assegna l'elemento a fgets */

        sscanf(temp, "%s %s %d %s", country, capital, &population, d);

        if (strcmp(d, "right") == 0) {
            driving_side = 1;
        } else {
            driving_side = 0;
        }

        append(head, country, capital, population, driving_side); 
        /* appending il nodo alla fine della lista */
    }
    fclose(fp);
}

void printList(node1* head) {
    while (head != NULL) /* stampa la lista*/
    {
        printf(" Paese: %s Capitale: %s Popolazione: %d", head->country, head->capital, head->population);
               
        if (head->driving_side == 1) {
            printf("Senso di guida: destra\n");
        } else {
            printf("Senso di guida: sinistra\n");
        }
        head = head->next; /* sposta la testa al prossimo nodo */
    }
}

int main() {
    int i = 0, choice, count = 1;
    node1* head = NULL;

    int a;
    node* country = (node*)calloc(100, sizeof(node));

    while (1) {
        printf("\nMENU\n");
        printf("\n1: Inserire nuova registrazione ");
        printf("\n2: Scrivi sul file ");
        printf("\n3: Leggi dal file ");
        printf("\n4: Stampa la lista ");
        printf("\n5: Exit\n");
        printf("La tua scelta ");
        scanf("%d", &choice);

        if (choice == 1) {
            count + 1;
            country = (node*)realloc(country, sizeof(node) * count);
            addList(&country, i);
            i++;
        } else if (choice == 2) {
            createFile(&country, i);
        } else if (choice == 3) {
            createList(count, &head);
        } else if (choice == 4) {
            printList(head);
        } else if (choice == 5) {
            exit(1);
        }
    }
    return 0;
}