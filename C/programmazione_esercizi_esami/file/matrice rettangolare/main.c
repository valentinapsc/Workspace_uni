#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    int n, m;
    int i, j;
    int **mat;
    int **out;

    if (fp == NULL) {
        printf("Errore\n");
        exit(-1);
    }

    fp = fopen("matrice.txt", "r");
    fscanf(fp, "%d %d", &m, &n);
    printf("%d %d\n", m, n);

    mat = (int **)malloc(m * sizeof(int *));

    for (i = 0; i < m; i++) {
        mat[i] = (int *)malloc(n * sizeof(int));
    }
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    fclose(fp);

    int nzeri = 0;

    for (i = 0; i < m; i++) {
        if (mat[i][0] == 0) {
            nzeri++;
        }
    }
    int mOut = m - nzeri;

    out = (int **)malloc(mOut * sizeof(int *));

    for (i = 0; i < mOut; i++) {
        out[i] = (int *)malloc(n * sizeof(int));
    }

    nzeri = 0;
    for (i = 0; i < m; i++) {
        if (mat[i][0] == 0) {
            nzeri++;
            continue;
        }
        for (j = 0; j < n; j++) {
            out[i - nzeri][j] = mat[i][j];
        }
    }

    int k;
    for (j = 0; j < n; j++) {
        for (i = 0; i < mOut / 2; i++) {
            k = out[i][j];
            out[i][j] = out[mOut - 1 - i][j];
            out[mOut - 1 - i][j] = k;
        }
    }

    fp = fopen("output.txt", "w");

    for (i = 0; i < mOut; i++) {
        for (j = 0; j < n; j++) {
            fprintf(fp, "%d ", out[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    
    return 0;
}
