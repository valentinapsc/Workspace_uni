#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *name;
    int number;
    struct Node *next;
};

struct Node *nameRecord;
struct Node *newRecord;

void printNameRecord() {
    struct Node *iterator = nameRecord;
    while (iterator != NULL) {
        printf("nome: %s\n", iterator->name);
        printf("numero: %d\n", iterator->number);
        iterator = iterator->next;
    }
}

void writeToFile() {
    FILE *fptr;
    fptr = fopen("rubrica.txt", "w");

    struct Node *iterator = nameRecord;

    if (fptr == NULL) {
        perror("");
    }

    else {
        while (iterator != NULL) {
            fprintf(fptr, "\nnome: %s\nnumero: %d\n", iterator->name, iterator->number);
            iterator = iterator->next;
        }
    }

    fclose(fptr);
}

int main() {
    int count, i;

    printf("quante persone vuoi aggiungere?\n");
    printf(":");
    scanf("%d", &count);

    for (i = 0; i < count; i++) {
        if (i == 0) {
            nameRecord = malloc(sizeof(struct Node));
            newRecord = nameRecord;
        } else {
            newRecord->next = malloc(sizeof(struct Node));
            newRecord = newRecord->next;
        }

        newRecord->name = malloc(50 * sizeof(char));

        printf("nome: ");
        scanf("%s", newRecord->name);
        printf("numero: ");
        scanf("%d", &newRecord->number);
    }

    newRecord->next = NULL;
    printf("\n\n");
    printNameRecord();
    writeToFile();
}