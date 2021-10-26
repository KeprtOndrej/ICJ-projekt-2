// print_htab_item_values.c
// Řešení IJC-DU2, příklad 2), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#include "htab.h"
#include "private_htab.h"

void print_htab_item_values(htab_pair_t *data){    
    printf("%s\t%d\n",data->key,(int)data->value);    
}