// private_htab.h
// Řešení IJC-DU2, příklad 2), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#ifndef __PRIVATE_HTAB_H__
#define __PRIVATE_HTAB_H__

#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

struct htab_item{
    htab_pair_t data;
    struct htab_item *next;
};

struct htab{
    size_t size;
    size_t arr_size;
    struct htab_item *array[];    
};

struct htab_item *create_htab_item(const htab_key_t key);
void free_htab_item(struct htab_item * item);
#endif //__PRIVATE_HTAB_H__