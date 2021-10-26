// htab_erase.c
// Řešení IJC-DU2, příklad 2), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#include "htab.h"
#include "private_htab.h"


bool htab_erase(htab_t * t, htab_key_t key){
    size_t index = (htab_hash_function(key) % t->arr_size); //rychlejsi, nez volat funkci size_t htab_bucket_count(const htab_t * t), pokud se ale ukladani velikosti pole zmeni, bude se muset zmenit i zde, coz pri pouziti funkce nehrozi, ale zmena v tomto ukolu jiz nenastane...  
    struct htab_item *deleting_item = NULL;
    if (t->array[index] != NULL){
        if (strcmp((char *)key,(char *)t->array[index]->data.key) == 0){
            deleting_item = t->array[index];
            t->array[index] = t->array[index]->next;
            free_htab_item(deleting_item);
            t->size--;
            return true;
        }
    }
    else return false; //pokud na indexu nic nebylo

    struct htab_item *walking_item = t->array[index];
    while(walking_item->next != NULL){
        deleting_item = walking_item->next;
        if (strcmp((char *)deleting_item->data.key,(char *)key) == 0){
            walking_item->next = deleting_item->next;
            free_htab_item(deleting_item);
            t->size--;
            return true;
        }
        else walking_item = walking_item->next ;
    }
    return false; //prosel jsem cely list a nenasel jsem
}