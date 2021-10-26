// htab_for_each.c
// Řešení IJC-DU2, příklad 2), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#include "htab.h"
#include "private_htab.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)){
    size_t arr_size = htab_bucket_count(t);
    struct htab_item * walking_item = NULL;
    for (size_t i = 0; i < arr_size;i++){
        walking_item = t->array[i];        
        while(walking_item != NULL){
            f(&(walking_item->data));
            walking_item = walking_item->next;
        }        
    }
}