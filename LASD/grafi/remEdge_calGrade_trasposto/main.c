/*
Dato un grafo pesato, implementare queste funzioni:
3a. Rimuovere l'arco col peso minimo
3b. Dato un vertice, calcolarne il grado adiacente ed incidente
3c. Generare un nuovo grafo G2 che è il trasposto del grafo originale
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
    int key;            // vertice di destinazione
    int weight;         // peso dell'arco
    struct edge *next;  // puntatore al prossimo arco
} edge;

typedef struct graph {
    int nv;             // numero di vertici del grafo
    struct edge **adj;  // vettore con le liste delle adiacenze
} graph;

int is_empty(graph *g) { return (g == NULL || g->nv <= 0); }

graph *empty_graph(int nv) {
    graph *g = (graph *)malloc(sizeof(graph));

    if (g != NULL) {
        g->nv = nv;
        g->adj = (edge **)calloc(nv, sizeof(edge *));

        if (g->adj == NULL) {
            free(g);
            g = NULL;
        }
    }
    return g;
}

int reach(graph *g, int from, int to) {
    int reached = 0;

    if (is_empty(g)) return reached;

    if (from < 0 || from >= g->nv) return reached;
    if (to < 0 || to >= g->nv) return reached;

    edge *head = g->adj[from];
    while (head != NULL && head->key != to) {
        head = head->next;
    }

    return head != NULL;
}

void add_edge(graph *g, int from, int to, int weight) {
    if (is_empty(g)) return;

    if (reach(g, from, to)) return;

    edge *newEdge = (edge *)malloc(sizeof(edge));
    if (newEdge == NULL) return;

    newEdge->key = to;
    newEdge->weight = weight;
    newEdge->next = g->adj[from];
    g->adj[from] = newEdge;
}

void remove_min_weight(graph* g) {
    if (is_empty(g)) return;

    int minWeight = INT_MAX;
    int minIndex = -1;

    // Trova l'arco con peso minimo
    for (int i = 0; i < g->nv; i++) {
        edge* head = g->adj[i];
        while (head != NULL) {
            if (head->weight < minWeight) {
                minWeight = head->weight;
                minIndex = i;
            }
            head = head->next;
        }
    }

    if (minIndex != -1) {
        edge* prev = NULL;
        edge* current = g->adj[minIndex];

        // Rimuovi l'arco con peso minimo
        while (current != NULL && current->weight != minWeight) {
            prev = current;
            current = current->next;
        }

        if (prev == NULL) {
            g->adj[minIndex] = current->next;
        } else {
            prev->next = current->next;
        }

        free(current);
        printf("Arco rimosso con peso minimo: %d\n", minWeight);
    }
}

int calculate_in_degree(graph* g, int vertex) {
    int inDegree = 0;

    for (int i = 0; i < g->nv; i++) {
        edge* head = g->adj[i];
        while (head != NULL) {
            if (head->key == vertex) {
                inDegree++;
            }
            head = head->next;
        }
    }

    return inDegree;
}

int calculate_out_degree(graph* g, int vertex) {
    int outDegree = 0;

    edge* head = g->adj[vertex];
    while (head != NULL) {
        outDegree++;
        head = head->next;
    }

    return outDegree;
}

graph* transpose_graph(graph* g) {
    if (is_empty(g)) return NULL;

    graph* transpose = empty_graph(g->nv);

    for (int i = 0; i < g->nv; i++) {
        edge* head = g->adj[i];
        while (head != NULL) {
            add_edge(transpose, head->key, i, head->weight);
            head = head->next;
        }
    }

    return transpose;
}

void print_graph(graph *g) {
    int i = 0;

    if (is_empty(g)) {
        printf("Errore nella stampa del grafo: il grafo è vuoto\n");
        return;
    }

    for (i = 0; i < g->nv; i++) {
        edge *head = g->adj[i];

        printf("[%d]: ", i);
        while (head != NULL) {
            printf("%d -> ", head->key);
            head = head->next;
        }
        printf("-|\n");
    }

    printf("\n\n");
}

void fill_graph(graph* g) {
    int scelta, // scelta dell'utente
        from,   // vertice di partenza dell'arco
        to,     // vertice di arrivo dell'arco
        weight; // peso dell'arco

    printf("RIEMPIMENTO GRAFO\n");

    do {
        printf("[0] per uscire\n");
        printf("[1] per inserire un arco\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        if (scelta == 1) {
            printf("\nInserisci l'arco\n");
            printf("Da: ");
            scanf("%d", &from);

            printf("A: ");
            scanf("%d", &to);

            printf("Peso: ");
            scanf("%d", &weight);

            add_edge(g, from, to, weight);

            printf("\n\n");
        }
    } while (scelta != 0);
}

int main() {
    int nv;
    printf("Inserisci il numero di vertici del grafo: ");
    scanf("%d", &nv);

    graph* g = empty_graph(nv);
    fill_graph(g);

    printf("Grafo originale:\n");
    print_graph(g);

    remove_min_weight(g);
    printf("Grafo dopo la rimozione dell'arco con peso minimo:\n");
    print_graph(g);

    int vertex;
    printf("Inserisci il vertice di cui calcolare il grado adiacente ed incidente: ");
    scanf("%d", &vertex);
    int inDegree = calculate_in_degree(g, vertex);
    int outDegree = calculate_out_degree(g, vertex);
    printf("Grado adiacente: %d\n", outDegree);
    printf("Grado incidente: %d\n", inDegree);

    graph* transpose = transpose_graph(g);
    printf("Grafo trasposto:\n");
    print_graph(transpose);

    return 0;
}