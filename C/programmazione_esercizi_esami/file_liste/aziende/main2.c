#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct GestoreProcessi {
    char nome[64];
    int dipendenti;
    int dipartimenti;
    int sedi;

    struct GestoreProcessi* next;
} GestoreProcessi;

void append_in_list(GestoreProcessi** head, GestoreProcessi val);
void read_file(char filename[64], struct GestoreProcessi** head);
void final_list(struct GestoreProcessi** head, int theshold);
void save_on_file(char filename[64], GestoreProcessi** head);
void print_list(GestoreProcessi* head);
void free_list(GestoreProcessi* head);

int main() {
    struct GestoreProcessi* head = NULL;

    read_file("nome_aziende.txt", &head);
    print_list(head);
    printf("rimozione delle aziende con meno di 300 dipendenti");
    final_list(&head, 300);
    print_list(head);

    save_on_file("aziende.txt", &head);
    return 0;
}

void append_in_list(GestoreProcessi** head, GestoreProcessi val) {
    if (*head == NULL) {
        GestoreProcessi* p_new = malloc(sizeof(GestoreProcessi));

        *p_new = val;
        p_new->next = NULL;
        *head = p_new;

        return;
    }
    append_in_list(&((*head)->next), val);
}

void read_file(char filename[64], struct GestoreProcessi** head) {
    FILE* fp = fopen(filename, "r");
    struct GestoreProcessi tmp;

    if (fp == NULL) {
        perror("");
        exit(-1);
    }

    while (fscanf(fp, "%s %d %d %d", tmp.nome, &(tmp.dipendenti), &(tmp.dipartimenti), &(tmp.sedi)) == 4) {
        append_in_list(head, tmp);
    }
    fclose(fp);
}

void final_list(struct GestoreProcessi** head, int theshold) {
    struct GestoreProcessi* tmp = *head;
    struct GestoreProcessi* last_read = NULL;

    while (tmp != NULL) {
        if (tmp->dipendenti < theshold) {
            struct GestoreProcessi* delete = tmp;

            if (last_read == NULL)
                *head = delete->next;
            else
                last_read->next = delete->next;

            tmp = delete->next;
            free(delete);
        } else {
            last_read = tmp;
            tmp = tmp->next;
        }
    }
}

void save_on_file(char filename[64], GestoreProcessi** head) {
    FILE* fp = fopen(filename, "w");

    if (fp == NULL) {
        perror("");
        exit(-1);
    }

    while (*head != NULL) {
        GestoreProcessi* tmp = *head;
        GestoreProcessi* max = *head;
        GestoreProcessi* last_read = NULL;
        GestoreProcessi* last_read_max = NULL;

        while (tmp != NULL) {
            if (tmp->dipendenti > max->dipendenti) {
                last_read_max = last_read;
                max = tmp;
            }

            last_read = tmp;
            tmp = tmp->next;
        }

        fprintf(fp, "%s %d %d %d\n", max->nome, max->dipendenti, max->dipartimenti, max->sedi);

        if (last_read_max == NULL)
            *head = max->next;
        else
            last_read_max->next = max->next;
        free(max);
    }

    fclose(fp);
}

void print_list(GestoreProcessi* head) {
    if (head == NULL) return;
    printf("Nome azienda: %s\nNumero dipendenti: %d\nNumero dipartimenti: %d\nNumero Sedi: %d\n\n", head->nome, head->dipendenti, head->dipartimenti,
           head->sedi);
    print_list(head->next);
}

void free_list(GestoreProcessi* head) {
    struct GestoreProcessi* tmp;
    while (head != NULL) {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}
