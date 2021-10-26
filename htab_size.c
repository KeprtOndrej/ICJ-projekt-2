// htab_size.c
// Řešení IJC-DU2, příklad 2), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#include "htab.h"
#include "private_htab.h"

size_t htab_size(const htab_t * t){
    return t->size;
}