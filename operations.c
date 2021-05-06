/**
 * @file operations.c Ficheiro que contém as funções referentes às operações na stack do parser
 */
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/**
 * \brief Esta é a função auxiliar da função parserOperacoes que trata os casos relacionados com operações aritméticas
 *
 * @param stack: stack
 * @param token: token
 *
 * @returns Se alguma das operações for bem sucessida retorna 1, caso contrário retorna 0
 */
int aritmeticas(char *token, STACK *stack)
{
    int r=0;

    if(strcmp(token,"+") == 0) r = soma(stack);
    if(strcmp(token,"-") == 0) r = subtracao(stack);
    if(strcmp(token,"*") == 0) r = multiplicacao(stack);
    if(strcmp(token,"/") == 0) r = divisao(stack);
    if(strcmp(token,")") == 0) r = incrementar(stack);
    if(strcmp(token,"(") == 0) r = decrementar(stack);
    if(strcmp(token,"%") == 0) r = restoDivInt(stack);
    if(strcmp(token,"#") == 0) r = exponenciacao(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar da função parserOperacoes que trata os casos relacionados com operações lógicas
 *
 * @param stack: stack
 * @param token: token
 *
 * @returns Se alguma das operações for bem sucessida retorna 1, caso contrário retorna 0
 */
int logicas(char *token, STACK *stack)
{
    int r = 0;

    if(strcmp(token,"&") == 0) r = and(stack);
    if(strcmp(token,"|") == 0) r = or(stack);
    if(strcmp(token,"^") == 0) r = xor(stack);
    if(strcmp(token,"~") == 0) r = not(stack);
    if(strcmp(token,"e&")== 0) r = conjuncao(stack);
    if(strcmp(token,"e|")== 0) r = disjuncao(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar da função parserOperacoes que trata os casos relacionados com operações da stack
 *
 * @param stack: stack
 * @param token: token
 *
 * @returns Se alguma das operações for bem sucessida retorna 1, caso contrário retorna 0
 */

int opStack(char *token, STACK *stack)
{
    int r = 0;

    if(strcmp(token,"_")  == 0) r = duplicar(stack);
    if(strcmp(token,";")  == 0) r = lastOut(stack);
    if(strcmp(token,"\\") == 0) r = switchTwo(stack);
    if(strcmp(token,"@")  == 0) r = rotateThree(stack);
    if(strcmp(token,"$")  == 0) r = copyN(stack);
    if(strcmp(token,",")  == 0) r = stringSize(stack);
    //if(strcmp(token,"S/") == 0) r = spaces(stack);
    //if(strcmp(token,"N/") == 0) r = newLine(stack);
    //if(strcmp(token,"/")  == 0) r = separate(stack);


    return r;
}

/**
 * \brief Esta é a função auxiliar da função parserOperacoes que trata os casos relacionados com conversões entre tipos
 *
 * @param stack: stack
 * @param token: token
 *
 * @returns Se alguma das operações for bem sucessida retorna 1, caso contrário retorna 0
 */
int convertions(char *token, STACK *stack)
{
    int r = 0;

    if(strcmp(token,"i") == 0) r = convInteiro(stack);
    if(strcmp(token,"f") == 0) r = convDouble(stack);
    if(strcmp(token,"c") == 0) r = convCaracter(stack);
    if(strcmp(token,"l") == 0) r = lerLinha(stack);
    if(strcmp(token,"t") == 0) r = lerTudo(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar da função parserOperacoes que trata os casos relacionados com comparações de elementos da stack
 *
 * @param stack: stack
 * @param token: token
 *
 * @returns Se alguma das operações for bem sucessida retorna 1, caso contrário retorna 0
 */
int comparison(char *token, STACK *stack)
{
    int r = 0;

    if(strcmp(token,"<") == 0) r = menor(stack);
    if(strcmp(token,">") == 0) r = maior(stack);
    if(strcmp(token,"=") == 0) r = igual(stack);
    if(strcmp(token,"!") == 0) r = nao(stack);
    if(strcmp(token,"e<")== 0) r = menorDe2(stack);
    if(strcmp(token,"e>")== 0) r = maiorDe2(stack);
    if(strcmp(token,"?") == 0) r = ifThenElse(stack);
 
    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a soma de dois elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int soma (STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if (r == 1){

        if ((somaTiposTop(stack)) == 2) {
            P.data.vl = POPL(stack);
            Z.data.vl = POPL(stack);
            PUSHL(stack, Z.data.vl + P.data.vl);
        } else {
            P.data.vd = POPD(stack);
            Z.data.vd = POPD(stack);
            PUSHD(stack, Z.data.vd + P.data.vd);
        }
    }
    else r = concatenarStrings(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a concatenação de strings e/ou chars e strings
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int concatenarStrings(STACK *stack)
{
    int r = 0;

    if (somaTiposTop(stack) == 16) r = concatena2Strings(stack);
    else if (somaTiposTop(stack) == 12) r = concatenaCharString(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a concatenação de duas strings
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int concatena2Strings(STACK *stack)
{
    int r=0;
    DADOS P, Z;

    P.data.vs = POPS(stack);
    Z.data.vs = POPS(stack);
    char *s = calloc(strlen(P.data.vs)+strlen(Z.data.vs)+1, sizeof(char));
    unsigned int i;

    for (i=0; i<strlen(Z.data.vs); i++)
    {
        s[i] = Z.data.vs[i];
    }

    for (i=strlen(Z.data.vs); i < strlen(P.data.vs)+strlen(Z.data.vs); i++)
    {
        s[i] = P.data.vs[i-strlen(Z.data.vs)];
    }
    s[i] = '\0';

    PUSHS(stack, s);
    r=1;

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a concatenação de um caracter e uma string
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int concatenaCharString(STACK *stack)
{
    int r=0;
    DADOS P, Z;

    P = POP(stack);
    Z = POP(stack);

    if (P.tipo == CHAR)
    {
        char *s = malloc (2*sizeof(char));
        s[0] = P.data.vc;
        s[1] = '\0';
        Z.data.vs = realloc (Z.data.vs,5*sizeof(char));
        strcat(Z.data.vs, s);
        PUSHS(stack, Z.data.vs);
        free(s);
        r=1;
    }
    else // char string
    {
        char *s = malloc (2*sizeof(char));
        s[0] = Z.data.vc;
        s[1] = '\0';
        s = realloc (s, (strlen(P.data.vs)) * sizeof(char));
        strncat(s, P.data.vs, strlen(P.data.vs));
        PUSHS(stack, s);
        free(P.data.vs);
        r=1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a subtração de dois elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int subtracao (STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if(r == 1) {

    if ((somaTiposTop(stack)) == 2)
    {
        P.data.vl = POPL(stack);
        Z.data.vl = POPL(stack);
        PUSHL (stack, Z.data.vl-P.data.vl);
    }
    else
    {
        P.data.vd = POPD(stack);
        Z.data.vd = POPD(stack);
        PUSHD(stack, Z.data.vd-P.data.vd);
    }
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a multiplicação de dois elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int multiplicacao (STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if(r == 1)
    {
        if ((somaTiposTop(stack)) == 2)
        {
            P.data.vl = POPL(stack);
            Z.data.vl = POPL(stack);
            PUSHL (stack, P.data.vl*Z.data.vl);
        }
        else
        {
            P.data.vd = POPD(stack);
            Z.data.vd = POPD(stack);
            PUSHD(stack, P.data.vd*Z.data.vd);
        }
    }
    else r = replicateString(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a replicação de strings
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int replicateString(STACK *stack)
{
    int r = 0;

    DADOS P, Z;

    if (somaTiposTop(stack) == 9)
    {
        P = POP(stack);
        Z = POP(stack);
        unsigned int x = strlen(Z.data.vs);
        Z.data.vs = realloc (Z.data.vs, (strlen(Z.data.vs) + 1) * sizeof(char));

        for (unsigned int i = 0; i < (P.data.vl-1)*x; i++)
        {
            Z.data.vs[x+i] = Z.data.vs[i];
        }
        PUSHS(stack, Z.data.vs);
        r = 1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a divisão de dois elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int divisao (STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if(r == 1)
    {
        if ((somaTiposTop(stack)) == 2)
        {
            P.data.vl = POPL(stack);
            Z.data.vl = POPL(stack);
            PUSHL (stack, Z.data.vl/P.data.vl);
        }
        else
        {
            P.data.vd = POPD(stack);
            Z.data.vd = POPD(stack);
            PUSHD(stack, Z.data.vd/P.data.vd);
        }
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite o incremento de um elemento da stack e a remoção do último elemento de uma string
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int incrementar (STACK *stack)
{
    int r = 0;

    DADOS P = POP(stack);

    if(P.tipo == DOUBLE) {PUSHD(stack, (P.data.vd+1)); r = 1;}
    if(P.tipo == CHAR) {PUSHC(stack, (P.data.vc+1)); r = 1;}
    if(P.tipo == LONG) {PUSHL(stack, (P.data.vl+1)); r = 1;}
    if(P.tipo == STRING)
    {
        unsigned long t = strlen(P.data.vs);
        char x = P.data.vs[t-1];
        P.data.vs[t-1] = '\0';
        PUSHS(stack, P.data.vs);
        PUSHC(stack, x);
        r=1;

    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite o decremento de um elemento da stack e a remoção do primeiro elemento de uma string
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int decrementar (STACK *stack)
{
    int r = 0;

    DADOS P = POP(stack);
    if(P.tipo == DOUBLE) {PUSHD(stack, (P.data.vd-1)); r = 1;}
    if(P.tipo == CHAR) {PUSHC(stack, (P.data.vc-1)); r = 1;}
    if(P.tipo == LONG) {PUSHL(stack, (P.data.vl-1)); r = 1;}
    if(P.tipo == STRING)
    {
        char x = P.data.vs[0];
        unsigned long t = strlen(P.data.vs);
        for (unsigned int i=0; i < strlen(P.data.vs); i++)
        {
            P.data.vs[i] = P.data.vs[i+1];
        }
        P.data.vs[t-1] = '\0';
        PUSHS(stack, P.data.vs);
        PUSHC(stack, x);
        r = 1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite obter o resto da divisão inteira de dois elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int restoDivInt(STACK *stack)
{
    int r = 0;
    
    DADOS P, Z;

    if ((somaTiposTop(stack)) == 2)
    {
        r = 1;
        P.data.vl = POPL(stack);
        Z.data.vl = POPL(stack);
        PUSHL(stack, (Z.data.vl) % (P.data.vl));
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que faz a exponenciação de dois elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int exponenciacao(STACK *stack)
{
    int r = areNumbers(stack);
    int x = somaTiposTop(stack);

    DADOS P, Z;

    if (r == 1)
    {
        if (x == 2)
        {
            P.data.vl = POPL(stack);
            Z.data.vl = POPL(stack);
            PUSHL(stack, pow(Z.data.vl, P.data.vl));
        }
        else
        {
            P.data.vd = POPD(stack);
            Z.data.vd = POPD(stack);
            PUSHD(stack, pow(Z.data.vd, P.data.vd));
        }
    }
    else r = searchSubstring(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar que faz a procura de uma substring numa string
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int searchSubstring(STACK *stack)
{
    int r;
    int x = somaTiposTop(stack);

    DADOS P = POP(stack);
    DADOS Z = POP(stack);

    if (x == 16)
    {
        long pos;
        char *s = strstr(Z.data.vs, P.data.vs);

        if (s != NULL)
        {
            pos = s - Z.data.vs;
            PUSHL(stack, pos);
        }
        else PUSHL(stack, -1);
        r = 1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (e(bitwise))
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int and(STACK *stack)
{
    int r = 0;
    
    DADOS P, Z;

    if ((somaTiposTop(stack)) == 2)
    {

        r = 1;
        P.data.vl = POPL(stack);
        Z.data.vl = POPL(stack);
        PUSHL(stack, (Z.data.vl) & (P.data.vl));
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (ou(bitwise))
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int or(STACK *stack)
{
    int r = 0;
    
    DADOS P, Z;

    if ((somaTiposTop(stack)) == 2)
    {
        r = 1;
        P.data.vl = POPL(stack);
        Z.data.vl = POPL(stack);
        PUSHL(stack, (Z.data.vl) | (P.data.vl));
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (xor(bitwise))
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int xor(STACK *stack)
{
    int r = 0;
    
    DADOS P, Z;

    if ((somaTiposTop(stack)) == 2)
    {
        r = 1;
        P.data.vl = POPL(stack);
        Z.data.vl = POPL(stack);
        PUSHL(stack, (Z.data.vl) ^ (P.data.vl));
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (not(bitwise))
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int not(STACK *stack)
{
    int r = 0;
    
    DADOS P = TOP(stack);

    if (P.tipo == LONG)
    {
        r = 1;
        P.data.vl = POPL(stack);
        PUSHL(stack, ~(P.data.vl));
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que verifica a relação lógica conjuntiva entre dois elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int conjuncao(STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if(r == 1)
    {
        P.data.vd = POPD(stack);
        Z.data.vd = POPD(stack);
        ((P.data.vd != 0) && (Z.data.vd != 0)) ? PUSHD(stack, (P.data.vd)) : PUSHD(stack, 0);
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que verifica a relação lógica disjuntiva entre dois elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int disjuncao(STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if(r == 1)
    {
        P.data.vd = POPD(stack);
        Z.data.vd = POPD(stack);
        (Z.data.vd != 0) ? PUSHD(stack, (Z.data.vd)):
        (P.data.vd != 0 && Z.data.vd == 0) ? PUSHD(stack, P.data.vd):PUSHL(stack, 0);
    }

    return r;

}

/**
 * \brief Esta é a função auxiliar que duplica o elemento do topo da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int duplicar(STACK *stack)
{
    DADOS P = POP(stack);
    PUSH(stack, P);
    PUSH(stack, P);

    return 1;
}

/**
 * \brief Esta é a função auxiliar que faz o POP do elemento no topo da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int lastOut(STACK *stack)
{
    POP(stack);

    return 1;
}

/**
 * \brief Esta é a função auxiliar que troca os dois elementos do topo da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int switchTwo(STACK *stack)
{
    DADOS P = POP(stack);
    DADOS Z = POP(stack);
    PUSH(stack, P);
    PUSH(stack, Z);

    return 1;
}

/**
* \brief Esta é a função auxiliar que roda os três elementos do topo da stack
*
* @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
*/
int rotateThree(STACK *stack)
{
    DADOS P = POP(stack);
    DADOS Z = POP(stack);
    DADOS T = POP(stack);
    PUSH(stack, Z);
    PUSH(stack, P);
    PUSH(stack, T);

    return 1;
}

/**
 * \brief Esta é a função auxiliar que copia o n-ésimo elemento para o topo da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int copyN(STACK *stack)
{
    int r = 0;
    DADOS P = TOP(stack);

    if(P.tipo == LONG)
    {
        r = 1;
        long n = POPL(stack);
        PUSH(stack, stack->comp[stack->count - n - 1]);
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que converte o elemento do topo da stack para um inteiro
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int convInteiro(STACK *stack)
{
    int r = 0;

    DADOS P = POP(stack);

    if(P.tipo == LONG) {PUSH(stack, P); r = 1;}
    if(P.tipo == DOUBLE) {PUSHL(stack, P.data.vd); r = 1;}
    if(P.tipo == CHAR) {PUSHL(stack, P.data.vc); r = 1;}
    if(P.tipo == STRING) {PUSHL(stack, atol(P.data.vs)); r = 1;}

    return r;

}

/**
 * \brief Esta é a função auxiliar que converte o elemento do topo da stack para um double
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int convDouble(STACK *stack)
{
    int r = 0;

    DADOS P = POP(stack);

    if(P.tipo == LONG) {PUSHD(stack, P.data.vl); r = 1;}
    if(P.tipo == DOUBLE) {;PUSH(stack, P); r = 1;}
    if(P.tipo == STRING) {PUSHD(stack, atof(P.data.vs)); r = 1;}

    return r;
}

/**
 * \brief Esta é a função auxiliar que converte o elemento do topo da stack para um caracter
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int convCaracter(STACK *stack)
{
    int r = 0;

    DADOS P = POP(stack);

    if(P.tipo == LONG) {PUSHC(stack, P.data.vl); r = 1;}
    if(P.tipo == STRING) {PUSHC(stack, atof(P.data.vs)); r = 1;}

    return r;
}

/**
 * \brief Esta é a função auxiliar que lê o conteúdo da próxima linha
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int lerLinha(STACK *stack)
{
    char *s = malloc (10240 * sizeof(char));
    assert (fgets(s, 10240, stdin) != NULL);
    int x = strlen(s);
    char *p = malloc ((x+1) * sizeof(char));
    strcpy(p,s);
    PUSHS(stack, p);
    free(s);

    return 1;

}

/**
 * \brief Esta é a função auxiliar que lê o conteúdo de todas as linhas seguintes
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int lerTudo(STACK *stack)
{
    int r=0;
    char *s = malloc(10240*sizeof(char));
    char *t = malloc(10240*sizeof(char));
    while (fgets(s, 10240, stdin))
    {
        strcat(t, s);
        if (s[0] == '\n') break;
        r=1;
    }

    for (int i=0; i < 2; i++)
    {
        t[strlen(t)-1] = '\0';
    }

    PUSHS(stack, t);

    return r;
}

/**
 * \brief Esta é a função auxiliar que verifica se o penúltimo elemento da stack é menor que o último
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int menor(STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if (somaTiposTop(stack)==2 || somaTiposTop(stack) ==3 || somaTiposTop(stack)==4)
    {
        P.data.vd = POPD(stack);
        Z.data.vd = POPD(stack);
        ((Z.data.vd) < (P.data.vd)) ? PUSHL(stack, 1) : PUSHL(stack, 0);
        r=1;
    }
    else if (somaTiposTop(stack) == 16)
    {
        P = POP(stack);
        Z = POP(stack);
        if(strcmp(Z.data.vs, P.data.vs) < 0) PUSHL(stack, 1);
        else PUSHL(stack, 0);
        r=1;
    }
    else if (somaTiposTop(stack)==5) r = menorChar(stack);
    else r = firstChars(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar que trata dos casos em que comparamos números com caracteres
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int menorChar(STACK *stack)
{
    int r=0;
    DADOS P, Z;

    if (stack->comp[stack->count - 1].tipo == CHAR)
    {
        P.data.vc = POPD(stack);
        Z.data.vd = POPD(stack);
        (Z.data.vd < P.data.vc) ? PUSHL(stack, 1):PUSHL(stack, 0);
        r=1;
    }
    if (stack->comp[stack->count - 2].tipo == CHAR)
    {
        P.data.vd = POPD(stack);
        Z.data.vc = POPD(stack);
        (Z.data.vc < P.data.vd) ? PUSHL(stack, 1):PUSHL(stack, 0);
        r=1;
    }

    return r;
}


/**
 * \brief Esta é a função auxiliar que vai buscar x caracteres ao início da string
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int firstChars(STACK *stack)
{
    int r = 0;
    DADOS P, Z;

    if (somaTiposTop(stack) == 9)
    {
        P = POP(stack);
        Z = POP(stack);
        char *s = calloc(P.data.vl+1, sizeof(char));
        unsigned int i;

        for (i = 0; i < P.data.vl; i++)
        {
            s[i] = Z.data.vs[i];
        }
        s[i] = '\0';
        PUSHS(stack, s);
        r=1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que verifica se o penúltimo elemento da stack é maior que o último
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int maior(STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if (somaTiposTop(stack)==2 || somaTiposTop(stack) ==3 || somaTiposTop(stack)==4)
    {
        P.data.vd = POPD(stack);
        Z.data.vd = POPD(stack);
        ((Z.data.vd) > (P.data.vd)) ? PUSHL(stack, 1) : PUSHL(stack, 0);
        r=1;
    }
    else if (somaTiposTop(stack) == 16)
    {
        P = POP(stack);
        Z = POP(stack);
        if(strcmp(Z.data.vs, P.data.vs) > 0) PUSHL(stack, 1);
        else PUSHL(stack, 0);
        r=1;
    }
    else if (somaTiposTop(stack)==5) r = maiorChar(stack);
    else r = lastChars(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar que trata das comparações de números com caracteres
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int maiorChar(STACK *stack)
{
    int r=0;
    DADOS P, Z;

    if (stack->comp[stack->count - 1].tipo == CHAR)
    {
        P.data.vc = POPD(stack);
        Z.data.vd = POPD(stack);
        (Z.data.vd > P.data.vc) ? PUSHL(stack, 1):PUSHL(stack, 0);
        r=1;
    }
    if (stack->comp[stack->count - 2].tipo == CHAR)
    {
        P.data.vd = POPD(stack);
        Z.data.vc = POPD(stack);
        (Z.data.vc > P.data.vd) ? PUSHL(stack, 1):PUSHL(stack, 0);
        r=1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que vai buscar x caracteres ao fim da string
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int lastChars(STACK *stack)
{
    int r = 0;
    DADOS P, Z;

    if (somaTiposTop(stack) == 9)
    {
        P = POP(stack);
        Z = POP(stack);
        char *s = calloc(P.data.vl +1 ,sizeof(char));
        int x = 0;
        unsigned int i = 0;

        for (i = strlen(Z.data.vs)-P.data.vl; i < strlen(Z.data.vs); i++)
        {
            s[x] = Z.data.vs[i];
            x++;
        }
        s[i] = '\0';
        PUSHS(stack, s);
        r=1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que compara os elementos no topo da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int igual(STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if (r == 1)
    {
        P.data.vd = POPD(stack);
        Z.data.vd = POPD(stack);
        ((Z.data.vd) == (P.data.vd)) ? PUSHL(stack, 1) : PUSHL(stack, 0);
        r = 1;
    }
    else if (somaTiposTop(stack) == 16)
    {
        P = POP(stack);
        Z = POP(stack);
        int result = strcmp(P.data.vs, Z.data.vs);
        (result == 0) ? PUSHL(stack, 1) : PUSHL(stack, 0);
        r = 1;
    }
    else r = indexStrings(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar que compara os elementos no topo da stack que sejam strings
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int indexStrings (STACK *stack)
{
    int r;

    if (somaTiposTop(stack) == 9)
    {
        DADOS P = POP(stack);
        DADOS Z = POP(stack);
        PUSHC(stack, Z.data.vs[P.data.vl]);
        r = 1;
    }
    else  r = 0;

    return r;
}

/**
 * \brief Esta é a função auxiliar que coloca na stack o contrário do seu valor lógico
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int nao(STACK *stack)
{
    DADOS P = POP(stack);
    (P.tipo == LONG && P.data.vl!=0) ? PUSHL(stack, 0):
    (P.tipo == DOUBLE && P.data.vd!=0) ? PUSHL(stack, 0):
    (P.tipo == CHAR && P.data.vc!=0) ? PUSHL(stack, 0): PUSHL(stack, 1);

    return 1;
}

/**
 * \brief Esta é a função auxiliar que coloca na stack o menor de 2 valores
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int menorDe2(STACK *stack)
{
    int r = 0;

    DADOS P = POP(stack);
    DADOS Z = POP(stack);

    (P.tipo == LONG && Z.tipo == LONG) ?
    (((P.data.vl)<(Z.data.vl)) ? PUSH(stack, P): PUSH(stack, Z)):
    (P.tipo == STRING && Z.tipo == STRING) ?
    ((strcmp(Z.data.vs, P.data.vs) < 0) ? PUSH(stack, Z): PUSH(stack, P)) :
    (P.tipo == LONG && Z.tipo == DOUBLE) ?
    (((P.data.vl)<(Z.data.vd)) ? PUSH(stack, P): PUSH(stack, Z)) :
    (P.tipo == DOUBLE && Z.tipo == LONG) ?
    (((P.data.vd)<(Z.data.vl)) ? PUSH(stack, P) : PUSH(stack, Z)):
    (P.tipo == DOUBLE && Z.tipo == DOUBLE) ?
    (((P.data.vd)<(Z.data.vd)) ? PUSH(stack, P):PUSH(stack, Z)) :
    exit(0);
    r = 1;

    return r;
}

/**
 * \brief Esta é a função auxiliar que coloca na stack o maior de 2 valores
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int maiorDe2(STACK *stack)
{
    int r = 0;

    DADOS P = POP(stack);
    DADOS Z = POP(stack);

    (P.tipo == LONG && Z.tipo == LONG) ?
    (((P.data.vl)>(Z.data.vl)) ? PUSH(stack, P): PUSH(stack, Z)):
    (P.tipo == STRING && Z.tipo == STRING) ?
    ((strcmp(Z.data.vs, P.data.vs) > 0) ? PUSH(stack, Z): PUSH(stack, P)) :
    (P.tipo == LONG && Z.tipo == DOUBLE) ?
    (((P.data.vl)>(Z.data.vd)) ? PUSH(stack, P): PUSH(stack, Z)) :
    (P.tipo == DOUBLE && Z.tipo == LONG) ?
    (((P.data.vd)>(Z.data.vl)) ? PUSH(stack, P) : PUSH(stack, Z)):
    (P.tipo == DOUBLE && Z.tipo == DOUBLE) ?
    (((P.data.vd)>(Z.data.vd)) ? PUSH(stack, P):PUSH(stack, Z)) :
    exit(0);
    r = 1;

    return r;
}
/**
 * \brief Esta é a função auxiliar que verifica a condição if-then-else de 3 elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int ifThenElse(STACK *stack)
{
    DADOS P = POP(stack);
    DADOS Z = POP(stack);
    DADOS T = POP(stack);
    STACK *array = T.data.va;

    (T.tipo == LONG && T.data.vl == 0) ? PUSH(stack, P) :
    (T.tipo == DOUBLE && T.data.vd == 0) ? PUSH(stack, P):
    (T.tipo == CHAR && T.data.vc == '\0') ? PUSH(stack, P):
    (T.tipo == STRING && strlen(T.data.vs) == 0) ? PUSH(stack, P) :
    (T.tipo == ARRAY) ? ((array->count == 0) ? PUSH(stack, P) : PUSH(stack, Z)):
    PUSH(stack, Z);

    return 1;
}

/**
 * \brief Esta é a função auxiliar que verifica o tamanho de uma string no topo da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int stringSize(STACK *stack)
{
    int r = 0;

    DADOS P = TOP(stack);
    if (P.tipo == STRING)
    {
        P = POP(stack);
        unsigned long x = strlen(P.data.vs);
        PUSHL(stack, x);
        r = 1;
    }
    return r;
}


/**
 * \brief Esta é a função auxiliar que testa se a variável é um caracter do alfabeto maiúsculo
 *
 * @param t : string com o token
 *
 * @returns Verdadeiro ou Falso
 */
int variableTeste (char *token)
{
    char k;
    k = token[0];
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
int twoPointsTeste (char *token)
{
    char k;
    k = token[0];
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
 * @param stack : stack
 */
void variableOut (STACK *stackPointer[], char *token, DADOS variaveis[26], int *flag)
{
    char k;
    k = token[0];
    DADOS P;
    int i = k - 65;
    P = variaveis[i];
    PUSH(stackPointer[*flag], P);
}

/**
 * \brief Esta é a função auxiliar que verifica o elemento do topo da stack e o guarda na variável pretendida
 *
 * @param t : string com o token
 * @param variaveis : variáveis passíveis de serem colocadas (alfabeto maiúsculo)
 * @param stack : stack
 */
void variableIn (STACK *stackPointer[], char *token, DADOS variaveis[26], int *flag)
{
    char k;
    k = token[1];
    DADOS P = TOP(stackPointer[*flag]);

    variaveis[k-65] = P;
}
