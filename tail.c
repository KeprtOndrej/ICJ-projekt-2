// tail.c
// Řešení IJC-DU2, příklad 1), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//CHARS_ON_LINE_MAX-1 znaku a jeden na '\n'
#define CHARS_ON_LINE_MAX 511 

int main(int argc, char *argv[]){    
    FILE *input = stdin; 
    long print_count = 10;
    char *input_file_name = NULL;
    bool print_all = false; 
    int c;  

    //obsluha argumentu
    switch (argc){
        case 1:    //bez parametru = tisk 10 radku ze stdin        
        break;

        case 2:
            input_file_name = argv[1];  //nastaveni vstupniho souboru a tisk 10 radku
        break;

        case 3:    // tisk ze stdin a nastaveni poctu radku
            if (!strcmp(argv[1],"-n")){
                char *end; 
                if (argv[2][0] == '+'){
                    print_all = true;
                }
                print_count = strtol(argv[2],&end,10);                
                if ((strcmp(end,"\0") != 0) || (print_count < 1)){
                    fprintf(stderr,"chyba: chybny format radku\n"); //mam err hlasku napsanou takto, protoze se pusti ikdyz budou radky zaporne nebo nebudou cislo  apod.
                    exit(1);
                }
            }
            else{
                fprintf(stderr,"chyba: spatny format argumentu\n");
                exit(1);
            } 
        break;

        case 4:
            if (!strcmp(argv[1],"-n")){ // pocet radku a vstupni soubor
                char *end;
                if (argv[2][0] == '+'){
                    print_all = true;
                }
                print_count = strtol(argv[2],&end,10);                
                if ((strcmp(end,"\0") != 0) || (print_count < 0)){
                    fprintf(stderr,"chyba: chybny format radku\n");
                    exit(1);
                }
                input_file_name = argv[3];
            }
            else if (!strcmp(argv[2],"-n")){ //vstupni soubor a pocet radku 
                char *end;
                if (argv[3][0] == '+'){
                    print_all = true;
                }
                print_count = strtol(argv[3],&end,10);                
                if ((strcmp(end,"\0") != 0) || (print_count < 0)){
                    fprintf(stderr,"chyba: chybny format radku\n");
                    exit(1);
                }
                input_file_name = argv[1];
            }
            else{
                fprintf(stderr,"chyba: spatny format argumentu\n");
                exit(1);
            } 
        break; //argc = 4

        default:    // nespravne parametry
            fprintf(stderr,"chyba: prilis mnoho argumentu\n");
            exit(1);
        break;       
    }// obsluha argumentu   

    if (print_count == 0){
        exit(0); // tail pri -n 0 skonci uspechem a nic neudela, podle UNIX programu tail
    }     
    
    //otevreni souboru pro cteni
    if (input_file_name != NULL){ //pokud byl zadan pokusim se jej otevrit, jinak ctu ze stdin
        input = fopen(input_file_name,"r");
        if (input == NULL){
            fprintf(stderr,"chyba: nepodarilo se otevrit soubor: %s\n",input_file_name);
            exit(1);
        }
    }

    //pokud pred cislem bylo +, preskocim print_count - 1 radku a vytisknu cely soubor a ukoncim cinost uspechem
    if (print_all){ 
        long line_skip_count = 0;
        print_count -= 1;
        while (line_skip_count < print_count){
            if ((c = fgetc(input)) == '\n'){
                line_skip_count++;      //pocitam radky, ktere preskakuji           
            }
            if (c == EOF){
                exit(0);    //pokud ma file mene radku, nez je pocet ktery se ma preskocit
            }
        }
        while ((c = fgetc(input)) != EOF){
            putc(c,stdout); //dokud neni EOF, tisknu soubor tak jak jej ctu
        }
        exit(0);
    }
  
    //alokace pameti pro jednotlive radky
    char * line_arr[print_count]; //pole ukazatelu 
    for (long i = 0; i < print_count;i++){                      
        line_arr[i] = calloc(sizeof(char),CHARS_ON_LINE_MAX+1); //alokace prostoru pro jednotlive radky, pouzivam calloc z duvodu, kdyby mel soubor mene radku jak pocet ktery se ma vytisknout, aby se tim nic "nevytisklo"
        if (line_arr[i] == NULL){                               //+1 abych mohl ulozit koncovou '\0'
            fprintf(stderr,"chyba: neuspesne alokovana pamet\n");
            exit(1);
        }
    }

    int exit_code = 0;
    //cteni ze soboru    
    long index = 0; //index, do ktereho bufferu (radku) ukladam znaky
    long char_index = 0;   
    while ((c = fgetc(input)) != EOF){
        line_arr[index][char_index] = c;
        char_index++;

        if ((char_index == CHARS_ON_LINE_MAX) && (c != '\n')){ //pokud bude radek delsi jak CHARS_ON_LINE_MAX delsi, ukonci se program s chybou
            if (exit_code == 0){
                fprintf(stderr,"Chyba: prekroceni delky radku\n");
                exit_code = 1;
            }             
            while((c = fgetc(input)) != '\n'){
                if (c == EOF){
                    break;
                } 
            }
            line_arr[index][char_index] = '\n';
            char_index = 0;
            index++;            
        }
        
        if(c == '\n'){          //precetl jsem konec radku, posouvam radek, index znaku posunuji na pocatek a na posledni misto ukladam '\0', abych nasledne pri tisku vytisknul pouze dany radek    
            line_arr[index][char_index] = '\0';
            index++;
            char_index = 0;            
        } 

        if (index == print_count){  //pokud jsem prekrocil pocet bufferu, zacinam ukladat do prvniho bufferu
            index = 0;
        }
    }//while ((c = fgetc(input)) != EOF)
    
    if(char_index != 0 && c != '\n'){           // pokud jsem dosel na konec souboru, ktery neni ukoncen "\n", musim na konec posledniho radku pridat "\0" 
        line_arr[index][char_index] = '\0';     //a zvetsit ukazatel radku, aby se mohlo hned cist a pridat '\0', aby bylo zajisteno spravne tisknuti
        index++;
        if (index == print_count){              //pokud nastane, ze bych se posunul mimo buffery, musim se vratit na zacatek
            index = 0;
        }
    }  

    //tisknuti radku
    //index ukazuje na misto kam se mel ukladat retezec, ale nastal konec, tedy ukazuje na prvni radek, co bych mel tisknout
    for(long i = 0; i < print_count;i++,index++){ //i mi hlida pocet radku, ktere mam vytisknout
        printf("%s",line_arr[index]); 
        if (index == print_count-1){
            index = -1; //dojdu na konec loopu a inkrementuje se mi na 0 a budu cist od zacatku
        }
    }   

    //uklid pameti
    for (long i = 0; i < print_count;i++){
        free(line_arr[i]);
    }    
    return exit_code;
}