// io.c
// Řešení IJC-DU2, příklad 2), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#include "io.h"

int read_word(char *s, int max, FILE *f){  
    static bool was_err_msg = false;  
    int c;
    int char_index = 0;
    max -= 1;    
    while(1){
        c = getc(f);
        if (char_index == max && (!isspace(c) || c == EOF)){     
            s[char_index] = '\0';
            c = getc(f);
            while(!isspace(c)){
                if (c == EOF) break;
                c = getc(f); 
            }  

            if (!was_err_msg){
                fprintf(stderr,"Chyba: prilis dlouhe slovo: %s\n",s);
                was_err_msg = true;
            }         
            return max;
        }
        if (char_index == 0 && c == EOF){ //pokud bych mel sobour kde je konec radku a pak hned EOF
            return EOF;
        }
        if (isspace(c) && char_index == 0 ){ //preskoceni vicero bilych znaku po sobe 
            continue;
        }
        if (isspace(c) || c == EOF){    //soubor muze koncit slovem a pak hned EOF, tak aby se i to posledni slovo zapocitalo
            s[char_index] = '\0'; //pridam za slovo konec
            return strlen(s);                     
        }
        else{
            s[char_index++] = c;  //ukladani po znaku            
        }    
    }
    return  0; //deathcode
}
