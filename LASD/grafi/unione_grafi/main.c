/*
Siano G1 e G2 due grafi orientati e pesati (con pesi interi positivi) di
0,1,…,n-1 vertici, implementati entrambi con liste di adiacenza. Scrivere una
funzione in C che presi in input (da tastiera) G1, G2 e una lista L doppiamente
puntata e non circolare di valori interi positivi, faccia l’unione dei due grafi
in un grafo G3 e modifichi L nel modo seguente: Un arco (i, j) con peso p sarà
aggiunto al grafo G3 se: l’arco (i,j) è presente in almeno uno tra G1 e G2 con
pesi rispettivamente p1 e p2 e p=p1+p2.

se p è presente in L, allora sarà rimosso da L

Scrivere una funzione che permetta di creare da tastiere G1, G2 e L e di
stamparli prima e dopo l’applicazione della funzione.

Bonus:+2 punti la funzione ha complessità quadratica nel numero dei vertici di
G1 e G2
*/

#include <stdio.h>
#include <stdlib.h>

// Struttura per rappresentare un arco
typedef struct {
    int u;       // Vertice di partenza
    int v;       // Vertice di arrivo
    int weight;  // Peso dell'arco
} Edge;

// Struttura per rappresentare un grafo
typedef struct {
    int numVertices;  // Numero di vertici nel grafo
    Edge* edges;      // Array degli archi del grafo
    int numEdges;     // Numero di archi nel grafo
} Graph;

// Funzione per creare un nuovo grafo
Graph createGraph(int numVertices) {
    Graph graph;
    graph.numVertices = numVertices;
    graph.edges = NULL;
    graph.numEdges = 0;
    return graph;
}

// Funzione per aggiungere un arco al grafo
void addEdge(Graph* graph, int u, int v, int weight) {
    // Incrementa il numero di archi
    graph->numEdges++;

    // Rialloca l'array degli archi
    graph->edges = (Edge*)realloc(graph->edges, graph->numEdges * sizeof(Edge));

    // Aggiunge il nuovo arco
    Edge edge;
    edge.u = u;
    edge.v = v;
    edge.weight = weight;
    graph->edges[graph->numEdges - 1] = edge;
}

// Funzione per stampare un grafo
void printGraph(Graph graph) {
    printf("Numero di vertici: %d\n", graph.numVertices);
    printf("Numero di archi: %d\n", graph.numEdges);
    printf("Elenco degli archi:\n");

    for (int i = 0; i < graph.numEdges; i++) {
        Edge edge = graph.edges[i];
        printf("(%d, %d) - Peso: %d\n", edge.u, edge.v, edge.weight);
    }
}

// Funzione per controllare se un dato peso è presente nella lista L
int isInList(int* list, int size, int weight) {
    for (int i = 0; i < size; i++) {
        if (list[i] == weight) {
            return 1;  // Il peso è presente nella lista
        }
    }
    return 0;  // Il peso non è presente nella lista
}

// Funzione per rimuovere un dato peso dalla lista L
void removeFromList(int* list, int* size, int weight) {
    int i, j;
    for (i = 0; i < *size; i++) {
        if (list[i] == weight) {
            // Sposta tutti gli elementi successivi indietro di una posizione
            for (j = i; j < *size - 1; j++) {
                list[j] = list[j + 1];
            }
            // Decrementa la dimensione della lista
            (*size)--;
            break;
        }
    }
}

// Funzione per unire due grafi G1 e G2 e modificare la lista L
Graph mergeGraphs(Graph G1, Graph G2, int* L, int size) {
    Graph G3 = createGraph(G1.numVertices + G2.numVertices);

    // Aggiunge gli archi di G1 a G3
    for (int i = 0; i < G1.numEdges; i++) {
        Edge edge = G1.edges[i];
        addEdge(&G3, edge.u, edge.v, edge.weight);
    }

    // Aggiunge gli archi di G2 a G3, controllando la condizione richiesta
    for (int i = 0; i < G2.numEdges; i++) {
        Edge edge = G2.edges[i];
        int p = edge.weight;

        // Controlla se il peso p è presente nella lista L
        if (isInList(L, size, p)) {
            // Rimuove il peso p dalla lista L
            removeFromList(L, &size, p);
        } else {
            // Cerca l'arco corrispondente in G1
            for (int j = 0; j < G1.numEdges; j++) {
                Edge g1Edge = G1.edges[j];
                if (g1Edge.u == edge.u && g1Edge.v == edge.v) {
                    int p1 = g1Edge.weight;
                    int p2 = edge.weight;

                    // Aggiunge l'arco a G3 solo se p = p1 + p2
                    if (p == p1 + p2) {
                        addEdge(&G3, edge.u, edge.v, p);
                    }
                    break;
                }
            }
        }
    }

    return G3;
}

int main() {
    int numVertices1, numVertices2;
    int numEdges1, numEdges2;

    printf("Inserisci il numero di vertici di G1: ");
    scanf("%d", &numVertices1);
    printf("Inserisci il numero di archi di G1: ");
    scanf("%d", &numEdges1);

    Graph G1 = createGraph(numVertices1);

    printf(
        "Inserisci gli archi di G1 nel formato (vertice di partenza, vertice "
        "di arrivo, peso):\n");
    for (int i = 0; i < numEdges1; i++) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        addEdge(&G1, u, v, weight);
    }

    printf("Inserisci il numero di vertici di G2: ");
    scanf("%d", &numVertices2);
    printf("Inserisci il numero di archi di G2: ");
    scanf("%d", &numEdges2);

    Graph G2 = createGraph(numVertices2);

    printf(
        "Inserisci gli archi di G2 nel formato (vertice di partenza, vertice "
        "di arrivo, peso):\n");
    for (int i = 0; i < numEdges2; i++) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        addEdge(&G2, u, v, weight);
    }

    int size;
    printf("Inserisci la dimensione della lista L: ");
    scanf("%d", &size);

    int* L = (int*)malloc(size * sizeof(int));
    printf("Inserisci gli elementi della lista L:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &L[i]);
    }

    printf("\nGrafo G1:\n");
    printGraph(G1);

    printf("\nGrafo G2:\n");
    printGraph(G2);

    Graph G3 = mergeGraphs(G1, G2, L, size);

    printf("\nGrafo G3:\n");
    printGraph(G3);

    free(G1.edges);
    free(G2.edges);
    free(G3.edges);
    free(L);

    return 0;
}