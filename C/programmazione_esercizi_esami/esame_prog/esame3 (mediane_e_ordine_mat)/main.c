// Valentina Piscopo

#include <stdio.h>
#include <stdlib.h>

float **matrix_alloc(int righe, int colonne);
float **read_file(int *m, int *n);
void print_matrix(float **mat, int righe, int colonne);
void print_array(float *arr, int size);
float *calcolo_mediane(float **mat, int righe, int colonne);
void write_file(float **mat, int righe, int colonne);
void bubbleSort(float *arr, int n);
void swap(float *a, float *b);
float *array_alloc(int size);
void arrangia_matrice(float **mat, float *mediane, int righe, int colonne);

int main(int argc, char const *argv[]) {
    int m, n;
    float **mat = read_file(&m, &n);
    print_matrix(mat, m, n);

    printf("\nMediane:\n");
    float *mediane = calcolo_mediane(mat, m, n);
    print_array(mediane, m);

    arrangia_matrice(mat, mediane, m, n);
    write_file(mat, m, n);
    return 0;
}

float **matrix_alloc(int righe, int colonne) {
    float **tmp = (float **)calloc(righe, sizeof(float *));
    if (tmp == NULL) {
        printf("Memoria non allocata");
        exit(-1);
    }
    for (int i = 0; i < colonne; i++) {
        tmp[i] = (float *)calloc(colonne, sizeof(float));
        if (tmp[i] == NULL) {
            printf("Memoria non allocata");
            exit(-1);
        }
    }

    return tmp;
}

float **read_file(int *m, int *n) {
    FILE *file;

    file = fopen("matrice.txt", "r");
    if (fopen == NULL) {
        printf("Erorre apertura file");
        exit(-1);
    }

    fscanf(file, "%d%d", m, n);

    float **mat = matrix_alloc(*m, *n);

    for (int i = 0; i < *m; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%f", &mat[i][j]);
        }
    }

    fclose(file);

    return mat;
}

void print_matrix(float **mat, int righe, int colonne) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            printf("%f ", mat[i][j]);
        }
        printf("\n");
    }
}

void print_array(float *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

float *array_alloc(int size) {
    float *arr = (float *)calloc(size, sizeof(float));
    if (arr == NULL) {
        printf("array non allocato");
        exit(-1);
    }
    return arr;
}

// restituisce un vettore contenente le mediane
float *calcolo_mediane(float **mat, int righe, int colonne) {
    float *mediane = array_alloc(righe);

    float *tmp = array_alloc(colonne);

    for (int i = 0; i < righe; i++) {
        // copio i valori della i-esima riga nel vettore temporaneo
        // cosi da non perdere l'ordine dei valori della matrice
        for (int j = 0; j < colonne; j++) {
            tmp[j] = mat[i][j];
        }

        // ordino il vettore temporaneo per calcolare la mediana
        bubbleSort(tmp, colonne);

        if (colonne % 2 == 0)
            mediane[i] = (tmp[colonne / 2] + tmp[colonne / 2 - 1]) / 2;
        else
            mediane[i] = tmp[colonne / 2];
    }

    return mediane;
}

void write_file(float **mat, int righe, int colonne) {
    FILE *file;

    file = fopen("output.txt", "w");
    if (fopen == NULL) {
        printf("Erorre apertura file");
        exit(-1);
    }

    fprintf(file, "%d %d\n", righe, colonne);
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            fprintf(file, "%f ", mat[i][j]);
        }
        fprintf(file, "\n");
    }
}

void bubbleSort(float *arr, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void swap(float *a, float *b) {
    float tmp = *a;
    *a = *b;
    *b = tmp;
}

// Punto C
void arrangia_matrice(float **mat, float *mediane, int righe, int colonne) {
    // indice del minimo del vettore mediane
    int min;
    for (int i = 0; i < righe; i++) {
        min = i;
        for (int z = i; z < righe; z++) {
            if (mediane[z] < mediane[min]) min = z;
        }

        // sposto il minimo cosi da escluderlo nel prossimo controllo
        float t = mediane[i];
        mediane[i] = mediane[min];
        mediane[min] = t;

        // scambio le righe
        float *tmp = mat[i];
        mat[i] = mat[min];
        mat[min] = tmp;
    }
}