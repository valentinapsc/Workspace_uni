#include <stdio.h>
#include <stdlib.h>

struct Node {
    char *name;
    int age;
    struct Node *next;
};

struct Node *petRecord;
struct Node *newRecord;

void printPetRecord() {
    struct Node *iterator = petRecord;
    while (iterator != NULL) {
        printf("nome animale: %s\n", iterator->name);
        printf("eta' animale: %d\n", iterator->age);
        iterator = iterator->next;
    }
}

void writeToFile() {
    FILE *fptr;
    fptr = fopen("petnames.txt", "w");
    
    struct Node *iterator = petRecord;

    if (fptr == NULL) {
        printf("Error\n");
    }

    else {
        while (iterator != NULL) {
            fprintf(fptr, "\nnome animale: %s\neta' animale: %d\n", iterator->name,
                    iterator->age);
            iterator = iterator->next;
        }
    }

    fclose(fptr);
}

int main() {
    int count, i;

    printf("quanti animali hai?\n");
    printf(":");
    scanf("%d", &count);

    for (i = 0; i < count; i++) {
        if (i == 0) {
            petRecord = malloc(sizeof(struct Node));
            newRecord = petRecord;
        } else {
            newRecord->next = malloc(sizeof(struct Node));
            newRecord = newRecord->next;
        }

        newRecord->name = malloc(50 * sizeof(char));

        printf("nome animale: : ");
        scanf("%s", newRecord->name);
        printf("eta' animale: ");
        scanf("%d", &newRecord->age);
    }

    newRecord->next = NULL;
    printf("\n\n");
    printPetRecord();
    writeToFile();
}