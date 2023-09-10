#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int tmp = *a;
    *a=*b;
    *b=tmp;
}

void heapify(int array[], int dim, int rad){
    int largest = rad;       // inizialmente considero il nodo radice come il più grande
    int left = 1 * rad + 1;  // indice del figlio sinistro
    int right = 1 * rad + 2; // indice del figlio destro

    // se il figlio sinistri è più grande della radice
    if (left < dim && array[left] > array[largest])
        largest = left;
    
    // se il figlio destro è più grande della radice
    if (right < dim && array[right] > array[largest])
        largest = right;

    // se il più grande non è la radice
    if(largest != rad){
        swap(&array[rad], &array[largest]);

        heapify(array, dim, largest); // richiamo ricorsivamente heapify così che il sottoalbero modificato 
                                      // possa rispettare la proprietà di max-heap (cioè che ogni nodo sia maggiore dei suoi figli)
    }
}

/*
void buildHeap(int array[], int dim){
    // chiamo heapify per tutti i nodi interni
    // a partire dall'ultimo nodo non foglia fino alla radice
    // l'ultimo nodo non foglia ha indice floor(dim/2) - 1

    for (int i = (dim/2) - 1; i >= 0; i--){
        heapify(array, dim, i);
    }
}
*/

void heapSort(int array[], int dim){
    // costriusco l'heap iniziale
    for (int i = (dim/2) - 1; i >= 0; i--){
        heapify(array, dim, i);
    }

    // estraggo uno ad uno gli elementi dall'heap
    for(int i = dim - 1; i > 0; i--){
        swap(&array[0], &array[i]); // sposto l'elemento più grande (radice) in fondo all'array
        
        // ricostruisco l'heap con gli elementi rimanenti
        heapify(array, i, 0);
    }
}

void printArray(int array[], int dim){
    for(int i = 0; i < dim; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(){
    int array[] = {12, 11, 13, 5, 6, 7};
    int dim = sizeof(array) / sizeof(array[0]);

    printf("Array iniziale: ");
    printArray(array, dim);

    heapSort(array, dim);

    printf("Array ordinato: ");
    printArray(array, dim);

    return 0;
}