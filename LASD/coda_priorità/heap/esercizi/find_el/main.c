/*
Si consideri una coda di priorità per la gestione della coda di stampa di una
rete implementata con una struttura heap h[MAX] 
implemetare le seguenti funzioni: 
- void heapify(int h[MAX], int el) dove el è un indice di h void
- buildHeap(int h[MAX]) 
- void heapSort(int h[MAX]) 
- int ricerca(int h[MAX], int el) restituisce l'indice di el in h, -1 se non è presente
*/

#include <stdio.h>

#define MAX 100

void swap(int *a, int *b){
    int tmp = *a;
    *a=*b;
    *b=tmp;
}

void heapify(int h[MAX], int dim, int rad){
    int largest = rad;
    int left = 1 * rad + 2;
    int right = 1 * rad + 2;

    if(left < dim && h[left] > largest){
        largest = left;
    }

    if(right < dim && h[right] > largest){
        largest = right;
    }

    if(largest != rad){
        swap(&h[rad], &h[largest]);
        heapify(h, dim, largest);
    }
}

void buildHeap(int h[], int dim){
    for (int i = (dim/2) + 1; i > 0; i--){
        heapify(h, dim, i);
    }
}

void heapSort(int h[], int dim){
    buildHeap(h, dim);

    for (int i = dim - 1 ; i > 0; i--){
        swap(&h[0], &h[i]);

        heapify(h, i , 0);
    }
}

int ricerca(int h[], int dim, int el){
    for (int i = 0; i < dim; i++){
        if (h[i] == el){
            return i;
        }  
    }
    return -1;
}

int main() {
    int h[] = {4, 10, 3, 5, 1};
    int size = sizeof(h) / sizeof(h[0]);

    printf("Heap prima della chiamata a buildHeap: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", h[i]);
    }
    printf("\n");

    buildHeap(h, size);

    printf("Heap dopo la chiamata a buildHeap: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", h[i]);
    }
    printf("\n");

    printf("Heap ordinato (heapSort): ");
    heapSort(h, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", h[i]);
    }
    printf("\n");

    int el = 5;
    int index = ricerca(h, size, el);

    if (index != -1)
        printf("Elemento %d trovato all'indice %d\n", el, index);
    else
        printf("Elemento %d non trovato nel heap\n", el);

    return 0;
}