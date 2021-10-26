#include "htab.h"
#include "io.h"
#include <stdlib.h>

//pro vetsinu tabulek je dobre mit dostatecnou velikost a zaroven aby byla prvocislo, nedochazi tolik ke kolizim
#define TABLE_SIZE 1009 
#define WORD_MAX_LENGHT 127

int main (){    
    
    htab_t * storage = htab_init(TABLE_SIZE);    
    if (storage == NULL){
        fprintf(stderr,"Chyba: nepodarilo se alokovat pamet pro tabulku\n");
        exit(1);
    } 

    htab_pair_t *result = NULL;
    char s[WORD_MAX_LENGHT] = {'\0'};
    while (read_word(s,WORD_MAX_LENGHT,stdin) != EOF){
        result = htab_lookup_add(storage,s);
        if (result == NULL){    //nepodarilo se pridat slovo
            fprintf(stderr,"Chyba: nepodarilo se alokovat pamet pro prvek: %s",s);
            htab_free(storage);
            exit(1); 
        }
        result->value++;
    }

    #ifdef MOVETEST
        htab_t * movetest_tab = htab_move(TABLE_SIZE/2,storage);  
        if (movetest_tab == NULL){
            fprintf(stderr,"Chyba: nepodarilo se alokovat pamet pro tabulku\n");
            exit(1);
        } 
        htab_for_each(movetest_tab,print_htab_item_values);
        htab_free(movetest_tab);
    #else
        htab_for_each(storage,print_htab_item_values); 
    #endif
       
    htab_free(storage);
    return 0;
}