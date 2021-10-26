// htab_init.c
// Řešení IJC-DU2, příklad 2), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#include "htab.h"
#include "private_htab.h"

htab_t *htab_init(size_t n){
    htab_t *tab = calloc(1,sizeof(htab_t)+ sizeof(struct htab_item *[n]));
    if (tab == NULL){
        fprintf(stderr,"Chyba: nepodarilo se alokovat pamet pro novou hash table\n");
        return NULL;
    }
    tab->arr_size = n;
    tab->size = 0;  
    /*              
    for(size_t i = 0; i < n;i++){       //pokud by se misto calloc pouzil malloc
        tab->array[i] = NULL;           // ale NULL je definovan jako ((void*)0), proto to jiz pri alokaci pomoci calloc "nastavim na NULL"
    }                                   // pri vetsi tabulce by toto prochazeni mohlo spomalit program
    */
    return tab;
}