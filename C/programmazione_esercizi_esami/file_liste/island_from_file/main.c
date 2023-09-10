#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct island {
    char *name;
    struct island *nextIsland;
} island;

void printIsland(island *head) {
    printf("%s\n", head->name);

    if (head->name != NULL) {
        printIsland(head->nextIsland);
    }
}

island *file_reader(FILE *file) {
    island *head = (island *)malloc(sizeof(island));
    char islandName[20];
    int fileRead = fscanf(file, "%s", islandName);

    if (fileRead != EOF) {
        head->name = strdup(islandName);
        head->nextIsland = file_reader(file);
    }

    if (fileRead == EOF) {
        return NULL;
    }

    return head;
}

int main() {
    FILE *fptr  = fopen("file.txt", "r");
    
    island *head = file_reader(fptr);
    printIsland(head);
    fclose(fptr);
}