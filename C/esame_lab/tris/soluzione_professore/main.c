#include "headers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    
    struct Partita* p_head = NULL;
    
    int err;
    printf("leggo dal file...");
    err = load_matches_from_file("traccia1_configurazioni.txt", &p_head);
    err_handler(err);
    printf("prima della rimozione:\n");
    print_list(p_head);
    
    remove_tied(&p_head);
    
    
    printf("dopo la rimozione:\n");
    print_list(p_head);
    
    err = write_winners_on_file("traccia1_vittorie_X.txt", p_head, 'X');
    err_handler(err);
    err = write_winners_on_file("traccia1_vittorie_O.txt", p_head, 'O');
    err_handler(err);
    
    free_list(p_head);
    p_head = NULL;
}
