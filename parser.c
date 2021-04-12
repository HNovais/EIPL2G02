/**
 * @file parser.c Ficheiro que contém as funções referentes ao parser.
 */
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/**
 * \brief Esta variável é a lista que guarda os elementos da stack, em tipo dados.
 */
DADOS stack[10240];

/**
 * \brief Esta variável serve de contador do número de elementos da stack.
 */
int count = 0;

/**
 * \brief Esta é a função que vai fazer o parse de uma linha
 *
 * Esta função recebe uma string, faz o parse e as devidas operações aritméticas.
 *
 * @param line : A linha que foi lida e da qual se vai fazer o parse.
 */
void parse (char *line) {

    int x, y;
    long Yl, Xl;
    double Yd, Xd;
    char Xc, *Xs, *delims = " \t\n";

    for (char *token = strtok(line, delims); token != NULL; token = strtok(NULL, delims))
    {
        char *sobra;
        long val_i = strtol(token, &sobra, 10);
        if (strlen(sobra) == 0)
        {
            PUSHL(val_i);
        }
        else
        {
            double val_d = strtod(token, &sobra);
            if (strlen(sobra) == 0)
            {
                PUSHD(val_d);
            }
            else if (strcmp(token, "+") == 0)
            {
                x = stack[count - 1].tipo;
                if (x == 0) {Yl = POPL();Yd = 0.0;}
                else {Yd = POPD();Yl = 0;}
                y = stack[count - 1].tipo;
                if (y == 0) {Xl = POPL();Xd = 0.0;}
                else {Xd = POPD();Xl = 0;}
                if (x == 0 && y == 0) PUSHL(Xl + Yl);
                else PUSHD(Xl + Xd + Yl + Yd);
            }
            else if (strcmp(token, "-") == 0)
            {
                x = stack[count - 1].tipo;
                if (x == 0) {Yl = POPL();Yd = 0.0;}
                else {Yd = POPD();Yl = 0;}
                y = stack[count - 1].tipo;
                if (y == 0) {Xl = POPL();Xd = 0.0;}
                else {Xd = POPD();Xl = 0;}
                if (x == 0 && y == 0) PUSHL(Xl - Yl);
                else PUSHD((Xl + Xd) - (Yl + Yd));
            }
            else if (strcmp(token, "*") == 0)
            {
                x = stack[count - 1].tipo;
                if (x == 0) {Yl = POPL();Yd = 0.0;}
                else {Yd = POPD();Yl = 0;}
                y = stack[count - 1].tipo;
                if (y == 0) {Xl = POPL();Xd = 0.0;}
                else {Xd = POPD();Xl = 0;}
                if (x == 0 && y == 0) PUSHL(Xl * Yl);
                else PUSHD((Xl + Xd) * (Yl + Yd));
            }
            else if (strcmp(token, "/") == 0)
            {
                x = stack[count - 1].tipo;
                if (x == 0) {Yl = POPL();Yd = 0.0;}
                else {Yd = POPD();Yl = 0;}
                y = stack[count - 1].tipo;
                if (y == 0) {Xl = POPL();Xd = 0.0;}
                else {Xd = POPD();Xl = 0;}
                if (x == 0 && y == 0) PUSHL(Xl / Yl);
                else PUSHD((Xl + Xd) / (Yl + Yd));
            }
            else if (strcmp(token, "(") == 0)
            {
                x = stack[count - 1].tipo;
                if (x == 0) {Xl = POPL();PUSHL(Xl - 1);}
                else if (x==1) {Xd = POPD();PUSHD(Xd - 1);}
                else if (x==2) {Xc = POPC();PUSHC(Xc -1);}
            }
            else if (strcmp(token, ")") == 0)
            {
                x = stack[count - 1].tipo;
                if (x == 0) {Xl = POPL();PUSHL(Xl + 1);}
                else if (x==1) {Xd = POPD();PUSHD(Xd + 1);}
                else if (x==2) {Xc = POPC();PUSHC(Xc +1);}
            }
            else if (strcmp(token, "%") == 0)
            {
                x = stack[count - 1].tipo;
                if (x == 0) { Yl = POPL();}
                y = stack[count - 1].tipo;
                if (y == 0) { Xl = POPL();}
                if (x == 0 && y == 0) PUSHL(Xl % Yl);
            }
            else if (strcmp(token, "#") == 0)
            {
                x = stack[count - 1].tipo;
                if (x == 0) {Yl = POPL();Yd = 0.0;}
                else {Yd = POPD();Yl = 0;}
                y = stack[count - 1].tipo;
                if (y == 0) {Xl = POPL();Xd = 0.0;}
                else {Xd = POPD();Xl = 0;}
                if (x == 0 && y == 0) PUSHL(pow(Xl, Yl));
                else PUSHD(pow((Xl + Xd), (Yl + Yd)));
            }