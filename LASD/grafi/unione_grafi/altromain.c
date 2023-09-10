/*
dati in input due grafi orientati e pesati di n vertici costruire in c una
funzione che prende in input i due grafi e ne costruisce un terzo che contiene
l'unione dei due grafi, ovvero, un arco i j è inserito nel nuovo grafo se e solo
se i j è presente in almeno uno dei due grafi di partenza e il peso è la somma
dei relativi pesi dei due grafi.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// struttura di un arco
typedef struct edge {
    int key;            // chiave dell'arco
    int weight;         // peso dell'arco
    struct edge *next;  // puntatore al prossimo arco
} edge;

// struttura di un grafo orientato e pesato
typedef struct graph {
    int n_node;   // numero di vertici
    edge *edges;  // array di archi
} graph;

// funzione che stampa un grafo
void printGraph(graph *g) {
    int i;
    edge *e;  // puntatore ad un arco

    printf("n: %d\n", g->n_node);

    // scorro tutti i vertici del grafo e stampo tutti gli archi che partono da
    // quel vertice
    for (i = 0; i < g->n_node; i++) {
        e = g->edges[i].next;
        while (e != NULL) {
            printf("i: %d\tj: %d\tpeso: %d\n", i, e->key, e->weight);
            e = e->next;
        }
    }
}

// funzione che crea un grafo orientato e pesato con n vertici e m archi
graph *createGraph(int n) {
    int i, j, k, m;
    graph *g = malloc(sizeof(graph));  // alloco lo spazio per il grafo
    g->n_node = n;
    g->edges = malloc(n * sizeof(edge));

    // creo un grafo completo con pesi random
    for (i = 0; i < n; i++) {
        g->edges[i].key = i;
        g->edges[i].weight = rand() % 10;
        g->edges[i].next = NULL;
    }

    // creo un grafo completo con pesi random
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            k = rand() % 2;
            if (k == 1 && i != j) {
                edge *e = malloc(sizeof(edge));
                e->key = j;
                e->weight = rand() % 10;
                e->next = g->edges[i].next;
                g->edges[i].next = e;
            }
        }
    }
    return g;
}

// funzione che fa l'unione dei due grafi e se i e j sono uguali somma i pesi

graph *unionGraph(graph *g1, graph *g2) {
    int i;
    edge *e1, *e2;  // puntatori ad un arco

    // alloco lo spazio per il grafo
    graph *g3 = malloc(sizeof(graph));
    g3->n_node = g1->n_node;
    g3->edges = malloc(g3->n_node * sizeof(edge));

    for (i = 0; i < g3->n_node; i++) {
        g3->edges[i].key = i;
        g3->edges[i].weight = 0;
        g3->edges[i].next = NULL;
    }

    // scorro tutti i vertici del grafo e stampo tutti gli archi che partono da
    // quel vertice
    for (i = 0; i < g3->n_node; i++) {
        e1 = g1->edges[i].next;  // puntatore al primo arco del grafo g1
        e2 = g2->edges[i].next;  // puntatore al primo arco del grafo g2

        // scorro tutti gli archi del grafo g1 e li inserisco nel grafo g3
        while (e1 != NULL) {
            edge *e = malloc(sizeof(edge));
            e->key = e1->key;
            e->weight = e1->weight;
            e->next = g3->edges[i].next;  // inserisco l'arco in testa
            g3->edges[i].next = e;
            e1 = e1->next;  // passo all'arco successivo
        }
        // scorro tutti gli archi del grafo g2 e li inserisco nel grafo g3 se sono uguali sommo i pesi
        while (e2 != NULL) {
            edge *e = malloc(sizeof(edge));
            e->key = e2->key;
            e->weight = e2->weight;
            e->next = g3->edges[i].next;
            g3->edges[i].next = e;
            e2 = e2->next;
        }
        
    }

    return g3;
}

// funzione principale
int main() {
    srand(time(NULL));

    graph *g1 = createGraph(2);
    graph *g2 = createGraph(2);
    graph *g3 = unionGraph(g1, g2);

    printGraph(g1);
    printf("\n");
    printGraph(g2);
    printf("\n");
    printGraph(g3);

    return 0;
}
