// htab_clear.c
// Řešení IJC-DU2, příklad 2), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#include "htab.h"
#include "private_htab.h"

void htab_clear(htab_t * t){
    size_t arr_size = htab_bucket_count(t);
    struct htab_item *deleting_item = NULL;
	for (size_t index = 0; index < arr_size; index++){
		while(t->array[index] != NULL){
            deleting_item = t->array[index];
            t->array[index] = t->array[index]->next;
            free_htab_item(deleting_item);
        }
	}
    t->size = 0;
}