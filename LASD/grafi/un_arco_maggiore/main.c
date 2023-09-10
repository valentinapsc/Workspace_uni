/*
preso in input il grafo G, trasformi G in modo che 
- ogni nodo abbia al più un solo arco uscente rappresentato da quello con peso
  maggiore
- restituisca in output un grafo H rappresentato con matrice di adiacenza.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
    int key;           // vertice di destinazione
    int weight;        // peso dell'arco
    struct edge *next; // puntatore al prossimo arco
} edge;

typedef struct graph{
    int nv;
    edge **adj;
}graph;

int is_empty(graph *g) {
    return (g == NULL || g->nv <= 0);
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

void add_edge_w(graph *g, int from, int to, int weight) {
    if (is_empty(g)) return;

    if (reach(g, from, to)) return; 

    edge *new = (edge *)malloc(sizeof(edge)); 
    if (new == NULL) return; 

    new->key = to;            // imposto il vertice di destinazione
    new->weight = weight;     // imposto il peso dell'arco
    new->next = g->adj[from]; // imposto il nuovo arco come primo arco della lista di adiacenza del vertice "from"
    g->adj[from] = new; 
}

graph* transformGraph(graph *G) {
    graph *H = empty_graph(G->nv);

    for (int i = 0; i < G->nv; i++) {
        int maxWeight = -1;
        int maxDest = -1;

        edge *current = G->adj[i];
        while (current != NULL) {
            if (current->weight > maxWeight) {
                maxWeight = current->weight;
                maxDest = current->key;
            }
            current = current->next;
        }

        if (maxDest != -1) {
            add_edge_w(H, i, maxDest, maxWeight);
        }
    }

    return H;
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

// funzione per riempire il grafo
void fill_graph(graph *g) {
    int scelta, 
        from, 
        to,
        weight;

    printf("RIEMPIMENTO GRAFO\n");

    do {
        printf("[0] per uscire\n"); 
        printf("[1] per inserire\n"); // inserisce un arco
        printf("Scelta: ");
        scanf("%d", &scelta);

        if (scelta == 1) {
            printf("\nInserisci arco\n");
            printf("da: ");
            scanf("%d", &from);

            printf("a: ");
            scanf("%d", &to);

            printf("Peso: ");
            scanf("%d", &weight);

            add_edge_w(g, from, to, weight);

            printf("\n\n");
        }
    } while (scelta != 0);
}

int main(){
    int nv;
    printf("Inserisci il numero di vertici del grafo: ");
    scanf("%d", &nv);

    graph* g = empty_graph(nv);
    fill_graph(g);

    printf("Grafo originale:\n");
    print_graph(g);

    graph *H = transformGraph(g);

    printf("\nGrafo trasformato:\n");
    print_graph(H);

    return 0;
}