#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MSG_LENGTH 256 // Lunghezza massima di un messaggio

typedef struct {
    char msg[MAX_MSG_LENGTH];  // Messaggio
    int n_likes;               // Numero di likes
} Post;

typedef struct {
    Post** posts;  // Array di puntatori a Post
    int size;      // Numero di post attualmente presenti
    int capacity;  // Numero di post massimo che possiamo inserire
} Bacheca;

int len(Bacheca* b) { 
    return b->size; 
}

int is_empty(Bacheca* b) { 
    return b->size == 0; 
}

void printPost(Post* p) {
    printf("Messaggio: %s\n", p->msg);
    printf("Likes: %d\n", p->n_likes);
}

// Aggiunge un post alla bacheca con politica FIFO
void append(Bacheca* bacheca, Post post) {
    if (bacheca->size == 0){
        bacheca->posts = (Post**)malloc(sizeof(Post*));
    }else{
        bacheca->posts = (Post**)realloc(bacheca->posts, (bacheca->size + 1) * sizeof(Post*));
    }
    
    Post *newPost = (Post*)malloc(sizeof(Post));

    if (newPost == NULL){
        perror("");
        return;
    }
    
    strcpy(newPost->msg, post.msg);
    newPost->n_likes = post.n_likes;

    bacheca->posts[bacheca->size] = newPost;
    bacheca->size++;
}

Post* pop(Bacheca* b) {
    if (is_empty(b)) {
        // La bacheca è vuota, quindi non ci sono post da restituire
        return NULL;
    }

    Post* p = b->posts[0]; // Prendiamo il primo post

    // Shiftiamo tutti i post di una posizione a sinistra per "eliminare" il primo post dalla bacheca
    for (int i = 1; i < b->size; i++) {
        b->posts[i - 1] = b->posts[i];
    }
    b->size--;

    return p;
}

void load_user_from_file(Bacheca* b, const char* file_name) {
    FILE* fp = fopen(file_name, "r");
    
    if (fp == NULL) {
        fprintf(stderr, "Errore nell'apertura del file %s\n", file_name);
        exit(1);
    }

    char line[MAX_MSG_LENGTH]; // Buffer per leggere una riga del file

    while (fgets(line, MAX_MSG_LENGTH, fp) != NULL) {
        // Leggiamo il messaggio dal file e rimuoviamo il carattere '\n' finale 
        line[strcspn(line, "\n")] = '\0'; // strcspn restituisce la posizione del primo carattere di line che è contenuto in "\n"

        // Creiamo un nuovo post e copiamo il messaggio
        Post* p = malloc(sizeof(Post));
        strcpy(p->msg, line);

        // Leggiamo il numero di likes dal file
        fgets(line, MAX_MSG_LENGTH, fp);
        p->n_likes = atoi(line); // atoi converte una stringa in un intero (atoi sta per "ascii to integer")

        append(b, *p);
    }
    fclose(fp);
}

int main() {
    Bacheca bacheca; // Creiamo una nuova bacheca
    bacheca.size = 0; // Inizialmente non ci sono post
    bacheca.capacity = 10; // Possiamo inserire al massimo 10 post
    bacheca.posts = malloc(bacheca.capacity * sizeof(Post*)); // Allochiamo l'array di post

    load_user_from_file(&bacheca, "utente42.txt"); // Carichiamo i post dell'utente 42

    char choice; // Scelta dell'utente

    while (1) {
        Post* post = pop(&bacheca); // Prendiamo il prossimo post
        // l'operazione di pop va fatta all'inizio del ciclo perchè se l'utente sceglie di fermarsi, il post attuale va rimesso nella bacheca

        if (post == NULL) {
            printf("Non ci sono altri post\n");
            break;
        }

        printPost(post); // Stampiamo il post

        printf(
            "Vuoi andare al prossimo post (p), aggiungere un like al post "
            "attuale (l), condividere il post attuale (c) o fermarti (f)? ");
        scanf(" %c", &choice);

        if (choice == 'p') {
            // Andiamo al prossimo post
            continue;

        } else if (choice == 'l') {
            // Aggiungiamo un like al post attuale e lo rimettiamo nella bacheca 
            post->n_likes++;
            append(&bacheca, *post);

        } else if (choice == 'c') {
            // Condividiamo il post attuale scrivendolo nel file condivisi.txt
            FILE* fp = fopen("condivisi.txt", "a");

            if (fp == NULL) {
                fprintf(stderr, "Errore nell'apertura del file condivisi.txt\n"); // stderr è lo standard error e serve per stampare messaggi di errore
                exit(1);
            }

            fprintf(fp, "%s\n", post->msg);
            fprintf(fp, "%d\n", post->n_likes);

            fclose(fp);

        } else if (choice == 'f') {
            // Usciamo dal ciclo
            break;

        } else {
            printf("Opzione non valida\n");
            append(&bacheca, *post); // Rimettiamo il post nella bacheca
        }
    }

    return 0;
}