#include <stdio.h>
#include <stdlib.h>

/*
un grafo è un insieme di vertici e archi
- può essere orientato (se gli archi hanno una direzione) o non orientato (se gli archi non hanno una direzione)
- può essere pesato (se gli archi hanno un peso) o non pesato (se gli archi non hanno un peso)
- può essere rappresentato con una matrice di adiacenza o con una lista di adiacenza
- può essere ciclico (se è possibile tornare al vertice di partenza) o aciclico (se non è possibile)
- può essere connesso (se è possibile raggiungere tutti i vertici) o non connesso (se non è possibile)

la lista di adiacenza è un vettore di liste, in cui ogni lista rappresenta i vertici adiacenti al vertice corrispondente
*/

typedef struct edge {
    int key;           // vertice di destinazione
    int weight;        // peso dell'arco
    struct edge *next; // puntatore al prossimo arco
} edge;

typedef struct graph {
    int nv;            // numero di vertici del grafo
    struct edge **adj; // vettore con le liste delle adiacenze
} graph;

int is_empty(graph *g) {
    return (g == NULL || g->nv <= 0);
}

// funzione che restituisce 1 se il vertice "to" è raggiungibile dal vertice "from", 0 altrimenti
int reach(graph *g, int from, int to) {
    int reached = 0; // 0 = false, 1 = true, reached indica se è stato raggiunto il vertice "to"

    if (is_empty(g)) return reached; // se il grafo è vuoto ritorna 0

    if (from < 0 || from >= g->nv) return reached; // se il vertice di partenza non è valido ritorna 0
    if (to < 0 || to >= g->nv) return reached;     // se il vertice di arrivo non è valido ritorna 0

    edge *head = g->adj[from];                // head punta alla lista di adiacenza del vertice "from"
    while (head != NULL && head->key != to) { // scorre la lista di adiacenza finché non trova il vertice "to"
        head = head->next;
    }

    return head != NULL; // se head è NULL allora il vertice "to" non è stato raggiunto, altrimenti sì
}

// crea un grafo vuoto con nv vertici (da 0 a nv-1)
graph *empty_graph(int nv) {
    graph *g = (graph *)malloc(sizeof(graph));

    if (g != NULL) { 
        g->nv = nv;
        g->adj = (edge **)calloc(nv, sizeof(edge *)); // alloca il vettore di liste di adiacenza, uso calloc per inizializzare a NULL ed evitare un for

        if (g->adj == NULL) { // se la calloc fallisce
            free(g);
            g = NULL;
        }
    }

    return g;
}

// aggiunge un arco da "from" a "to" 
void add_edge(graph *g, int from, int to) {
    if (is_empty(g)) return;

    if (reach(g, from, to)) return; // se il vertice "to" è raggiungibile dal vertice "from" non aggiungo l'arco

    edge *new = (edge *)malloc(sizeof(edge)); // alloco il nuovo arco
    if (new == NULL) return; 

    new->key = to;            // imposto il vertice di destinazione
    new->next = g->adj[from]; // imposto il nuovo arco come primo arco della lista di adiacenza del vertice "from"
    g->adj[from] = new; 
}

// aggiunge un arco da "from" a "to" con peso weight 
void add_edge_w(graph *g, int from, int to, int weight) {
    if (is_empty(g)) return;

    if (reach(g, from, to)) return; // se il vertice "to" è raggiungibile dal vertice "from" non aggiungo l'arco

    edge *new = (edge *)malloc(sizeof(edge)); // alloco il nuovo arco
    if (new == NULL) return; 

    new->key = to;            // imposto il vertice di destinazione
    new->weight = weight;     // imposto il peso dell'arco
    new->next = g->adj[from]; // imposto il nuovo arco come primo arco della lista di adiacenza del vertice "from"
    g->adj[from] = new; 
}

// elimina l'arco da "from" a "to"  
void delete_edge(graph *g, int from, int to) {
    if (is_empty(g)) return;

    if (!reach(g, from, to)) return; // se il vertice "to" non è raggiungibile dal vertice "from" non elimino l'arco

    edge *curr = g->adj[from]; // curr punta alla lista di adiacenza del vertice "from"
    edge *prev = curr;         // prev punta al precedente di curr

    while (curr != NULL && curr->key != to) { // scorro la lista di adiacenza finché non trovo il vertice "to"
        prev = curr;
        curr = curr->next;
    }

    // sto eliminando la testa 
    if (prev == curr) {
        g->adj[from] = curr->next; // imposto la testa al prossimo arco
        free(curr);               // libero il nodo corrente
    } else {
        prev->next = curr->next; // imposto il prossimo del precedente al prossimo del corrente
        free(curr);
    }
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
    int scelta, // scelta dell'utente
        from,   // vertice di partenza dell'arco
        to;     // vertice di arrivo dell'arco

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

            add_edge(g, from, to);

            printf("\n\n");
        }
    } while (scelta != 0);
}

// funzione per unire due grafi, cioè crea un nuovo grafo che contiene tutti gli archi dei due grafi 
// con i pesi sommati se un arco è presente in entrambi i grafi
graph *graph_union(graph *g1, graph *g2) {
    graph *g3 = NULL; // grafo di ritorno
    int *weight;     // vettore per memorizzare i pesi degli archi
    int *flag;      // vettore per memorizzare se un vertice è stato raggiunto

    if (!is_empty(g1) && !is_empty(g2)) {
        g3 = empty_graph(g1->nv); // creo il grafo di ritorno

        if (g3 != NULL) {
            // alloco i vettori
            weight = (int *)calloc(g1->nv, sizeof(int)); 
            flag = (int *)calloc(g1->nv, sizeof(int));

            for (int i = 0; i < g1->nv; i++) { // scorro i vertici
                edge *head;

                head = g1->adj[i]; // head punta alla lista di adicenza del vertice i del grafo g1
                // scorro la lista di adiacenza del vertice i del grafo g1
                while (head != NULL) {
                    weight[head->key] += head->weight; // sommo i pesi degli archi
                    flag[head->key] = 1;               // imposto il flag a 1 per indicare che il vertice è stato raggiunto
                    head = head->next;                 // scorro la lista di adiacenza
                }

                head = g2->adj[i]; // head punta alla lista di adiacenza del vertice i del grafo g2
                // scorro la lista di adiacenza del vertice i del grafo g2
                while (head != NULL) {
                    weight[head->key] += head->weight;
                    flag[head->key] = 1;
                    head = head->next;
                }

                for (int j = 0; j < g1->nv; j++) {
                    if (flag[j]) add_edge_w(g3, i, j, weight[j]); // aggiungo l'arco solo se il vertice è stato raggiunto

                    flag[j] = 0;   // resetto il flag
                    weight[j] = 0; // resetto il peso
                }
            }
        }
    }

    return g3;
}

////////////////////////////////////////////////////////////////////////////

/*
un albero binario di ricerca è un albero binario in cui ogni nodo ha un valore maggiore rispetto ai nodi del sottoalbero sinistro e minore dei nodi del sottoalbero destro
le sue proprietà sono:
- ogni nodo ha al massimo due figli (i nodi in totale sono 2^(h+1)-1,dove h è l'altezza dell'albero e i nodi foglia sono 2^h, h+1 è il numero di livelli e il -1 è per il nodo radice)
- ogni sottoalbero è un albero binario di ricerca
- non ci sono nodi duplicati
- l'altezza dell'albero è logaritmica rispetto al numero di nodi (log2(n+1)) 
- l'albero è bilanciato (cioè la differenza tra l'altezza del sottoalbero sinistro e l'altezza del sottoalbero destro è al massimo 1)
- non sono presenti cicli
- ogni nodo ha un solo padre (tranne la radice che non ha padre)
- ogni nodo ha un solo cammino per raggiungere un altro nodo
*/

typedef struct btree {
    int key;             // etichetta del nodo
    struct btree *left;  // puntatore al sottoalbero sinistro
    struct btree *right; // puntatore al sottoalbero destro
} btree;

// funzione che trova il massimo valore del sottoalbero destro scorrendolo fino ad arrivare all'ultimo nodo
btree *max(btree *tree) {
    if (tree == NULL) return NULL;
    if (tree->right == NULL) return tree;

    return max(tree->right);
}

// funzione che trova il minimo valore del sottoalbero sinistro
btree *min(btree *tree) {
    if (tree == NULL) return NULL;
    if (tree->left == NULL) return tree;

    return min(tree->left);
}

// funzione che inserisce un nodo nell'albero in questo modo: 
// se il valore del nodo da inserire è maggiore della radice allora lo inserisco nel sottoalbero destro, 
// altrimenti lo inserisco nel sottoalbero sinistro
btree* search(btree* root, int to_search) {
    if (root == NULL)
        return NULL;
    else {
        if (to_search > root->key)
            return search(root->right, to_search);
        else if (to_search < root->key)
            return search(root->left, to_search);

        return root;
    }
}

// funzione che restituisce 1 se l'albero è un ABR, 0 altrimenti
int is_binary_search_tree(btree *tree) {
    if (tree == NULL) return 1;

    btree *max_left_node = max(tree->left);                                // trovo il massimo valore del sottoalbero sinistro
    if (max_left_node != NULL && max_left_node->key > tree->key) return 0; // se il massimo valore è maggiore della radice allora non è un ABR

    btree *min_right_node = min(tree->right);                                // trovo il minimo valore del sottoalbero destro
    if (min_right_node != NULL && min_right_node->key < tree->key) return 0; // se il minimo valore è minore della radice allora non è un ABR

    if (!(is_binary_search_tree(tree->left))) return 0;

    if (!(is_binary_search_tree(tree->right))) return 0;

    return 1;
}

// funzione che costruisce un nuovo nodo con chiave k
btree *build_node(int k) {
    btree *new_node = (btree *)malloc(sizeof(btree));
    new_node->key = k;

    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

btree* insert(btree* root, int key) {
    if (root == NULL) {
        root = build_node(key);
    } else if (key < root->key) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }
    return root;
}

// stampa che scorre l'albero in ordine, cioè prima il sottoalbero sinistro, poi la radice e infine il sottoalbero destro
void print_in_order(btree *tree) {
    if (tree == NULL) return;

    print_in_order(tree->left);
    printf("%d ", tree->key);
    print_in_order(tree->right);
}

// stampa che scorre l'albero in postordine, cioè prima il sottoalbero sinistro, poi il sottoalbero destro e infine la radice
void printPostOrder(btree *root) {
    if (root == NULL) {
        return;
    }

    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d ", root->key);
}

// stampa che scorre l'albero in preordine, cioè prima la radice, poi il sottoalbero sinistro e infine il sottoalbero destro
void printPreOrder(btree *root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->key);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void deleteFromAbr(btree **root, int value){
	btree *node = *root; 
	
	if(node){ // se l'albero non è vuoto
		if(node->key < value){                  // se il valore da eliminare è maggiore della radice
			deleteFromAbr(&node->right, value); // elimino il valore nel sottoalbero destro

		} else if(node->key > value){           // se il valore da eliminare è minore della radice
			deleteFromAbr(&node->left, value);  // elimino il valore nel sottoalbero sinistro

		} else { // se il valore da eliminare è uguale alla radice
			if(!node->left && !node->right){ // se il nodo è una foglia
				free(*root); 
				*root = NULL; 

			} else { // se il nodo non è una foglia
				if(!node->left){ // se il nodo ha solo il sottoalbero destro
					*root = node->right; // imposto la radice al sottoalbero destro
					free(node);  

				} else if(!node->right){
					*root = node->left; 
					free(node); 

				} else { // se il nodo ha entrambi i sottoalberi
					btree *minNode = min(node->right); // trovo il minimo valore del sottoalbero destro
					node->key = minNode->key;          // imposto il valore del nodo corrente al minimo valore del sottoalbero destro
					if(minNode->right){                // se il minimo valore ha un sottoalbero destro
						node->right = minNode->right;  // imposto il sottoalbero destro del nodo corrente al sottoalbero destro del minimo valore
					}
				    deleteFromAbr(&(node->right), minNode->key); // elimino il minimo valore del sottoalbero destro perchè è stato spostato al posto del nodo corrente
				}
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////////

/*
le liste doppiamente puntate sono liste in cui ogni nodo ha un puntatore al nodo precedente e al nodo successivo
funzionano come le liste semplicemente puntate, ma hanno un puntatore in più
utili per scorrere la lista in entrambi i sensi
*/

typedef struct List {
    int key;            // etichetta del nodo

    struct List *next;  // puntatore al prossimo nodo
    struct List *prev;  // puntatore al nodo precedente
} List;

// funzione che costruisce un nuovo nodo con chiave key
List *build_node(int key) {
    List *new_node = (List *)malloc(sizeof(List));

    if (new_node != NULL) {
        new_node->next = NULL;
        new_node->prev = NULL;
        new_node->key = key;
    }

    return new_node;
}

// funzione che inserisce un nodo in testa alla lista
void insert_node(List **list, List *new_node) {
    if (new_node == NULL) return;
    new_node->next = *list;

    if (*list != NULL) {
        new_node->prev = (*list)->prev; // imposto il precedente del nuovo nodo al precedente del primo nodo

        if ((*list)->prev != NULL) 
            (*list)->prev->next = new_node; // imposto il prossimo del precedente del primo nodo al nuovo nodo

        (*list)->prev = new_node; // imposto il precedente del primo nodo al nuovo nodo
    }

    *list = new_node; // imposto il primo nodo al nuovo nodo
} 

// funzione che inserisce un nodo in ordine nella lista
void insert_sorted_node(List **list, List *new_node) {
    if (new_node == NULL) return;

    List *curr = *list; // curr punta al primo nodo
    List *prev = *list; // prev punta al primo nodo

    while (curr != NULL && new_node->key >= curr->key) {
        prev = curr;
        curr = curr->next;
    }

    // inserisco in testa
    if (prev == curr) {
        new_node->prev = NULL; // il precedente del nuovo nodo è NULL
        new_node->next = curr; // il prossimo del nuovo nodo è il primo nodo

        if (curr != NULL) curr->prev = new_node; // il precedente del primo nodo è il nuovo nodo

        *list = new_node;
    } else { // inserisco in mezzo
        new_node->next = curr; // il prossimo del nuovo nodo è il nodo corrente
        new_node->prev = prev; // il precedente del nuovo nodo è il precedente del nodo corrente

        if (prev != NULL) {
            prev->next = new_node; // il prossimo del precedente del nodo corrente è il nuovo nodo
        }

        if (curr != NULL) {
            curr->prev = new_node; // il precedente del nodo corrente è il nuovo nodo
        }
    }
}

List* mergeLists(List* L1, List* L2) {
    if (L1 == NULL)
        return L2;
    if (L2 == NULL)
        return L1;

    // se l'elemento della prima lista è minore o uguale all'elemento della seconda lista
    if (L1->key <= L2->key) {
        L1->next = mergeLists(L1->next, L2); // richiamo ricorsivamente la funzione passando come primo parametro la coda della prima lista e come secondo parametro la seconda lista
        L1->next->prev = L1; // il puntatore al nodo precedente del nodo successivo del nodo corrente della prima lista punta al nodo corrente
        L1->prev = NULL; // il puntatore al nodo precedente del nodo corrente della prima lista punta a NULL
        return L1;
    } else {
    // se l'elemento della seconda lista è minore dell'elemento della prima lista 
        L2->next = mergeLists(L1, L2->next);
        L2->next->prev = L2;
        L2->prev = NULL;
        return L2;
    }
}

//elimina un dato nodo con key k dalla lista

// funzione che elimina un nodo dalla lista
List *delete_node(List **list) {
    List *deleted_node = *list; 

    if (deleted_node != NULL) {
        *list = (*list)->next; // imposto il primo nodo al prossimo del primo nodo
        if (*list != NULL) 
            (*list)->prev = deleted_node->prev; // imposto il precedente del primo nodo al precedente del primo nodo

        deleted_node->next = NULL;
        deleted_node->prev = NULL;
    }

    return deleted_node;
}

void print_list(List *list) { // rifalla tenendo gli elementi dentro come tua mamma tiene sempre dentro qw
    if (list == NULL) {
        printf("->|\n\n");
        return;
    }

    List *curr = delete_node(&list);
    printf("%d -> ", curr->key);
    print_list(list);
    insert_node(&list, curr);
}

// funzione che riempie la lista
void fill_list(List **list) {
    int scelta; // scelta dell'utente
    int valore; // valore da inserire

    do {
        printf("RIEMPI LISTA\n");
        printf("[1] per inserire\n");
        printf("[0] per uscire\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        if (scelta == 1) {
            printf("\nInserisci valore: ");
            scanf("%d", &valore);

            insert_node(list, build_node(valore));
        }

        printf("\n\n");

    } while (scelta);
}

// funzione che riempie la lista in ordine
void sort_list(List **list) {
    if (*list == NULL) return;

    List *curr = delete_node(list);

    sort_list(list);

    insert_sorted_node(list, curr);
}

////////////////////////////////////////////////////////////////////////////
// inserisci stack non ordinato e poi ordina

// lo stack verrà allocato con dimensione STACK_MAX_SIZE+1
#define STACK_MAX_SIZE <inserisci_valore>

int empty_stack(int S[]) {
    return S[0] == 0;
}

int full_stack(int S[]) {
    return S[0] == STACK_MAX_SIZE;
}

void push(int S[], int val) {
    if (!full_stack(S)) {
        S[0] = S[0] + 1;
        S[S[0]] = val;
    }
}

int pop(int S[]) {
    int val = 0;

    if (!empty_stack(S)) {
        S[0] = S[0] - 1;
        val = S[S[0] + 1];
    }

    return val;
}

void stampa(int S[]) {
    if (!empty_stack(S)) {
        int valore = pop(S);
        printf("%d ", valore);
        stampa(S);
        push(S, valore);
    } else {
        printf("\n");
    }
}

void new_stack(int S[]) {
    int num_elementi, valore;
    S[0] = 0;

    printf("\nQuanti elementi (max %d elementi): ", STACK_MAX_SIZE);
    scanf("%d", &num_elementi);

    while (num_elementi > STACK_MAX_SIZE) {
        printf("\nmax %d elementi: ", STACK_MAX_SIZE);
        scanf("%d", &num_elementi);
    }

    while (num_elementi) {
        printf("\nInserire un valore: ");
        scanf("%d", &valore);

        push(S, valore);
        --num_elementi;
    }
}

///////////////////////////////////////////////////////////////////////////

// la coda verrà allocata con dimensione QUEUE_MAX_SIZE+2
#define QUEUE_MAX_SIZE <inserisci_valore>

int empty_queue(int Q[]) {
    return Q[0] == 0;
}

int full_queue(int Q[]) {
    return Q[0] == Q[QUEUE_MAX_SIZE + 1];
}

void enqueue(int Q[], int val) {
    if (!full_queue(Q)) {
        Q[Q[QUEUE_MAX_SIZE + 1]] = val;

        if (empty_queue(Q)) Q[0] = 1;

        Q[QUEUE_MAX_SIZE + 1] = (Q[QUEUE_MAX_SIZE + 1] % QUEUE_MAX_SIZE) + 1;
    }
}

int dequeue(int Q[]) {
    int valore = Q[Q[0]];
    Q[0] = (Q[0] % QUEUE_MAX_SIZE) + 1;

    if (full_queue(Q)) {
        Q[0] = 0;
        Q[QUEUE_MAX_SIZE + 1] = 1;
    }

    return valore;
}

void new_queue(int Q[]) {
    int num_elementi, valore;
    Q[0] = 0;
    Q[QUEUE_MAX_SIZE + 1] = 1;

    printf("\nQuanti elementi (max %d elementi): ", QUEUE_MAX_SIZE);
    scanf("%d", &num_elementi);

    while (num_elementi > QUEUE_MAX_SIZE) {
        printf("\nmax %d elementi: ", QUEUE_MAX_SIZE);
        scanf("%d", &num_elementi);
    }

    while (num_elementi) {
        printf("\nInserire un valore: ");
        scanf("%d", &valore);

        enqueue(Q, valore);
        num_elementi--;
    }
}

////////////////////////////////////////////////////////////////////////////

/*
un heap è un albero binario completo (tutti i livelli sono riempiti tranne l'ultimo che può essere incompleto)
in un max-heap ogni nodo è maggiore o uguale ai suoi figli
un heap funziona come un vettore, quindi per accedere al figlio sinistro di un nodo i si usa l'indice 2*i+1 (questa formula sposta il nodo i al livello successivo e lo sposta a sinistra)
per accedere al figlio destro di un nodo i si usa l'indice 2*i+2 (sposta il nodo i al livello successivo e lo sposta a destra)
per accedere al padre di un nodo i si usa l'indice floor((i-1)/2) (sposta il nodo i al livello precedente e lo sposta a sinistra)
*/

void swap(int *a, int *b) {
	int temp = *a; 
	*a = *b;
	*b = temp;  
}
	
void heapify(int heap[], int dim, int rad){
    int largest = rad;       // inizialmente considero il nodo radice come il più grande
    int left = 1 * rad + 1;  // indice del figlio sinistro
    int right = 1 * rad + 2; // indice del figlio destro

    // se il figlio sinistro è più grande della radice
    if (left < dim && heap[left] > heap[largest])
        largest = left;
    
    // se il figlio destro è più grande della radice
    if (right < dim && heap[right] > heap[largest])
        largest = right;

    // se il più grande non è la radice
    if(largest != rad){
        swap(&heap[rad], &heap[largest]); 

        heapify(heap, dim, largest); // richiamo ricorsivamente heapify così che il sottoalbero modificato 
                                    // possa rispettare la proprietà di max-heap (cioè che ogni nodo sia maggiore dei suoi figli)
    }
}

void buildHeap(int heap[], int dim){
    // chiamo heapify per tutti i nodi interni
    // a partire dall'ultimo nodo non foglia fino alla radice
    // l'ultimo nodo non foglia ha indice floor(dim/2) - 1

    for (int i = (dim/2) - 1; i >= 0; i--){
        heapify(heap, dim, i);
    }
}

void heapSort(int heap[], int dim){
    // costriusco l'heap iniziale
    buildHeap(heap, dim);

    // estraggo uno ad uno gli elementi dall'heap
    for(int i = dim - 1; i > 0; i--){
        swap(&heap[0], &heap[i]); // sposto l'elemento più grande (radice) in fondo all'heap
        
        // ricostruisco l'heap con gli elementi rimanenti
        heapify(heap, i, 0);
    }
}

// funzione che genera un heap di dimensione heapSize
int *generateHeap(int heapSize) {
    srand(time(NULL));

	int i; 
    int *heap = (int *)malloc(heapSize * sizeof(int));

    if (heap == NULL) {
        printf("Errore allocazione");
        exit(-1);
    }

    for (i = 0; i < heapSize; i++) {
        heap[i] = rand() % 90 + 10;
    }

    buildHeap(heap, heapSize);

    return heap;
}

void printHeap(int heap[], int heapSize){
	int i; 
	
	printf("[Heap]-> "); 
	for(i = 0; i < heapSize; i++){
		printf("%d ", heap[i]); 
	}
	printf("\n"); 
	
}

// funzione che restituisce 1 se l'array heap[0...heapSize-1] è un max-heap, 0 altrimenti
int isHeap(int heap[], int heapSize, int root) {
    if (root >= heapSize) return 1;

    int leftChild = 2 * root + 1;
    int rightChild = 2 * root + 2;

    if (leftChild >= heapSize || rightChild >= heapSize) // se il figlio sinistro o destro non esiste
        return 1;

    if (heap[root] < heap[leftChild] || heap[root] < heap[rightChild]) // se il nodo corrente è minore di uno dei due figli
        return 0;
    

    // se a sinistra è stato trovato un errore, è inutile scendere anche a destra
    if (isHeap(heap, heapSize, leftChild) == 0) // chiamata ricorsiva per il figlio sinistro
		return 0;

    return isHeap(heap, heapSize, rightChild);
}