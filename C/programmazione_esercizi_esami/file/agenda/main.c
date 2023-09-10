#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getDay(char *str) {
    if (strcmp("Lunedi'", str) == 0)
        return 1;
    else if (strcmp("Martedi'", str) == 0)
        return 2;
    else if (strcmp("Mercoledi'", str) == 0)
        return 3;
    else if (strcmp("Giovedi'", str) == 0)
        return 4;
    else if (strcmp("Venerdi'", str) == 0)
        return 5;
    else if (strcmp("Sabato", str) == 0)
        return 6;
    else
        return 7;
}

int main() {
    FILE *fp;
    int v, i, j;
    char ***str;

    fp = fopen("agenda.txt", "r");
    fscanf(fp, "%d", &v);

    str = (char ***)malloc(v * sizeof(char **));
    for (i = 0; i < v; i++) {
        str[i] = (char **)malloc(9 * sizeof(char *));
        for (j = 0; j < 9; j++) {
            str[i][j] = (char *)malloc(30 * sizeof(char));}
    }

    for (i = 0; i < v; i++) {
        fscanf(fp, "%s %s %s %s %s %s %s %s %s", str[i][0], str[i][1],
               str[i][2], str[i][3], str[i][4], str[i][5], str[i][6], str[i][7],
               str[i][8]);
    }

    int startingDay;   // str[i][2]
    int endingDay;     // str[i][6]
    int startingHour;  // str[i][4]
    int endingHour;    // str[i][8]

    int *durata = (int *)malloc(v * sizeof(int));
    for (i = 0; i < v; i++) {
        startingDay = getDay(str[i][2]);
        endingDay = getDay(str[i][6]);
        startingHour = atoi(str[i][4]);
        endingHour = atoi(str[i][8]);

        durata[i] = (24 - startingHour) + endingHour;
        if (startingDay != endingDay)
            durata[i] += (endingDay - startingDay - 1) * 24;
    }

    int max = 0;
    for (i = 1; i < v; i++) {
        if (durata[i] > durata[max]) max = i;
    }
 printf( "%s %s %s %s %s %s %s %s %s. Durata %d ore", str[max][0], str[max][1],
               str[max][2], str[max][3], str[max][4], str[max][5], str[max][6], str[max][7],
               str[max][8], durata[max]);


}
