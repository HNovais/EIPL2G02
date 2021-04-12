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
            }else if (strcmp(token, "&") == 0)
            {
                x = stack[count - 1].tipo;
                if (x == 0) { Yl = POPL();}
                y = stack[count - 1].tipo;
                if (y == 0) { Xl = POPL();}
                if (x == 0 && y == 0) PUSHL(Xl & Yl);
            }
            else if (strcmp(token, "|") == 0)
            {
                x = stack[count - 1].tipo;
                if (x == 0) { Yl = POPL();}
                y = stack[count - 1].tipo;
                if (y == 0) { Xl = POPL();}
                if (x == 0 && y == 0) PUSHL(Xl | Yl);
            }
            else if (strcmp(token, "^") == 0)
            {
                x = stack[count - 1].tipo;
                if (x == 0) { Yl = POPL();}
                y = stack[count - 1].tipo;
                if (y == 0) { Xl = POPL();}
                if (x == 0 && y == 0) PUSHL(Xl ^ Yl);
            }
            else if (strcmp(token, "~") == 0)
            {
                x = stack[count - 1].tipo;
                if (x == 0) {Yl = POPL();PUSHL(~Yl);}
            }
            else if (strcmp(token, "_") == 0)
            {
                DADOS P = POP();
                PUSH(P);
                PUSH(P);
            }
            else if (strcmp(token, ";") == 0)
            {
                POP();
            }
            else if (strcmp(token, "\\") == 0)
            {
                DADOS P = POP();
                DADOS Z = POP();
                PUSH(P);
                PUSH(Z);
            }
            else if (strcmp(token, "@") == 0)
            {
                DADOS P = POP();
                DADOS Z = POP();
                DADOS T = POP();
                PUSH(Z);
                PUSH(P);
                PUSH(T);
            }
            else if (strcmp(token, "$") == 0)
            {
                long n = POPL();
                PUSH(stack[count - n - 1]);
            }
            else if (strcmp(token, "i") == 0)
            {
                x = stack[count - 1].tipo;
                if (x == 1) {Yd = POPD();PUSHL(Yd);}
                else if (x == 2) {Xc = POPC(); PUSHL(Xc);}
                else if (x==3) {Xs = POPS(); PUSHL(atol(Xs));}
            }
            else if (strcmp(token, "f") == 0)
            {
                x = stack[count - 1].tipo;
                if (x == 0) {Yl = POPL(); PUSHD(Yl);}
                else if (x==3) {Xs = POPS(); PUSHD(atof(Xs));}
            }
            else if (strcmp(token, "c") == 0)
            {
                x = stack[count - 1].tipo;
                if (x == 0) {Yl = POPL(); PUSHC(Yl);}
                else if (x==3) {Xs = POPS(); PUSHC(atol(Xs));}
            }
            else if (strcmp(token, "s") == 0)
            {
                //x = stack[count - 1].tipo;
                //if (x == 0) {Yl = POPL();PUSHS(ltoa(Yl, Xs, 10));}
                //else if (x==1) {Yd = POPD(); PUSHS(snprintf (Xs, count,stack[count], Yd));}
                //else if (x==2) {Xc = POPC(); PUSHS(Xc);}
            }
            else if (strcmp(token, "l") == 0)
            {
                char s[10240];
                assert (fgets(s, 10240, stdin) != NULL);
                PUSHS(s);
            }
        }
    }
    PRINT_STACK(count);
}

/**
 * \brief Esta é a função auxiliar da PRINT_STACK que imprime um elemento dos diferentes tipos de dados
 *
 * @param d : É o elemento a ser imprimido
 */
void print_DADOS (DADOS d) {
    switch (d.tipo)
    {
        case 0 : printf("%ld", d.vl); break;
        case 1 : printf("%g", d.vd); break;
        case 2 : printf("%c", d.vc); break;
        case 3 : printf("%s", d.vs); break;
    }
}

/**
 * \brief Esta é a função auxiliar da parse que imprime a stack
 *
 * @param x : É o parametro que indica o tamanho da stack que será imprimida
 */
void PRINT_STACK(int x) {
    int i;
    for (i = 0; i<x; i++) {
        print_DADOS (stack[i]);
    }
    putchar('\n');
}

/**
 * \brief Esta é a função auxiliar que retira o último elemento do tipo long da stack
 *
 * @returns O último elemento da stack
 */
long POPL() {
    long x;
    x = stack[count -1].vl;
    count--;
    return x;
}

/**
 * \brief Esta é a função auxiliar que retira o último elemento do tipo double da stack
 *
 * @returns O último elemento da stack
 */
double POPD() {
    double x;
    x = stack[count -1].vd;
    count--;
    return x;
}

/**
 * \brief Esta é a função auxiliar que retira o último elemento do tipo char da stack
 *
 * @returns O último elemento da stack
 */
char POPC() {
    char x;
    x = stack[count -1].vc;
    count--;
    return x;
}

/**
 * \brief Esta é a função auxiliar que retira o último elemento do tipo string da stack
 *
 * @returns O último elemento da stack
 */
char *POPS()
{
    char *x = stack[count-1].vs;
    count--;
    return x;
}

/**
 * \brief Esta é a função auxiliar que retira o último elemento da stack
 *
 * @returns O último elemento da stack
 */
DADOS POP()
{
    DADOS P = stack[count-1];
    count--;
    return P;
}

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo long na stack
 *
 * @param x : É o elemento que queremos colocar na stack
 */
void PUSHL(long x) {
    stack[count].tipo = 0;
    stack[count].vl = x;
    count++;
}

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo double na stack
 *
 * @param x : É o elemento que queremos colocar na stack
 */
void PUSHD(double x) {
    stack[count].tipo = 1;
    stack[count].vd = x;
    count++;
}

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo char na stack
 *
 * @param x : É o elemento que queremos colocar na stack
 */
void PUSHC(char x)
{
    stack[count].tipo = 2;
    stack[count].vc = x;
    count++;
}

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo string na stack
 *
 * @param x : É o elemento que queremos colocar na stack
 */
void PUSHS(char *x)
{
    stack[count].tipo = 3;
    stack[count].vs = x;
    count++;
}

/**
 * \brief Esta é a função auxiliar que põe um elemento na stack
 *
 * @param P : É o elemento que queremos colocar na stack
 */
void PUSH(DADOS P)
{
    stack[count] = P;
    count++;
}
