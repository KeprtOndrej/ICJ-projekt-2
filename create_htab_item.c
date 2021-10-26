// create_htab_item.c
// Řešení IJC-DU2, příklad 2), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#include "htab.h"
#include "private_htab.h"

struct htab_item *create_htab_item(const htab_key_t key){    
    struct htab_item *item = malloc(sizeof(struct htab_item));
    if (item == NULL){
        return NULL;
    }
    item->next = NULL;
    item->data.value = 0;    
    char *new_key = malloc(strlen(key)+1); 
    if (new_key == NULL){
        free(item);
        return NULL;
    }
    strcpy(new_key,key);  //nastavim pole na hodnotu klice
    item->data.key = new_key; //ukazatel nastavim na pole, kde je klic
    return item;
}