#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Azienda {
    char nome[64];
    int dipendenti;
    int dipartimenti;
    int sedi;

    struct Azienda* next;
} Azienda;

void append_in_list(Azienda** head, Azienda val) {
    if (*head == NULL) {
        Azienda* p_new = malloc(sizeof(Azienda));

        *p_new = val;
        p_new->next = NULL;
        *head = p_new;

        return;
    }
    append_in_list(&((*head)->next), val);
}

void read_file(char filename[64], struct Azienda** head) {
    FILE* fp = fopen(filename, "r");
    struct Azienda tmp;

    if (fp == NULL) {
        perror("");
        exit(-1);
    }

    while (fscanf(fp, "%s %d %d %d", tmp.nome, &(tmp.dipendenti), &(tmp.dipartimenti), &(tmp.sedi)) == 4) {
        append_in_list(head, tmp);
    }
    fclose(fp);
}

void final_list(struct Azienda** head, int theshold) {
    struct Azienda* tmp = *head;
    struct Azienda* last_read = NULL;

    while (tmp != NULL) {
        if (tmp->dipendenti < theshold) {
            struct Azienda* delete = tmp;

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

void save_on_file(char filename[64], Azienda** head) {
    FILE* fp = fopen(filename, "w");

    if (fp == NULL){
        perror("");
        exit(-1);
    }

    while (*head != NULL) {
    
        Azienda* tmp = *head;
        Azienda* max = *head;
        Azienda* last_read = NULL;
        Azienda* last_read_max = NULL;

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

void print_list(Azienda* head) {
    if (head == NULL) return;
    printf(
        "Nome azienda: %s\nNumero dipendenti: %d\nNumero dipartimenti: %d\nNumero Sedi: %d\n\n",
        head->nome, head->dipendenti, head->dipartimenti, head->sedi);
    print_list(head->next);
}

void free_list(Azienda* head) {
    struct Azienda* tmp;
    while (head != NULL) {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}

int main() {
    struct Azienda* head = NULL;

    read_file("nome_aziende.txt", &head);
    print_list(head);
    printf("rimozione delle aziende con meno di 300 dipendenti\n\n");
    final_list(&head, 300);
    print_list(head);

    save_on_file("aziende.txt", &head);
    return 0;
}