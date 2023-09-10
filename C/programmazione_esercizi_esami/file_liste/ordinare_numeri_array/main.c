#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} point;

typedef struct {
    int size;
    int capacity;
    point *values;
} list;

// Compute the polar angle in radians formed
// by the line segment that runs from p0 to p
double polarAngle(point p, point p0) { return atan2(p.y - p0.y, p.x - p0.x); }

// Determine the turn direction around the corner
// formed by the points a, b, and c. Return a
// positive number for a left turn and negative
// for a right turn.
double direction(point a, point b, point c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

int whereSmallest(point values[], int begin, int end, point p0) {
    point min = values[begin];
    int where = begin;
    int n;
    
    for (n = begin + 1; n < end; n++)
        if (polarAngle(values[n], p0) < polarAngle(min, p0)) {
            min = values[n];
            where = n;
        }
    return where;
}
void selectionSort(point values[], int N, point p0) {
    int n, s;
    point temp;

    for (n = 0; n < N; n++) {
        s = whereSmallest(values, n, N, p0);
        temp = values[n];
        values[n] = values[s];
        values[s] = temp;
    }
}

// Remove the last item from the list
void popBack(list *p) {
    int x;

    x = p->size - 1;
    p->values[x] = p->values[x + 1];
}

// Return the last item from the list
point getLast(list *p) {
    point value;

    value = p->values[p->size];
    return value;
}

// Return the next to the last item
point getNextToLast(list *p) {
    point value;

    value = p->values[p->size - 1];
    return value;
}

int main(int argc, const char *argv[]) {
    FILE *input;
    list *p;
    int N, n, x, y;

    /*Assuming that the first piece of data in the array indicates the amount of
     * numbers in the array then we record this number as a reference.*/
    N = 0;
    input = fopen("points.txt", "r");

    if (input == NULL) return -1;
    if (fscanf(input, "%d", &N) != 1) {
        fclose(input);
        return -1;
    }

    p = malloc(sizeof(*p));
    if (p == NULL) return -1;

    /*Now that we have an exact size requirement for our array we can use that
     * information to create a dynamic array.*/
    p->values = malloc(N * sizeof(point));
    p->capacity = N;
    p->size = 0;

    if (p->values ==
        NULL)  // As a safety precaution we want to terminate the program in
               // case the dynamic array could not be successfully created.
    {
        free(p);
        fclose(input);

        return -1;
    }

    /*Now we want to collect all of the data from our file and store it in our
     * array.*/
    for (n = 0; ((n < N) && (fscanf(input, "%d%d", &x, &y) == 2)); n++) {
        p->values[n].x = x;
        p->values[n].y = y;
        p->size += 1;
    }
    fclose(input);

    free(p->values);
    free(p);
    return 0;
}