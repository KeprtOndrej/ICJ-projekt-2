// htab_move.c
// Řešení IJC-DU2, příklad 2), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#include "htab.h"
#include "private_htab.h"

//funkce vraci NULL pokud se presun nepovede a v tabulce from zustanou data nenarusena
//pri velkych tabulkach bude tento algoritmus, narocny na pamet, protoze v jednu chvili budou dana data 2x v pameti,
//pokud ale pri presunu nastane chyba, nedojde ke ztrate dat
htab_t *htab_move(size_t n, htab_t *from){
    htab_t *tab = htab_init(n);
    if (tab == NULL){
        return NULL; 
    }  
    size_t old_arr_size = htab_bucket_count(from);
    struct htab_item *moving_item = NULL;
    for (size_t i = 0; i < old_arr_size;i++){
        moving_item = from->array[i];
        while(moving_item != NULL){ 
            htab_pair_t *new_pair = htab_lookup_add(tab, moving_item->data.key);
            if (new_pair == NULL){
                fprintf(stderr,"Chyba: nepodarilo se presunout tabulku\n");
                htab_free(tab);
                return NULL;
            }
            else{
                new_pair->value = moving_item->data.value;  
                moving_item = moving_item->next;
            }           
        }        
    }
    tab->size = htab_size(from);    
    htab_clear(from);
    return tab;
}