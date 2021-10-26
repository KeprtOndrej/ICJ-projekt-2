// htab_find.c
// Řešení IJC-DU2, příklad 2), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#include "htab.h"
#include "private_htab.h"

htab_pair_t * htab_find(htab_t * t, htab_key_t key){
    size_t index = (htab_hash_function(key) % t->arr_size);     //rychlejsi, nez volat funkci size_t htab_bucket_count(const htab_t * t), pokud se ale ukladani velikosti pole zmeni, bude se muset zmenit i zde, coz pri pouziti funkce nehrozi, ale zmena v tomto ukolu jiz nenastane... 
    struct htab_item *walking_item = t->array[index];
    while (walking_item != NULL){
        if (strcmp((char *)walking_item->data.key,(char *)key) == 0){
            return &(walking_item->data);
        }
        else walking_item = walking_item->next;
    }
    return NULL; //prosel jsem cely list a nenasel jsem
}