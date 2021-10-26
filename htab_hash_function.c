// htab_hash_function.c
// Řešení IJC-DU2, příklad 2), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#include "htab.h"
#include "private_htab.h"

#ifdef HASHTEST
    size_t htab_hash_function(const char *str) {
        //fprintf(stderr,"myhash\n");
        uint32_t hash = 43;
        uint32_t lenght = strlen(str);
        for(uint32_t i = 0; i < lenght;i++){
            hash = (str[i] * hash >> 4) + 33;
        }  
        return hash;
    }
#else 
    //funkce ze zadani
    size_t htab_hash_function(const char *str) {
        uint32_t h=0;     // musí mít 32 bitů
        const unsigned char *p;
        for(p=(const unsigned char*)str; *p!='\0'; p++){
            h = 65599*h + *p;
        }        
        return h;
    }
#endif