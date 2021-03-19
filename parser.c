/**
 * @file Ficheiro que contém as funções referentes ao parser.
 */ 
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long stack[10240];
int count = 0;

/**
 * \brief Esta é a função que vai fazer o parse de uma linha
 * 
 * Esta função recebe uma string, faz o parse e as devidas operações aritméticas.
 * 
 * @param line : A linha que foi lida e da qual se vai fazer o parse.
 */
void parse (char *line) {

    char *delims = " \t\n"; // Conjundo dos delimitidaores

    for (char *token = strtok(line, delims); token != NULL; token = strtok(NULL, delims)) {
        char *sobra;
        long val_i = strtol(token, &sobra, 10);
        if (strlen(sobra) == 0) {
            PUSH(val_i); // cada vez que temos um inteiro, por na stack
        } else if (strcmp(token, "+") == 0) {
            long Y = POP();
            long X = POP();
            PUSH(X + Y);
        } else 	if (strcmp (token, "-") == 0) {
            long Y = POP();
            long X = POP();
            PUSH(X - Y);
        } else 	if (strcmp (token, "*") == 0) {
            long Y = POP();
            long X = POP();
            PUSH(X * Y);
        } else 	if (strcmp (token, "/") == 0) {
            long Y = POP();
            long X = POP();
            PUSH(X / Y);
        } else 	if (strcmp (token, "(") == 0) {
            long X = POP();
            PUSH(X-1);
        } else 	if (strcmp (token, ")") == 0) {
            long X = POP();
            PUSH(X+1);
        } else 	if (strcmp (token, "%") == 0) {
            long Y = POP();
            long X = POP();
            PUSH(X % Y);
        } else 	if (strcmp (token, "#") == 0) {
            long Y = POP();
            long X = POP();
            PUSH(pow(X,Y));
        } else 	if (strcmp (token, "&") == 0) {
            long Y = POP();
            long X = POP();
            PUSH(X & Y);
        } else 	if (strcmp (token, "|") == 0) {
            long Y = POP();
            long X = POP();
            PUSH(X | Y);
        } else 	if (strcmp (token, "^") == 0) {
            long Y = POP();
            long X = POP();
            PUSH(X ^ Y);
        } else 	if (strcmp (token, "~") == 0) {
            long X = POP();
            PUSH(~X);
        }
    }

    PRINT_STACK(count);

}

/**
 * \brief Esta é a função auxiliar da parse que imprime a stack
 *
 * @param x : É o parametro que indica o tamanho da stack que será imprimida
 */
void PRINT_STACK(int x) {
    int i;
    for (i = 0; i<x; i++) {
        printf("%ld", stack[i]);
    }
    putchar('\n');
}

/**
 * \brief Esta é a função auxiliar que retira o último elemento da stack
 *
 * @returns O último elemento da stack
 */
long POP() {
    int res = stack[count -1];
    count--;
    return res;
}

/**
 * \brief Esta é a função auxiliar que põe um elemento na stack
 *
 * @param i : É o elemento que queremos colocar na stack
 */
void PUSH(long i) {
    stack[count] = i;
    count++;
}
