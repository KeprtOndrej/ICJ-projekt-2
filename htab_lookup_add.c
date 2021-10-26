// htab_lookup_add.c
// Řešení IJC-DU2, příklad 2), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#include "htab.h"
#include "private_htab.h"

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key){
    size_t index = (htab_hash_function(key) % t->arr_size); //rychlejsi, nez volat funkci size_t htab_bucket_count(const htab_t * t), pokud se ale t->arr_size nejak zmeni, bude se muset zmenit i zde, coz pri pouziti funkce nehrozi, ale zmena v tomto ukolu jiz nenastane... 
    if (t->array[index] == NULL){
        t->array[index] = create_htab_item(key);
        if (t->array[index] == NULL){
            return NULL;
        }
        t->size++;       
        return &(t->array[index]->data);
    }

    if (strcmp((char *)t->array[index]->data.key,(char *)key) == 0){
        return &(t->array[index]->data);
    }

    struct htab_item *walking_item = t->array[index];
    while (walking_item->next != NULL){        
        if (strcmp((char *)walking_item->next->data.key,(char *)key) == 0){            
            return &(walking_item->next->data);
        }
        walking_item = walking_item->next;
    }

    walking_item->next = create_htab_item(key);
    if (walking_item->next == NULL){      
        return NULL;
    }
    else{
        t->size++; 
        return &(walking_item->next->data);
    }     
}