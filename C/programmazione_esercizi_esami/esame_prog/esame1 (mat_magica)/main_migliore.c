#include <stdio.h>
#include <stdlib.h>

void print_array(int *arr, int arr_size);
void print_matrix(int *mat, int rows, int columns);
int all_values_same(int *arr, int arr_size, int item);

int main() {
    // righe
    int r;

    // colonne
    int c;

    // indici
    int i, j;

    // 1 è magica - 0 non è magica
    int magica = 1;

    // array grande r
    // contiene la somma delle righe
    int *sr;

    // array grande c
    // contiene la somma delle colonne
    int *sc;

    // matrice grande [r] righe e [c] colonne
    int *matrice;

    // contiene la somma delle diagonali
    int sd[2] = {0, 0};

    FILE *fp;

    fp = fopen("matrice.txt", "r");
    if (fp == NULL) {
        printf("Impossibile aprire il file");
        return -1;
    }

    fscanf(fp, "%d", &r);
    fscanf(fp, "%d", &c);

    sr = (int *)calloc(r, sizeof(int));
    sc = (int *)calloc(c, sizeof(int));

    matrice = (int *)calloc(r * c, sizeof(int));
    if (matrice == NULL) {
        printf("Memoria non allocata");
        exit(1);
    }

    // riempio matrice
    while (!feof(fp)) {
        int value;
        fscanf(fp, "%d", &value);
        fscanf(fp, "%d", &i);
        fscanf(fp, "%d", &j);
        i--;
        j--;
        matrice[i * c + j] = value;
    }

    // controllo se tutti gli elementi sono diversi
    for (i = 0; (i < r * c) && (magica == 1); i++) {
        for (j = 0; (j < r * c) && (i != j) && (magica == 1); j++) {
            if (matrice[i] == matrice[j]) magica = 0;
        }
    }

    // calcolo la somma di righe, colonne e diagonali
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            int index = i * c + j;

            sr[i] += matrice[index];
            sc[j] += matrice[index];

            if (i == j) sd[0] += matrice[index];
            if ((i + j) == r - 1) sd[1] += matrice[index];
        }
    }

    // controllo se gli elementi sono divisibili per i && j
    for (i = 0; i < r; i++) {
        if (i == 0) continue;
        for (j = 0; j < c; j++) {
            if (j == 0) continue;
            int index = i * c + j;

            if (((matrice[index] % i) == 0) && ((matrice[index] % j) == 0))
                matrice[index] = 0;
        }
    }

    magica = magica && all_values_same(sr, r, sr[0]) &&
             all_values_same(sc, c, sr[0]) && all_values_same(sd, 2, sr[0]);
    printf("Magica: %s\n\n", magica ? "si" : "no");

    printf("Somma righe:\n");
    print_array(sr, r);

    printf("Somma colonne:\n");
    print_array(sc, c);

    printf("Somma diagonali:\n");
    print_array(sd, 2);

    fclose(fp);
    fp = fopen("output.txt", "w");
    if (fp == NULL) {
        printf("Impossibile aprire il file");
        return -1;
    }

    fprintf(fp, "%d %d\n", r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            fprintf(fp, "%d %d %d\n", matrice[i * r + j], i, j);
        }
    }

    free(sr);
    free(sc);
    free(matrice);

    return 0;
}

int all_values_same(int *arr, int arr_size, int item) {
    for (int i = 0; i < arr_size; i++) {
        if (arr[i] != item) return 0;
    }
    return 1;
}

void print_array(int *arr, int arr_size) {
    for (int i = 0; i < arr_size; i++) printf("%d ", arr[i]);
    printf("\n\n");
}

void print_matrix(int *mat, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", mat[i * columns + j]);
        }
        printf("\n");
    }
    printf("\n");
}