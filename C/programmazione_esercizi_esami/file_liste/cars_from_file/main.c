#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cars Cars_t, *pCars_t;
struct Cars {
    char brand[30], model[30];
    int year;
    float engine;

    pCars_t next;
};

void load_cars(Cars_t *head) {
    Cars_t *temp = head;
    Cars_t *previous = NULL; 

    FILE *fptr = fopen("cars.txt", "r");
    if (fptr != NULL) {

        while (fscanf(fptr, "%s%s%d%f", temp->brand, temp->model, &(temp->year), &(temp->engine)) == 4) {

            temp->next = malloc(sizeof(Cars_t));

            if (temp->next == NULL) {
                fprintf(stderr, "Allocation error!\n");
                exit(1);
            }

            previous = temp; 
            temp = temp->next;
        }
        
        temp->next = NULL;
        free(previous->next);  
        previous->next = NULL;

    } else {
        fprintf(stderr, "File problem!");
        return;
    }
    fclose(fptr);
}

void print_list(Cars_t *head) {
    Cars_t *current = head;

    while (current != NULL) {
        printf("%s\t%s\t%d\t%.2f\n", current->brand, current->model,
               current->year, current->engine);
        current = current->next;
    }
}

int main() {
    pCars_t head = malloc(sizeof(Cars_t));
    if (head == NULL) {
        fprintf(stderr, "Allocation error!\n");
        return 1;
    }
    load_cars(head);
    print_list(head);

    return 0;
}