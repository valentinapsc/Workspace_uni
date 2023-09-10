#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    float v[1000], *w;
    int n, v_size;
    int i, j;
    int K, k1, k2;

    fp = fopen("sequenza.txt", "r");

    if (fp == NULL) {
        perror("Errore\n");
        exit(1);
    }

    printf("valore soglia: ");
    scanf("%d", &K);

    for (v_size = 0; v_size < 1000 && (fscanf(fp, "%f", &v[v_size]) != EOF);
         v_size++)
        ;

    int t = v_size;
    for (i = 0; i < t; i++) {
        if (v[i] < K) {
            v_size = v_size - 1;
            for (int j = i; j < t - 1; j++) {
                v[j] = v[j + 1];
            }
        }
    }


    do {
        printf("valore k1, k2: ");
        scanf("%d %d", &k1, &k2);

    } while (k1 >= k2);

    w = (float *)malloc(v_size * sizeof(float));
    for (i = 0; i < v_size; i++) {
    }

      int elementi_inseriti = 0;
    t = 0;
    for (i = 0; i < v_size; i++) {
        for (j = t; j < v_size; j++) {
            if (v[j] < k1) {
                w[i] = v[j];
                elementi_inseriti++;
                t = j + 1;
                break;
            }
        }
    }

    t = 0;
    for (i = elementi_inseriti; i < v_size; i++) {
        for (j = t; j < v_size; j++) {
            if (v[j] <= k2 && v[j] >= k1) {
                w[i] = v[j];
                elementi_inseriti++;
                t = j + 1;
                break;
            }
        }
    }

    t = 0;
    for (i = elementi_inseriti; i < v_size; i++) {
        for (j = t; j < v_size; j++) {
            if (v[j] > k2) {
                w[i] = v[j];
                t = j + 1;
                break;
            }
        }
    }

    for (int i = 0; i < v_size; i++) printf("%g ", v[i]);
    printf("\n");

    fclose(fp);

    fp = fopen("OUT.txt", "w");
    for (i = 0; i < v_size; i++) {
        fprintf(fp, "%g ", w[i]);
    }

    fclose(fp);
    
    return 0;
}
