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
 * \brief Esta é a função que cria a Stack
 *
 * @returns Stack
 */
STACK *novaStack(){
    return malloc(sizeof (STACK));

/**
 * \brief Esta é a função que vai fazer o parse de uma linha
 *
 * Esta função recebe uma string, faz o parse e as devidas operações aritméticas.
 *
 * @param line : A linha que foi lida e da qual se vai fazer o parse.
 */
    void parse (char *line) {

        STACK *stack = novaStack();
        stack->count = 0;

        char *delims = " \t\n";
        DADOS variaveis [26];
        // Variáveis com valor por omissão
        // A = 10
        variaveis['A'-65].tipo = 0;
        variaveis['A'-65].vl = 10;
        // B = 11
        variaveis['B'-65].tipo = 0;
        variaveis['B'-65].vl = 11;
        // C = 12
        variaveis['C'-65].tipo = 0;
        variaveis['C'-65].vl = 12;
        // D = 13
        variaveis['D'-65].tipo = 0;
        variaveis['D'-65].vl = 13;
        // E = 14
        variaveis['E'-65].tipo = 0;
        variaveis['E'-65].vl = 14;
        // F = 15
        variaveis['F'-65].tipo = 0;
        variaveis['F'-65].vl = 15;
        // N = '\n'
        variaveis['N'-65].tipo = 2;
        variaveis['N'-65].vc = '\n';
        // S = ' '
        variaveis['S'-65].tipo = 2;
        variaveis['S'-65].vc = ' ';
        // X = 0
        variaveis['X'-65].tipo = 0;
        variaveis['X'-65].vl = 0;
        // Y = 1
        variaveis['Y'-65].tipo = 0;
        variaveis['Y'-65].vl = 1;
        // Z = 2
        variaveis['Z'-65].tipo = 0;
        variaveis['Z'-65].vl = 2;

        for (char *token = strtok(line, delims); token != NULL; token = strtok(NULL, delims))
        {
            char *sobra;
            long val_i = strtol(token, &sobra, 10);
            if (strlen(sobra) == 0)
            {
                PUSHL(stack, val_i);
            }
            else
            {
                double val_d = strtod(token, &sobra);
                if (strlen(sobra) == 0)
                {
                    PUSHD(stack, val_d);
                }
                else
                {
                    (strcmp(token,"+")==0)  ? soma(stack) :
                    (strcmp(token,"-")==0)  ? subtracao(stack) :
                    (strcmp(token, "*")==0) ? multiplicacao(stack) :
                    (strcmp(token, "/")==0) ? divisao(stack) :
                    (strcmp(token, "(")==0) ? incrementar(stack) :
                    (strcmp(token, ")")==0) ? decrementar(stack) :
                    (strcmp(token, "%")==0) ? restoDivInt(stack) :
                    (strcmp(token, "#")==0) ? exponenciacao(stack) :
                    (strcmp(token, "&")==0) ? and(stack) :
                    (strcmp(token, "|")==0) ? or(stack) :
                    (strcmp(token, "^")==0) ? xor(stack) :
                    (strcmp(token, "~")==0) ? not(stack) :
                    (strcmp(token, "_")==0) ? duplicar(stack) :
                    (strcmp(token, ";")==0) ? lastOut(stack) :
                    (strcmp(token, "\\")==0)? switchTwo(stack) :
                    (strcmp(token, "@")==0) ? rotateThree(stack) :
                    (strcmp(token, "$")==0) ? copyN(stack) :
                    (strcmp(token, "i")==0) ? convInteiro(stack) :
                    (strcmp(token, "f")==0) ? convDouble(stack) :
                    (strcmp(token, "c")==0) ? convCaracter(stack) :
                    (strcmp(token, "s")==0) ? convString(stack) :
                    (strcmp(token, "l")==0) ? lerLinha(stack) :
                    (strcmp(token, "=")==0) ? igual(stack) :
                    (strcmp(token, "<")==0) ? menor(stack) :
                    (strcmp(token, ">")==0) ? maior(stack) :
                    (strcmp(token, "!")==0) ? nao(stack) :
                    (strcmp(token, "e&")==0) ? conjuncao(stack) :
                    (strcmp(token, "e|")==0) ? disjuncao(stack) :
                    (strcmp(token, "e<")==0) ? menorDe2(stack) :
                    (strcmp(token, "e>")==0) ? maiorDe2(stack) :
                    (strcmp(token, "?")==0)  ? ifThenElse(stack) :
                    (variableTeste(token)==0)  ? variableOut(stack, token, variaveis) :
                    (twoPointsTeste(token)==0) ? variableIn(stack, token, variaveis) :
                    doNothing();
                }
            }
        }
        PRINT_STACK(stack);
    }

/**
 * \brief Esta é a função auxiliar da função parse que permite o término do expression base
 */
    void doNothing()
    {}

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
 * @param stk: stack
 */
    void PRINT_STACK(STACK *stk) {
        int i;
        for (i = 0; i<stk->count; i++) {
            print_DADOS (stk->comp[i]);
        }
        putchar('\n');
    }

/**
 * \brief Esta é a função auxiliar que retira o último elemento do tipo long da stack
 *
 * @param stk: stack
 *
 * @returns O último elemento da stack
 */
    long POPL(STACK *stk) {
        long x;
        x = stk->comp[stk->count -1].vl;
        stk->count--;
        return x;
    }

/**
 * \brief Esta é a função auxiliar que retira o último elemento do tipo double da stack
 *
 * @param stk: stack
 *
 * @returns O último elemento da stack
 */
    double POPD(STACK *stk) {
        double x;
        x = stk->comp[stk->count -1].vd;
        stk->count--;
        return x;
    }

/**
 * \brief Esta é a função auxiliar que retira o último elemento do tipo char da stack
 *
 * @param stk: stack
 *
 * @returns O último elemento da stack
 */
    char POPC(STACK *stk) {
        char x;
        x = stk->comp[stk->count -1].vc;
        stk->count--;
        return x;
    }

/**
 * \brief Esta é a função auxiliar que retira o último elemento do tipo string da stack
 *
 * @param stk: stack
 *
 * @returns O último elemento da stack
 */
    char *POPS(STACK *stk)
    {
        char *x = stk->comp[stk->count-1].vs;
        stk->count--;
        return x;
    }

/**
 * \brief Esta é a função auxiliar que retira o último elemento da stack
 *
 * @param stk: stack
 *
 * @returns O último elemento da stack
 */
    DADOS POP(STACK *stk)
    {
        DADOS P = stk->comp[stk->count-1];
        stk->count--;
        return P;
    }

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo long na stack
 *
 * @param x : É o elemento que queremos colocar na stack
 * @param stk: stack
 */
    void PUSHL(STACK *stk, long x) {
        stk->comp[stk->count].tipo = 0;
        stk->comp[stk->count].vl = x;
        stk->count++;
    }

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo double na stack
 *
 * @param x : É o elemento que queremos colocar na stack
 * @param stk: stack
 */
    void PUSHD(STACK *stk, double x) {
        stk->comp[stk->count].tipo = 1;
        stk->comp[stk->count].vd = x;
        stk->count++;
    }

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo char na stack
 *
 * @param x : É o elemento que queremos colocar na stack
 * @param stk: stack
 */
    void PUSHC(STACK *stk, char x)
    {
        stk->comp[stk->count].tipo = 2;
        stk->comp[stk->count].vc = x;
        stk->count++;
    }

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo string na stack
 *
 * @param x : É o elemento que queremos colocar na stack
 * @param stk: stack
 */
    void PUSHS(STACK *stk, char *x)
    {
        stk->comp[stk->count].tipo = 3;
        stk->comp[stk->count].vs = x;
        stk->count++;
    }

/**
 * \brief Esta é a função auxiliar que põe um elemento na stack
 *
 * @param P : É o elemento que queremos colocar na stack
 * @param stk: stack
 */
    void PUSH(STACK *stk, DADOS P)
    {
        stk->comp[stk->count] = P;
        stk->count++;
    }

/**
 * \brief Esta é a função auxiliar que converte um long em dados
 *
 * @param x : É o elemento a ser convertido
 * @param stk: stack
 *
 * @returns Retorna uma estrutura do tipo Dados com o valor pretendido
 */
    DADOS longTOdados (long x) {
        DADOS P;
        P.tipo = 0;
        P.vl = x;

        return P;
    }

/**
 * \brief Esta é a função auxiliar que converte um double em dados
 *
 * @param x : É o elemento a ser convertido
 *
 * @returns Retorna uma estrutura do tipo Dados com o valor pretendido
 */
    DADOS doubleTOdados (double x) {
        DADOS P;
        P.tipo = 1;
        P.vd = x;

        return P;
    }

/**
 * \brief Esta é a função auxiliar que converte um char em dados
 *
 * @param x : É o elemento a ser convertido
 *
 * @returns Retorna uma estrutura do tipo Dados com o valor pretendido
 */
    DADOS charTOdados (char x) {
        DADOS P;
        P.tipo = 2;
        P.vc = x;

        return P;
    }

/**
 * \brief Esta é a função auxiliar que converte um elemento do tipo dados em long
 *
 * @param P : É o elemento a ser convertido
 *
 * @returns O valor no tipo long presente na estrutura de Dados
 */
    long dadosTOlong (DADOS P) {
        long x;
        x = P.vl;

        return x;
    }

/**
 * \brief Esta é a função auxiliar que converte um elemento do tipo dados em double
 *
 * @param P : É o elemento a ser convertido
 *
 * @returns O valor no tipo double presente na estrutura de Dados
 */
    double dadosTOdouble (DADOS P) {
        double x;
        x = P.vd;

        return x;
    }

/**
 * \brief Esta é a função auxiliar que permite a soma de dois elementos da stack
 *
 * @param stk : stack
 */
    void soma (STACK *stk)
    {
        int x, y;
        long Yl, Xl;
        double Yd, Xd;

        x = stk->comp[stk->count - 1].tipo;
        if (x == 0)
        {
            Yl = POPL(stk);
            Yd = 0.0;
        }
        else
        {
            Yd = POPD(stk);
            Yl = 0;
        }

        y = stk->comp[stk->count - 1].tipo;
        if (y == 0)
        {
            Xl = POPL(stk);
            Xd = 0.0;
        }
        else
        {
            Xd = POPD(stk);
            Xl = 0;
        }

        if (x == 0 && y == 0)
            PUSHL(stk, Xl + Yl);
        else
            PUSHD(stk, Xl + Xd + Yl + Yd);
    }

/**
 * \brief Esta é a função auxiliar que permite a subtração de dois elementos da stack
 *
 * @param stk : stack
 */
    void subtracao(STACK *stk)
    {
        int x, y;
        long Yl, Xl;
        double Yd, Xd;

        x = stk->comp[stk->count - 1].tipo;
        if (x == 0)
        {
            Yl = POPL(stk);
            Yd = 0.0;
        }
        else
        {
            Yd = POPD(stk);
            Yl = 0;
        }

        y = stk->comp[stk->count - 1].tipo;
        if (y == 0)
        {
            Xl = POPL(stk);
            Xd = 0.0;
        }
        else
        {
            Xd = POPD(stk);
            Xl = 0;
        }

        if (x == 0 && y == 0)
            PUSHL(stk, Xl - Yl);
        else
            PUSHD(stk, (Xl + Xd) - (Yl + Yd));
    }

/**
 * \brief Esta é a função auxiliar que permite a multiplicação de dois elementos da stack
 *
 * @param stk : stack
 */
    void multiplicacao(STACK *stk)
    {
        int x, y;
        long Yl, Xl;
        double Xd, Yd;

        x = stk->comp[stk->count - 1].tipo;
        if (x == 0)
        {
            Yl = POPL(stk);
            Yd = 0.0;
        }
        else
        {
            Yd = POPD(stk);
            Yl = 0;
        }

        y = stk->comp[stk->count - 1].tipo;
        if (y == 0)
        {
            Xl = POPL(stk);
            Xd = 0.0;
        }
        else
        {
            Xd = POPD(stk);
            Xl = 0;
        }

        if (x == 0 && y == 0)
            PUSHL(stk, Xl * Yl);
        else
            PUSHD(stk, (Xl + Xd) * (Yl + Yd));
    }

/**
 * \brief Esta é a função auxiliar que permite a divisão de dois elementos da stack
 *
 * @param stk : stack
 */
    void divisao(STACK *stk)
    {
        int x, y;
        long Yl, Xl;
        double Xd, Yd;

        x = stk->comp[stk->count - 1].tipo;
        if (x == 0)
        {
            Yl = POPL(stk);
            Yd = 0.0;
        }
        else
        {
            Yd = POPD(stk);
            Yl = 0;
        }

        y = stk->comp[stk->count - 1].tipo;
        if (y == 0)
        {
            Xl = POPL(stk);
            Xd = 0.0;
        }
        else
        {
            Xd = POPD(stk);
            Xl = 0;
        }

        if (x == 0 && y == 0)
            PUSHL(stk, Xl / Yl);
        else
            PUSHD(stk, (Xl + Xd) / (Yl + Yd));
    }

/**
 * \brief Esta é a função auxiliar que permite o incremento de um elemento da stack
 *
 * @param stk : stack
 */
    void incrementar(STACK *stk)
    {
        int x;
        long Xl;
        double Xd;
        char Xc;

        x = stk->comp[stk->count - 1].tipo;
        switch (x){
            case 0:
                Xl = POPL(stk);
                PUSHL(stk, Xl - 1);
                break;
            case 1:
                Xd = POPD(stk);
                PUSHD(stk, Xd - 1);
                break;
            case 2:
                Xc = POPC(stk);
                PUSHC(stk, Xc - 1);
                break;
        }
    }

/**
 * \brief Esta é a função auxiliar que permite o decremento de um elemento da stack
 *
 * @param stk : stack
 */
    void decrementar(STACK *stk)
    {
        int x;
        long Xl;
        double Xd;
        char Xc;

        x = stk->comp[stk->count - 1].tipo;
        switch (x){
            case 0:
                Xl = POPL(stk);
                PUSHL(stk, Xl + 1);
                break;
            case 1:
                Xd = POPD(stk);
                PUSHD(stk, Xd + 1);
                break;
            case 2:
                Xc = POPC(stk);
                PUSHC(stk, Xc + 1);
                break;
        }
    }

/**
 * \brief Esta é a função auxiliar que permite obter o resto da divisão inteira de dois elementos da stack
 *
 * @param stk : stack
 */
    void restoDivInt(STACK *stk)
    {
        int x, y;
        long Xl, Yl;

        x = stk->comp[stk->count - 1].tipo;
        if (x == 0)
            Xl = POPL(stk);

        y = stk->comp[stk->count - 1].tipo;
        if (y == 0)
            Yl = POPL(stk);

        if (x == 0 && y == 0)
            PUSHL(stk, Yl % Xl);
    }

/**
 * \brief Esta é a função auxiliar que faz a exponenciação de dois elementos da stack
 *
 * @param stk : stack
 */
    void exponenciacao(STACK *stk)
    {
        int x, y;
        long Xl, Yl;
        double Xd, Yd;

        x = stk->comp[stk->count - 1].tipo;
        if (x == 0)
        {
            Xl = POPL(stk);
            Xd = 0.0;
        }
        else
        {
            Xd = POPD(stk);
            Xl = 0;
        }

        y = stk->comp[stk->count - 1].tipo;
        if (y == 0)
        {
            Yl = POPL(stk);
            Yd = 0.0;
        }
        else
        {
            Yd = POPD(stk);
            Yl = 0;
        }

        if (x == 0 && y == 0)
            PUSHL(stk, pow(Yl, Xl));
        else
            PUSHD(stk, pow((Yl + Yd), (Xl + Xd)));
    }

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (e(bitwise))
 *
 * @param stk : stack
 */
    void and(STACK *stk)
    {
        int x, y;
        long Xl, Yl;

        x = stk->comp[stk->count - 1].tipo;
        if (x == 0)
            Xl = POPL(stk);

        y = stk->comp[stk->count - 1].tipo;
        if (y == 0)
            Yl = POPL(stk);

        if (x == 0 && y == 0)
            PUSHL(stk, Yl & Xl);
    }

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (ou(bitwise))
 *
 * @param stk : stack
 */
    void or(STACK *stk)
    {
        int x, y;
        long Xl, Yl;

        x = stk->comp[stk->count - 1].tipo;
        if (x == 0)
            Xl = POPL(stk);

        y = stk->comp[stk->count - 1].tipo;
        if (y == 0)
            Yl = POPL(stk);

        if (x == 0 && y == 0)
            PUSHL(stk, Yl | Xl);
    }

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (xor(bitwise))
 *
 * @param stk : stack
 */
    void xor(STACK *stk)
    {
        int x, y;
        long Xl, Yl;

        x = stk->comp[stk->count - 1].tipo;
        if (x == 0)
            Xl = POPL(stk);

        y = stk->comp[stk->count - 1].tipo;
        if (y == 0)
            Yl = POPL(stk);

        if (x == 0 && y == 0)
            PUSHL(stk, Yl ^ Xl);
    }

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (not(bitwise))
 *
 * @param stk : stack
 */
    void not(STACK *stk)
    {
        int x;
        long Xl;

        x = stk->comp[stk->count - 1].tipo;
        if (x == 0)
        {
            Xl = POPL(stk);
            PUSHL(stk, ~Xl);
        }
    }

/**
 * \brief Esta é a função auxiliar que duplica o elemento do topo da stack
 *
 * @param stk : stack
 */
    void duplicar(STACK *stk)
    {
        DADOS P = POP(stk);
        PUSH(stk, P);
        PUSH(stk, P);
    }

/**
 * \brief Esta é a função auxiliar que faz o POP do elemento no topo da stack
 *
 * @param stk : stack
 */
    void lastOut(STACK *stk)
    {
        POP(stk);
    }

/**
 * \brief Esta é a função auxiliar que troca os dois elementos do topo da stack
 *
 * @param stk : stack
 */
    void switchTwo(STACK *stk)
    {
        DADOS P = POP(stk);
        DADOS Z = POP(stk);
        PUSH(stk, P);
        PUSH(stk, Z);
    }

    /**
 * \brief Esta é a função auxiliar que roda os três elementos do topo da stack
 *
 * @param stk : stack
 */
    void rotateThree(STACK *stk)
    {
        DADOS P = POP(stk);
        DADOS Z = POP(stk);
        DADOS T = POP(stk);
        PUSH(stk, Z);
        PUSH(stk, P);
        PUSH(stk, T);
    }

/**
 * \brief Esta é a função auxiliar que copia o n-ésimo elemento para o topo da stack
 *
 * @param stk : stack
 */
    void copyN(STACK *stk)
    {
        long n = POPL(stk);
        PUSH(stk, stk->comp[stk->count - n - 1]);
    }

/**
 * \brief Esta é a função auxiliar que converte o elemento do topo da stack para um inteiro
 *
 * @param stk : stack
 */
    void convInteiro(STACK *stk)
    {
        int x;
        double Xd;
        char Xc, *Xs;

        x = stk->comp[stk->count - 1].tipo;
        switch (x){
            case 1:
                Xd = POPD(stk);
                PUSHL(stk, Xd);
                break;
            case 2:
                Xc = POPC(stk);
                PUSHL(stk, Xc);
                break;
            case 3:
                Xs = POPS(stk);
                PUSHL(stk, atol(Xs));
                break;
        }
    }

/**
 * \brief Esta é a função auxiliar que converte o elemento do topo da stack para um double
 *
 * @param stk : stack
 */
    void convDouble(STACK *stk)
    {
        int x;
        long Xl;
        char *Xs;

        x = stk->comp[stk->count - 1].tipo;
        switch (x){
            case 0:
                Xl = POPL(stk);
                PUSHD(stk, Xl);
                break;
            case 3:
                Xs = POPS(stk);
                PUSHD(stk, atof(Xs));
                break;
        }
    }

/**
 * \brief Esta é a função auxiliar que converte o elemento do topo da stack para um caracter
 *
 * @param stk : stack
 */
    void convCaracter(STACK *stk)
    {
        int x;
        long Xl;
        char *Xs;

        x = stk->comp[stk->count - 1].tipo;
        switch (x){
            case 0:
                Xl = POPL(stk);
                PUSHC(stk, Xl);
                break;
            case 3:
                Xs = POPS(stk);
                PUSHC(stk, atof(Xs));
                break;
        }
    }

/**
 * \brief Esta é a função auxiliar que converte o elemento do topo da stack para uma string
 */
    void convString()
    {
        /*
        int x;
        long Xl;
        double Xd;
        char Xc, *Xs;
        x = stack[count - 1].tipo;
        if (x == 0) {Xl = POPL();PUSHS(ltoa(Xl, Xs, 10));}
        else if (x==1) {Xd = POPD(); PUSHS(snprintf (Xs, count,stack[count], Xd));}
        else if (x==2) {Xc = POPC(); PUSHS(Xc);}
         */
    }

/**
 * \brief Esta é a função auxiliar que lê o conteúdo da próxima linha
 *
 * @param stk : stack
 */
    void lerLinha(STACK *stk)
    {
        char s[10240];
        assert (fgets(s, 10240, stdin) != NULL);
        PUSHS(stk, s);
    }

/**
 * \brief Esta é a função auxiliar que compara os elementos no topo da stack
 *
 * @param stk : stack
 */
    void igual(STACK *stk)
    {
        int x, y;
        long Xl, Yl;
        double Xd, Yd;

        x = stk->comp[stk->count-1].tipo;
        if (x == 0)
        {
            Xl = POPL(stk);
            Xd = 0.0;
        }
        else
        {
            Xd = POPD(stk);
            Xl = 0;
        }

        y = stk->comp[stk->count-1].tipo;
        if (y == 0)
        {
            Yl = POPL(stk);
            Yd = 0.0;
        }
        else
        {
            Yd = POPD(stk);
            Yl = 0;
        }

        if ((Xl+Xd) == (Yl+Yd))
            PUSHL(stk, 1);
        else
            PUSHL(stk, 0);
    }

/**
 * \brief Esta é a função auxiliar que verifica se o penúltimo elemento da stack é menor que o último
 *
 * @param stk : stack
 */
    void menor(STACK *stk)
    {
        int x, y;
        long Xl, Yl;
        double Xd, Yd;

        x = stk->comp[stk->count-1].tipo;
        if (x == 0)
        {
            Xl = POPL(stk);
            Xd = 0.0;
        }
        else
        {
            Xd = POPD(stk);
            Xl = 0;
        }

        y = stk->comp[stk->count-1].tipo;
        if (y == 0)
        {
            Yl = POPL(stk);
            Yd = 0.0;
        }
        else
        {
            Yd = POPD(stk);
            Yl = 0;
        }

        if ((Yl+Yd) < (Xl+Xd))
            PUSHL(stk, 1);
        else
            PUSHL(stk, 0);
    }

/**
 * \brief Esta é a função auxiliar que verifica se o penúltimo elemento da stack é maior que o último
 *
 * @param stk : stack
 */
    void maior(STACK *stk)
    {
        int x, y;
        long Xl, Yl;
        double Xd, Yd;

        x = stk->comp[stk->count-1].tipo;
        if (x == 0)
        {
            Xl = POPL(stk);
            Xd = 0.0;
        }
        else
        {
            Xd = POPD(stk);
            Xl = 0;
        }

        y = stk->comp[stk->count-1].tipo;
        if (y == 0)
        {
            Yl = POPL(stk);
            Yd = 0.0;
        }
        else
        {
            Yd = POPD(stk);
            Yl = 0;
        }

        if ((Yl+Yd) > (Xl+Xd))
            PUSHL(stk, 1);
        else
            PUSHL(stk, 0);
    }

/**
 * \brief Esta é a função auxiliar que coloca na stack o contrário do seu valor lógico
 *
 * @param stk : stack
 */
    void nao(STACK *stk)
    {
        int x;
        long Xl;
        double Xd;
        char Xc;

        x = stk->comp[stk->count-1].tipo;
        switch (x) {
            case 0:
                Xl = POPL(stk);
                if (Xl != 0)
                    PUSHL(stk, 0);
                else
                    PUSHL(stk, 1);
                break;
            case 1:
                Xd = POPD(stk);
                if (Xd != 0)
                    PUSHL(stk, 0);
                else
                    PUSHL(stk, 1);
                break;
            case 2:
                Xc = POPC(stk);
                if (Xc != 0)
                    PUSHL(stk, 0);
                else
                    PUSHL(stk, 1);
                break;
        }
    }

/**
 * \brief Esta é a função auxiliar que verifica a relação lógica conjuntiva entre dois elementos da stack
 *
 * @param stk : stack
 */
    void conjuncao(STACK *stk)
    {
        int x, y;
        long Xl, Yl;
        double Xd, Yd;

        x = stk->comp[stk->count-1].tipo;
        if (x==0)
        {
            Xl=POPL(stk);
            Xd=0.0;
        }
        else
        {
            Xd=POPD(stk);
            Xl=0;
        }

        y = stk->comp[stk->count-1].tipo;
        if (y==0)
        {
            Yl=POPL(stk);
            Yd=0.0;
        }
        else
        {
            Yd=POPD(stk);
            Yl=0;
        }

        if ((Xl+Xd)*(Yl+Yd) != 0)
        {
            if (x==0) PUSHL(stk, Xl);
            else PUSHD(stk, Xd);
        }
        else
            PUSHL(stk, 0);
    }

/**
 * \brief Esta é a função auxiliar que verifica a relação lógica disjuntiva entre dois elementos da stack
 *
 * @param stk : stack
 */
    void disjuncao(STACK *stk)
    {
        int x, y;
        long Xl, Yl;
        double Xd, Yd;

        x = stk->comp[stk->count-1].tipo;
        if (x==0)
        {
            Xl=POPL(stk);
            Xd=0.0;
        }
        else
        {
            Xd=POPD(stk);
            Xl=0;
        }

        y = stk->comp[stk->count-1].tipo;
        if (y==0)
        {
            Yl=POPL(stk);
            Yd=0.0;
        }
        else
        {
            Yd=POPD(stk);
            Yl=0;
        }
        if ((Yl+Yd) != 0)
        {
            if (y==0) PUSHL(stk, Yl);
            else PUSHD(stk, Yd);
        }
        else if ((Xl+Xd) != 0 && (Yl+Yd) == 0)
        {
            if(x==0)
                PUSHL(stk, Xl);
            else
                PUSHD(stk, Xd);
        }
        else
            PUSHL(stk, 0);
    }

/**
 * \brief Esta é a função auxiliar que coloca na stack o menor de 2 valores
 *
 * @param stk : stack
 */
void menorDe2(STACK *stk)
{
    int x, y;
    long Xl, Yl;
    double Xd, Yd;

    x = stk->comp[stk->count-1].tipo;
    if (x==0)
    {
        Xl=POPL(stk);
        Xd=0.0;
    }
    else
    {
        Xd=POPD(stk);
        Xl=0;
    }

    y = stk->comp[stk->count-1].tipo;
    if (y==0)
    {
        Yl=POPL(stk);
        Yd=0.0;
    }
    else
    {
        Yd=POPD(stk);
        Yl=0;
    }

    if ((Yl+Yd) < (Xl+Xd))
    {
        if (y==0)
            PUSHL(stk, Yl);
        else
            PUSHD(stk, Yd);
    }
    else
    {
        if (x==0)
            PUSHL(stk, Xl);
        else
            PUSHD(stk, Xd);
    }
}

/**
 * \brief Esta é a função auxiliar que coloca na stack o maior de 2 valores
 *
 * @param stk : stack
 */
void maiorDe2(STACK *stk)
{
    int x, y;
    long Xl, Yl;
    double Xd, Yd;

    x = stk->comp[stk->count-1].tipo;
    if (x==0)
    {
        Xl=POPL(stk);
        Xd=0.0;
    }
    else
    {
        Xd=POPD(stk);
        Xl=0;
    }

    y = stk->comp[stk->count-1].tipo;
    if (y==0)
    {
        Yl=POPL(stk);
        Yd=0.0;
    }
    else
    {
        Yd=POPD(stk);
        Yl=0;
    }

    if ((Yl+Yd) > (Xl+Xd))
    {
        if (y==0)
            PUSHL(stk, Yl);
        else
            PUSHD(stk, Yd);
    }
    else
    {
        if (x==0)
            PUSHL(stk, Xl);
        else
            PUSHD(stk, Xd);
    }
}

/**
 * \brief Esta é a função auxiliar que verifica a condição if-then-else de 3 elementos da stack
 *
 * @param stk : stack
 */
void ifThenElse(STACK *stk)
{
    int x, y, z;
    long Xl, Yl;
    double Xd, Yd, Z;

    x = stk->comp[stk->count-1].tipo;
    if (x == 0)
        Xl=POPL(stk);
    else
        Xd=POPD(stk);

    y = stk->comp[stk->count-1].tipo;
    if (y == 0)
        Yl=POPL(stk);
    else
        Yd=POPD(stk);

    z = stk->comp[stk->count-1].tipo;
    if (z == 0)
        Z = POPL(stk);
    else
        Z = POPD(stk);

    if (Z != 0)
    {
        if (y == 0) PUSHL(stk, Yl);
        else PUSHD(stk, Yd);
    }
    else
    {
        if (x == 0) PUSHL(stk, Xl);
        else PUSHD(stk, Xd);
    }
}

/**
 * \brief Esta é a função auxiliar que testa se a variável é um caracter do alfabeto maiúsculo
 *
 * @param t : string com o token
 *
 * @returns Verdadeiro ou Falso
 */
int variableTeste (char *t)
{
    char k;
    k = t[0];
    int res;

    if (k <= 90 && k >= 65) res = 0;
    else res = 1;

    return res;
}

/**
 * \brief Esta é a função auxiliar que testa se o primeiro caracter da string é :
 *
 * @param t : string com o token
 *
 * @returns Verdadeiro ou Falso
 */
int twoPointsTeste (char *t)
{
    char k;
    k = t[0];
    int res;

    if (k == ':') res = 0;
    else res = 1;

    return res;
}

/**
 * \brief Esta é a função auxiliar que coloca na stack a variável pretendida
 *
 * @param t : string com o token
 * @param variaveis : variáveis passíveis de serem colocadas (alfabeto maiúsculo)
 */
void variableOut (STACK *stk, char *t, DADOS variaveis[26])
{
    char k;
    k = t[0];
    DADOS P;
    int i = k - 65;
    P = variaveis[i];
    PUSH(stk, P);
}

/**
 * \brief Esta é a função auxiliar que verifica o elemento do topo da stack e o guarda na variável pretendida
 *
 * @param t : string com o token
 * @param variaveis : variáveis passíveis de serem colocadas (alfabeto maiúsculo)
 */
void variableIn (STACK *stk, char *t, DADOS variaveis[26])
{
    char k;
    k = t[1];
    DADOS P = TOP(stk);

    variaveis[k-65] = P;
}

/**
 * @brief Esta é a função que verifica o elemento do topo da stack
 *
 * @param stk: stack
 *
 * @returns O elemento no topo da stack
 */
    DADOS TOP(STACK *stk)
    {
        DADOS P = stk->comp[stk->count-1];
        return P;
    }