#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int h[], int size, int i) {
    int largest = i;  
    int left = 2 * i + 1;  
    int right = 2 * i + 2;  

    if (left < size && h[left] > h[largest])
        largest = left;

    if (right < size && h[right] > h[largest])
        largest = right;

    if (largest != i) {
        swap(&h[i], &h[largest]);
        heapify(h, size, largest);
    }
}

void buildHeap(int h[], int size) {
    int i;
    for (i = size / 2 - 1; i >= 0; i--)
        heapify(h, size, i);
}

void heapSort(int h[], int size) {
    buildHeap(h, size);

    int i;
    for (i = size - 1; i >= 0; i--) {
        swap(&h[0], &h[i]);
        heapify(h, i, 0);
    }
}

void annulla_lavoro(int h[], int* heapsize, int el) {
    int i;
    for (i = 0; i < *heapsize; i++) {
        if (h[i] == el) {
            h[i] = h[*heapsize - 1];
            (*heapsize)--;
            heapify(h, *heapsize, i);
            return;
        }
    }
}

int main() {
    int h[] = {10, 5, 3, 4, 1};
    int heapsize = sizeof(h) / sizeof(h[0]);

    heapSort(h, heapsize);
    printf("Heap prima dell'annullamento: ");
    for (int i = 0; i < heapsize; i++) {
        printf("%d ", h[i]);
    }
    printf("\n");

    int el = 5;
    annulla_lavoro(h, &heapsize, el);

    printf("Heap dopo l'annullamento: ");
    for (int i = 0; i < heapsize; i++) {
        printf("%d ", h[i]);
    }
    printf("\n");

    return 0;
}

/*
La complessità di questa funzione dipende dalla complessità delle operazioni di ricerca dell'elemento el e di ordinamento dell'heap. 
La ricerca dell'elemento richiede un ciclo for che scorre l'array h, quindi ha una complessità di O(n), dove n è la dimensione dell'heap. 
L'ordinamento dell'heap utilizzando la funzione heapSort richiede O(n log n), dove n è la dimensione dell'heap.

Quindi, la complessità complessiva della funzione annulla_lavoro è O(n + n log n), che semplifica a O(n log n).
*/