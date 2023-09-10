#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Bacheca {
    char name[50];
    double x;
    double y;
    struct Bacheca *next;
};

int menuChoice() {
    int choice;
    printf("\n1: Leggere da lista gli oggetti da file\n");
    printf("\n2: Stampa\n");
    /*printf("\n3: Rimuovi\n");
    printf("\n4: Ordina\n");*/
    printf("\n5: Esci\n");
    printf("\n--------------------------------------\n");
    printf("Immetti una scelta:\t");
    scanf("%d", &choice);
    printf("\n");
    system("cls");
    return choice;
}

void cleanComma(char *string) {
    int i = 0;
    int writing = 0;

    while (string[i] != '\0') {
        // salto gli spazi non entrando in if
        if (string[i] != (',')) {
            string[writing] = string[i];
            writing++;
        }
        i++;
    }
    string[writing] = '\0';
}

struct Bacheca *creatNew(char *name, double x, double y) {
    struct Bacheca *element = NULL;
    element =
        malloc(sizeof(struct Bacheca));  // Alloco memoria dinamica per la struct

    strncpy(element->name, name, 50);
    element->x = x;
    element->y = y;

    return element;
}

void addElement(struct Bacheca **head, struct Bacheca *element) {
    // nodo usato per attraversare la lista
    struct Bacheca *prec = NULL;
    element->next = NULL;

    // se lista vuota
    if (*head == NULL) {
        *head = element;
    }
    // aggiungo in coda
    else {
        prec = *head;
        while (prec->next) prec = prec->next;
        prec->next = element;
    }
}

/*
void handleAdd(struct Room **head) {
    struct Room *new = createNew();
    addElement(head, new);
}
*/

int displayList(struct Bacheca *head) {
    int i = 1;
    printf("ID name\t\tx\t y\n");
    while (head != NULL) {
        printf("%d. %s\t%.2lf\t%.2lf\n", i, head->name, head->x, head->y);
        head = head->next;
        i++;
    }
    return i;
}

void list(struct Bacheca **head) {
    FILE *p;
    char name[50];
    char coordinate1[10], coordinate2[10];

    double x, y;
    char *endPtr;

    if ((p = fopen("file.csv", "r")) == NULL) {
        printf("il file non esiste!\n");
    } else {
        while (!feof(p)) {
            fscanf(p, "%s %s %s", name, coordinate1, coordinate2);
            cleanComma(name);
            cleanComma(coordinate1);
            cleanComma(coordinate2);
            x = strtod(coordinate1, &endPtr);
            y = strtod(coordinate2, &endPtr);
            printf("%s %.2lf %.2lf\n", name, x, y);
            struct Bacheca *new = creatNew(name, x, y);
            addElement(head, new);
        }
    }
    fclose(p);
}

struct Bacheca *delete(struct Bacheca *head) {}

int main() {
    struct Bacheca *head = NULL;

    while (1) {
        int menu = menuChoice();
        switch (menu) {
            case 1:
                list(&head);
                break;
            case 2:
                displayList(head);
                break;
            // case 3:
            //  rimuoviOggetto(&head);
            //  case 4:
            //  ordinamento(&head);
            case 6:
                exit(EXIT_SUCCESS);
            default:
                printf("comando non trovato!\n");
        }
    }
}