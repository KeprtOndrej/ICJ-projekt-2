// free_htab_item.c
// Řešení IJC-DU2, příklad 2), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#include "htab.h"
#include "private_htab.h"

void free_htab_item(struct htab_item * item){    
    free((void *)item->data.key);   // z const char delam void *,protoze prekladac haze warning,
    free(item);                     // ale k polozce uz by se nemelo pristupovat, mela by byt tedy smazana   
}