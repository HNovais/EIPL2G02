/**
 *  @file main.c Ficheiro que contém a função principal do programa
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "parser.h"

/**
 * \brief Esta é a função principal do programa
 * 
 * Esta função recebe uma sequência de caracteres e forma uma string "line"
 * 
 * @returns O valor 0
 */
int main () {

	char line[10240];

	assert( fgets(line, 10240, stdin) != NULL);
	assert( line [strlen(line) - 1] == '\n');   // Se conseguir encontrar o \n no final quer dizer que leu a linha toda

    parse(line);
	return 0;
}
