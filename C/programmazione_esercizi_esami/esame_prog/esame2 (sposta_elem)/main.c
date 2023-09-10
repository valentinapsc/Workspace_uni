// Piscopo Valentina

#include <stdio.h>
#include <stdlib.h>

float *read_file(char *file_name, int *data_size);

void write_file(char *, float *, int);
void print_array(float *, int);
void sposta_elementi(float *, int, int, int);
float *alloca_matrice(int);

int main(int argc, char const *argv[]) {
    float *data;
    int data_size;

    int S1, S2;

    printf("Inserisci S1: ");
    scanf("%d", &S1);

    printf("Inserisci S2: ");
    scanf("%d", &S2);

    // controllo indici
    if (S1 > S2) {
        printf("S1 deve essere minore di S2\n");
        return 0;
    }

    data = read_file("dati.txt", &data_size);

    print_array(data, data_size);

    sposta_elementi(data, data_size, S1, S2);
    write_file("output.txt", data, data_size);

    return 0;
}

float *alloca_matrice(int data_size) {
    return (float *)malloc(data_size * sizeof(float));
}

float *read_file(char *file_name, int *data_size) {
    FILE *file;

    if ((file = fopen(file_name, "r")) == NULL) {
        perror("");
        exit(-1);
    }

    fscanf(file, "%d", data_size);

    float *temp_vett = alloca_matrice(*data_size);

    for (int i = 0; i < *data_size; i++) {
        fscanf(file, "%f", &temp_vett[i]);
    }

    fclose(file);

    return temp_vett;
}

// stampa l'array
void print_array(float *data, int data_size) {
    printf("%d\n", data_size);
    for (int i = 0; i < data_size; i++) printf("%g\t", data[i]);
    printf("\n");
}

// sposta gli elementi
void sposta_elementi(float *data, int data_size, int S1, int S2) {
    float *tmp = (float *)calloc(data_size, sizeof(float));
    int i;

    // conta rispettivamente: v < s1,  s1 < v < s2,  v > s2
    int x = 0, y = 0, z = 0;

    if (tmp == NULL) {
        printf("Allocazione fallita");
        exit(-1);
    }

    for (i = 0; i < data_size; i++) {
        if (data[i] <= S1) {
            tmp[x] = data[i];
            x++;
        }
    }

    y = x;
    for (i = 0; i < data_size; i++) {
        if (data[i] <= S2 && data[i] > S1) {
            tmp[y] = data[i];
            y++;
        }
    }

    z = y;
    for (i = 0; i < data_size; i++) {
        if (data[i] > S2) {
            tmp[z] = data[i];
            z++;
        }
    }

    for (i = 0; i < data_size; i++) data[i] = tmp[i];

    free(tmp);
}

void write_file(char *file_name, float *data, int data_size) {
    FILE *file;

    if ((file = fopen(file_name, "w")) == NULL) {
        perror("");
        exit(-1);
    }
    int i = 0;
    fprintf(file, "%d\n", data_size);
    for (i = 0; i < data_size; i++) fprintf(file, "%g ", data[i]);
    fclose(file);
}