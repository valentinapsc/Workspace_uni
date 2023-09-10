/*il file IN contiene una sequenza di valori interi li ordini in senso
 decrescente quindi inserisci gli elementi nel file OUT */

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    int *s;    // puntatore array da leggere
    int size;  // dimensione di s
    int hold;  // array ordinato
    int i, j;

    if ((fp = fopen("IN.txt", "r")) == NULL) {
        perror("error");
        return -1;
    }

    fscanf(fp, "%d", &size);

    s = (int *)malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
        fscanf(fp, "%d", &s[i]);
    }

    for (i = 0; i < size; i++) {
        for (j = 0; j < size - 1; j++) {
            if (s[j] < s[j + 1]) {
                hold = s[j];
                s[j] = s[j + 1];
                s[j + 1] = hold;
            }
        }
    }

    fclose(fp);

    fp = fopen("OUT.txt", "w");
    for (i = 0; i < size; i++) {
        fprintf(fp, "%d ", s[i]);
    }

    fclose(fp);
    return 0;
}
