// io.h
// Řešení IJC-DU2, příklad 2), 17.4.2021
// Autor: Ondřej Keprt, FIT
// Přeloženo: gcc 7.5
// 

#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int read_word(char *s, int max, FILE *f);

#endif