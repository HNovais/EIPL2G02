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
 * @param stk: stack
 * @param t: token
 */
int aritmeticas(char *t, STACK *stk)
{
    int r=0;

    if(strcmp(t,"+")==0) r = soma(stk);
    if(strcmp(t,"-")==0) r = subtracao(stk);
    if(strcmp(t,"*")==0) r = multiplicacao(stk);
    if(strcmp(t,"/")==0) r = divisao(stk);
    if(strcmp(t,")")==0) r = incrementar(stk);
    if(strcmp(t,"(")==0) r = decrementar(stk);
    if(strcmp(t,"%")==0) r = restoDivInt(stk);
    if(strcmp(t,"#")==0) r = exponenciacao(stk);

    return r;
}

/**
 * \brief Esta é a função auxiliar da função parserOperacoes que trata os casos relacionados com operações lógicas
 *
 * @param stk: stack
 * @param t: token
 */
int logicas(char *t, STACK *stk)
{
    int r = 0;

    if(strcmp(t,"&")==0) r = and(stk);
    if(strcmp(t,"|")==0) r = or(stk);
    if(strcmp(t,"^")==0) r = xor(stk);
    if(strcmp(t,"~")==0) r = not(stk);
    if(strcmp(t,"e&")==0) r = conjuncao(stk);
    if(strcmp(t,"e|")==0) r = disjuncao(stk);

    return r;
}

/**
 * \brief Esta é a função auxiliar da função parserOperacoes que trata os casos relacionados com operações da stack
 *
 * @param stk: stack
 * @param t: token
 */

int opStack(char *t, STACK *stk)
{
    int r = 0;

    if(strcmp(t,"_")==0) r = duplicar(stk);
    if(strcmp(t,";")==0) r = lastOut(stk);
    if(strcmp(t,"\\")==0) r = switchTwo(stk);
    if(strcmp(t,"@")==0) r = rotateThree(stk);
    if(strcmp(t,"$")==0) r = copyN(stk);
    if(strcmp(t,",")==0) r = stringSize(stk);
    //if(strcmp(t,"S/")==0) r = spaces(stk);
    //if(strcmp(t,"N/")==0) r = newLine(stk);


    return r;
}

/**
 * \brief Esta é a função auxiliar da função parserOperacoes que trata os casos relacionados com conversões entre tipos
 *
 * @param stk: stack
 * @param t: tokenR
 */
int convertions(char *t, STACK *stk)
{
    int r = 0;

    if(strcmp(t,"i")==0) r = convInteiro(stk);
    if(strcmp(t,"f")==0) r = convDouble(stk);
    if(strcmp(t,"c")==0) r = convCaracter(stk);
    //if(strcmp(t,"s")==0) r = convString(stk);
    if(strcmp(t,"l")==0) r = lerLinha(stk);
    //if(strcmp(t,"t")==0) r = lerTudo(stk);

    return r;
}

/**
 * \brief Esta é a função auxiliar da função parserOperacoes que trata os casos relacionados com comparações de elementos da stack
 *
 * @param stk: stack
 * @param t: token
 */
int comparison(char *t, STACK *stk)
{
    int r = 0;

    if(strcmp(t,"<")==0) r = menor(stk);
    if(strcmp(t,">")==0) r = maior(stk);
    if(strcmp(t,"=")==0) r = igual(stk);
    if(strcmp(t,"!")==0) r = nao(stk);
    if(strcmp(t,"e<")==0) r = menorDe2(stk);
    if(strcmp(t,"e>")==0) r = maiorDe2(stk);
    if(strcmp(t,"?")==0) r = ifThenElse(stk);
 
    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a soma de dois elementos da stack
 *
 * @param stk : stack
 */
int soma (STACK *stk)
{
    int r = areNumbers(stk);

    DADOS P, Z;

    if (r == 1){

        if ((tipoTop(stk)) == 2) {
            P.data.vl = POPL(stk);
            Z.data.vl = POPL(stk);
            PUSHL(stk, Z.data.vl + P.data.vl);
        } else {
            P.data.vd = POPD(stk);
            Z.data.vd = POPD(stk);
            PUSHD(stk, Z.data.vd + P.data.vd);
        }
    }
    else if (tipoTop(stk) == 16)
    {
        P.data.vs = POPS(stk);
        Z.data.vs = POPS(stk);
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

        PUSHS(stk, s);
        r=1;
    }
    else if (tipoTop(stk) == 12)
    {
        P = POP(stk); 
        Z = POP(stk); 

        if (P.tipo == CHAR) // string char
        {
            char *s = malloc (2*sizeof(char));
            s[0] = P.data.vc;
            s[1] = '\0';
            Z.data.vs = realloc (Z.data.vs,5*sizeof(char));
            strcat(Z.data.vs, s);
            PUSHS(stk, Z.data.vs);
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
            PUSHS(stk, s);
            free(P.data.vs);
            r=1;
        }
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a subtração de dois elementos da stack
 *
 * @param stk : stack
 */
int subtracao (STACK *stk)
{
    int r = areNumbers(stk);

    DADOS P, Z;

    if(r == 1) {

    if ((tipoTop(stk)) == 2)
    {
        P.data.vl = POPL(stk);
        Z.data.vl = POPL(stk);
        PUSHL (stk, Z.data.vl-P.data.vl);
    }
    else
    {
        P.data.vd = POPD(stk);
        Z.data.vd = POPD(stk);
        PUSHD(stk, Z.data.vd-P.data.vd);
    }
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a multiplicação de dois elementos da stack
 *
 * @param stk : stack
 */
int multiplicacao (STACK *stk)
{
    int r = areNumbers(stk);

    DADOS P, Z;

    if(r == 1)
    {
        if ((tipoTop(stk)) == 2)
        {
            P.data.vl = POPL(stk);
            Z.data.vl = POPL(stk);
            PUSHL (stk, P.data.vl*Z.data.vl);
        }
        else
        {
            P.data.vd = POPD(stk);
            Z.data.vd = POPD(stk);
            PUSHD(stk, P.data.vd*Z.data.vd);
        }
    }
    else if (tipoTop(stk) == 9)
    {
        P = POP(stk);
        Z = POP(stk);
        unsigned int x = strlen(Z.data.vs);
        Z.data.vs = realloc (Z.data.vs, (strlen(Z.data.vs) + 1) * sizeof(char));

        for (unsigned int i = 0; i < (P.data.vl-1)*x; i++)
        {
            Z.data.vs[x+i] = Z.data.vs[i];
        }
        PUSHS(stk, Z.data.vs);
        r = 1;
    }
    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a divisão de dois elementos da stack
 *
 * @param stk : stack
 */
int divisao (STACK *stk)
{
    int r = areNumbers(stk);

    DADOS P, Z;

    if(r == 1)
    {
        if ((tipoTop(stk)) == 2)
        {
            P.data.vl = POPL(stk);
            Z.data.vl = POPL(stk);
            PUSHL (stk, Z.data.vl/P.data.vl);
        }
        else
        {
            P.data.vd = POPD(stk);
            Z.data.vd = POPD(stk);
            PUSHD(stk, Z.data.vd/P.data.vd);
        }
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite o incremento de um elemento da stack
 *
 * @param stk : stack
 */
int incrementar (STACK *stk)
{
    int r = 0;

    DADOS P = POP(stk);

    if(P.tipo == DOUBLE) {PUSHD(stk, (P.data.vd+1)); r = 1;}
    if(P.tipo == CHAR) {PUSHC(stk, (P.data.vc+1)); r = 1;}
    if(P.tipo == LONG) {PUSHL(stk, (P.data.vl+1)); r = 1;}
    if(P.tipo == STRING)
    {
        unsigned long t = strlen(P.data.vs);
        char x = P.data.vs[t-1];
        P.data.vs[t-1] = '\0';
        PUSHS(stk, P.data.vs);
        PUSHC(stk, x);
        r=1;

    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite o decremento de um elemento da stack
 *
 * @param stk : stack
 */
int decrementar (STACK *stk)
{
    int r = 0;

    DADOS P = POP(stk);
    if(P.tipo == DOUBLE) {PUSHD(stk, (P.data.vd-1)); r = 1;}
    if(P.tipo == CHAR) {PUSHC(stk, (P.data.vc-1)); r = 1;}
    if(P.tipo == LONG) {PUSHL(stk, (P.data.vl-1)); r = 1;}
    if(P.tipo == STRING)
    {
        char x = P.data.vs[0];
        unsigned long t = strlen(P.data.vs);
        for (unsigned int i=0; i < strlen(P.data.vs); i++)
        {
            P.data.vs[i] = P.data.vs[i+1];
        }
        P.data.vs[t-1] = '\0';
        PUSHS(stk, P.data.vs);
        PUSHC(stk, x);
        r = 1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite obter o resto da divisão inteira de dois elementos da stack
 *
 * @param stk : stack
 */
int restoDivInt(STACK *stk)
{
    int r = 0;
    
    DADOS P, Z;

    if ((tipoTop(stk)) == 2) {

    r = 1;
    P.data.vl = POPL(stk);
    Z.data.vl = POPL(stk);
    PUSHL(stk, (Z.data.vl) % (P.data.vl));
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que faz a exponenciação de dois elementos da stack
 *
 * @param stk : stack
 */
int exponenciacao(STACK *stk)
{
    int r = areNumbers(stk);

    DADOS P, Z;

    if(r == 1)
    {

        if ((tipoTop(stk)) == 2) {
            P.data.vl = POPL(stk);
            Z.data.vl = POPL(stk);
            PUSHL(stk, pow(Z.data.vl, P.data.vl));
        } else {
            P.data.vd = POPD(stk);
            Z.data.vd = POPD(stk);
            PUSHD(stk, pow(Z.data.vd, P.data.vd));
        }
    }
    else if (tipoTop(stk)==16)
    {
        P = POP(stk);
        Z = POP(stk);
        long pos;
        char *s = strstr(Z.data.vs, P.data.vs);

        if (s != NULL)
        {
            pos = s - Z.data.vs;
            PUSHL(stk, pos);
        }
        else PUSHL(stk, -1);
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (e(bitwise))
 *
 * @param stk : stack
 */
int and(STACK *stk)
{
    int r = 0;
    
    DADOS P, Z;

    if ((tipoTop(stk)) == 2) {

    r = 1;
    P.data.vl = POPL(stk);
    Z.data.vl = POPL(stk);
    PUSHL(stk, (Z.data.vl) & (P.data.vl));
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (ou(bitwise))
 *
 * @param stk : stack
 */
int or(STACK *stk)
{
    int r = 0;
    
    DADOS P, Z;

    if ((tipoTop(stk)) == 2) {

    r = 1;
    P.data.vl = POPL(stk);
    Z.data.vl = POPL(stk);
    PUSHL(stk, (Z.data.vl) | (P.data.vl));
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (xor(bitwise))
 *
 * @param stk : stack
 */
int xor(STACK *stk)
{
    int r = 0;
    
    DADOS P, Z;

    if ((tipoTop(stk)) == 2) {

    r = 1;
    P.data.vl = POPL(stk);
    Z.data.vl = POPL(stk);
    PUSHL(stk, (Z.data.vl) ^ (P.data.vl));
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (not(bitwise))
 *
 * @param stk : stack
 */
int not(STACK *stk)
{
    int r = 0;
    
    DADOS P = TOP(stk);

    if (P.tipo == LONG) {

    r = 1;
    P.data.vl = POPL(stk);
    PUSHL(stk, ~(P.data.vl));
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que verifica a relação lógica conjuntiva entre dois elementos da stack
 *
 * @param stk : stack
 */
int conjuncao(STACK *stk)
{
    int r = 0;

    r = areNumbers(stk);

    DADOS P, Z;

    if(r == 1) {
    P.data.vd = POPD(stk);
    Z.data.vd = POPD(stk);
    ((P.data.vd != 0) && (Z.data.vd != 0)) ? PUSHD(stk, (P.data.vd)) : PUSHD(stk, 0);
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que verifica a relação lógica disjuntiva entre dois elementos da stack
 *
 * @param stk : stack
 */
int disjuncao(STACK *stk)
{
    int r = areNumbers(stk);

    DADOS P, Z;

    if(r == 1) {
    P.data.vd = POPD(stk);
    Z.data.vd = POPD(stk);
    (Z.data.vd != 0) ? PUSHD(stk, (Z.data.vd)):
    (P.data.vd != 0 && Z.data.vd == 0) ? PUSHD(stk, P.data.vd):PUSHL(stk, 0);
    }

    return r;

}

/**
 * \brief Esta é a função auxiliar que duplica o elemento do topo da stack
 *
 * @param stk : stack
 */
int duplicar(STACK *stk)
{
    DADOS P = POP(stk);
    PUSH(stk, P);
    PUSH(stk, P);

    return 1;
}

/**
 * \brief Esta é a função auxiliar que faz o POP do elemento no topo da stack
 *
 * @param stk : stack
 */
int lastOut(STACK *stk)
{
    POP(stk);

    return 1;
}

/**
 * \brief Esta é a função auxiliar que troca os dois elementos do topo da stack
 *
 * @param stk : stack
 */
int switchTwo(STACK *stk)
{
    DADOS P = POP(stk);
    DADOS Z = POP(stk);
    PUSH(stk, P);
    PUSH(stk, Z);

    return 1;
}

/**
* \brief Esta é a função auxiliar que roda os três elementos do topo da stack
*
* @param stk : stack
*/
int rotateThree(STACK *stk)
{
    DADOS P = POP(stk);
    DADOS Z = POP(stk);
    DADOS T = POP(stk);
    PUSH(stk, Z);
    PUSH(stk, P);
    PUSH(stk, T);

    return 1;
}

/**
 * \brief Esta é a função auxiliar que copia o n-ésimo elemento para o topo da stack
 *
 * @param stk : stack
 */
int copyN(STACK *stk)
{
    int r = 0;
    DADOS P = TOP(stk);

    if(P.tipo == LONG) {

    r = 1;
    long n = POPL(stk);
    PUSH(stk, stk->comp[stk->count - n - 1]);
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que converte o elemento do topo da stack para um inteiro
 *
 * @param stk : stack
 */
int convInteiro(STACK *stk)
{
    int r = 0;

    DADOS P = POP(stk);

    if(P.tipo == LONG) {PUSH(stk, P); r = 1;}
    if(P.tipo == DOUBLE) {PUSHL(stk, P.data.vd); r = 1;}
    if(P.tipo == CHAR) {PUSHL(stk, P.data.vc); r = 1;}
    if(P.tipo == STRING) {PUSHL(stk, atol(P.data.vs)); r = 1;}

    return r;

}

/**
 * \brief Esta é a função auxiliar que converte o elemento do topo da stack para um double
 *
 * @param stk : stack
 */
int convDouble(STACK *stk)
{
    int r = 0;

    DADOS P = POP(stk);

    if(P.tipo == LONG) {PUSHD(stk, P.data.vl); r = 1;}
    if(P.tipo == DOUBLE) {PUSH(stk, P); r = 1;}
    if(P.tipo == STRING) {PUSHD(stk, atof(P.data.vs)); r = 1;}

    return r;
}

/**
 * \brief Esta é a função auxiliar que converte o elemento do topo da stack para um caracter
 *
 * @param stk : stack
 */
int convCaracter(STACK *stk)
{
    int r = 0;

    DADOS P = POP(stk);

    if(P.tipo == LONG) {PUSHC(stk, P.data.vl); r = 1;}
    if(P.tipo == STRING) {PUSHC(stk, atof(P.data.vs)); r = 1;}

    return r;
}

/*
brief Esta é a função auxiliar que converte o elemento do topo da stack para uma string
void convString(STACK *stk)
{
}
*/

/**
 * \brief Esta é a função auxiliar que lê o conteúdo da próxima linha
 *
 * @param stk : stack
 */
int lerLinha(STACK *stk)
{
    char *s = malloc (10240 * sizeof(char));
    assert (fgets(s, 10240, stdin) != NULL);
    int x = strlen(s);
    char *p = malloc ((x+1) * sizeof(char));
    strcpy(p,s);
    PUSHS(stk, p);
    free(s);

    return 1;

}

/*
int lerTudo(STACK *stk)
{

}
*/
/**
 * \brief Esta é a função auxiliar que verifica se o penúltimo elemento da stack é menor que o último
 *
 * @param stk : stack
 */
int menor(STACK *stk)
{
    int r = areNumbers(stk);

    DADOS P, Z;

    if (tipoTop(stk)==2 || tipoTop(stk) ==3 || tipoTop(stk)==4)
    {
        P.data.vd = POPD(stk);
        Z.data.vd = POPD(stk);
        ((Z.data.vd) < (P.data.vd)) ? PUSHL(stk, 1) : PUSHL(stk, 0);
        r=1;
    }
    else if (tipoTop(stk)==5)
    {
        if (stk->comp[stk->count - 1].tipo == CHAR)
        {
            P.data.vc = POPD(stk);
            Z.data.vd = POPD(stk);
            (Z.data.vd < P.data.vc) ? PUSHL(stk, 1):PUSHL(stk, 0);
            r=1;
        }
        if (stk->comp[stk->count - 2].tipo == CHAR)
        {
            P.data.vd = POPD(stk);
            Z.data.vc = POPD(stk);
            (Z.data.vc < P.data.vd) ? PUSHL(stk, 1):PUSHL(stk, 0);
            r=1;
        }
    }
    else if (tipoTop(stk) == 16)
    {
        P = POP(stk);
        Z = POP(stk);
        if(strcmp(Z.data.vs, P.data.vs) < 0) PUSHL(stk, 1);
        else PUSHL(stk, 0);
        r=1;
    }
    else if (tipoTop(stk) == 9)
    {
        P = POP(stk);
        Z = POP(stk);
        char *s = calloc(P.data.vl+1, sizeof(char));
        unsigned int i;

        for (i = 0; i < P.data.vl; i++)
        {
            s[i] = Z.data.vs[i];
        }
        s[i] = '\0';
        PUSHS(stk, s);
        r=1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que verifica se o penúltimo elemento da stack é maior que o último
 *
 * @param stk : stack
 */
int maior(STACK *stk)
{
    int r = areNumbers(stk);

    DADOS P, Z;

    if (tipoTop(stk)==2 || tipoTop(stk) ==3 || tipoTop(stk)==4)
    {
        P.data.vd = POPD(stk);
        Z.data.vd = POPD(stk);
        ((Z.data.vd) > (P.data.vd)) ? PUSHL(stk, 1) : PUSHL(stk, 0);
        r=1;
    }
    else if (tipoTop(stk)==5)
    {
        if (stk->comp[stk->count - 1].tipo == CHAR)
        {
            P.data.vc = POPD(stk);
            Z.data.vd = POPD(stk);
            (Z.data.vd > P.data.vc) ? PUSHL(stk, 1):PUSHL(stk, 0);
            r=1;
        }
        if (stk->comp[stk->count - 2].tipo == CHAR)
        {
            P.data.vd = POPD(stk);
            Z.data.vc = POPD(stk);
            (Z.data.vc > P.data.vd) ? PUSHL(stk, 1):PUSHL(stk, 0);
            r=1;
        }
    }
    else if (tipoTop(stk) == 16)
    {
        P = POP(stk);
        Z = POP(stk);
        if(strcmp(Z.data.vs, P.data.vs) > 0) PUSHL(stk, 1);
        else PUSHL(stk, 0);
        r=1;
    }
    else if (tipoTop(stk) == 9)
    {
        P = POP(stk);
        Z = POP(stk);
        char *s = calloc(P.data.vl +1 ,sizeof(char));
        int x = 0;
        unsigned int i = 0;

        for (i = strlen(Z.data.vs)-P.data.vl; i < strlen(Z.data.vs); i++)
        {
            s[x] = Z.data.vs[i];
            x++;
        }
        s[i] = '\0';
        PUSHS(stk, s);
        r=1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que compara os elementos no topo da stack
 *
 * @param stk : stack
 */
int igual(STACK *stk)
{
    int r = areNumbers(stk);

    DADOS P, Z;

    if (r != 1) {
        if (tipoTop(stk) == 16) {
            P = POP(stk);
            Z = POP(stk);
            int result = strcmp(P.data.vs, Z.data.vs);
            if (result == 0) PUSHL(stk, 1);
            else PUSHL(stk, 0);
            r = 1;
        } else if (tipoTop(stk) == 9) {
            P.data.vl = POPL(stk);
            DADOS Z = POP(stk);
            PUSHC(stk, Z.data.vs[P.data.vl]);
            r = 1;
        }
    }
    else
    {
        P.data.vd = POPD(stk);
        Z.data.vd = POPD(stk);
        if ((Z.data.vd) == (P.data.vd))
            PUSHL(stk, 1);
        else
            PUSHL(stk, 0);
        r = 1;
    }
    return r;
}


/**
 * \brief Esta é a função auxiliar que coloca na stack o contrário do seu valor lógico
 *
 * @param stk : stack
 */
int nao(STACK *stk)
{
    DADOS P = POP(stk);
    (P.tipo == LONG && P.data.vl!=0) ? PUSHL(stk, 0):
    (P.tipo == DOUBLE && P.data.vd!=0) ? PUSHL(stk, 0):
    (P.tipo == CHAR && P.data.vc!=0) ? PUSHL(stk, 0): PUSHL(stk, 1);

    return 1;
}

/**
 * \brief Esta é a função auxiliar que coloca na stack o menor de 2 valores
 *
 * @param stk : stack
 */
int menorDe2(STACK *stk)
{
    int r = 0;

    DADOS P, Z;
    P.tipo = stk->comp[stk->count - 1].tipo;
    Z.tipo = stk->comp[stk->count - 2].tipo;


    if (P.tipo == LONG && Z.tipo == LONG)
    {
        r = 1;
        P = POP(stk);
        Z = POP(stk);
        if ((P.data.vl)<(Z.data.vl)) PUSH(stk, P);
        else PUSH(stk, Z);
    }
    if (P.tipo == LONG && Z.tipo == DOUBLE)
    {
        r = 1;
        P = POP(stk);
        Z = POP(stk);
        if ((P.data.vl)<(Z.data.vd)) PUSH(stk, P);
        else PUSH(stk, Z);
    }
    if (P.tipo == DOUBLE && Z.tipo == LONG)
    {
        r = 1;
        P = POP(stk);
        Z = POP(stk);
        if ((P.data.vd)<(Z.data.vl)) PUSH(stk, P);
        else PUSH(stk, Z);
    }
    if (P.tipo == DOUBLE && Z.tipo == DOUBLE)
    {
        r = 1;
        P = POP(stk);
        Z = POP(stk);
        if ((P.data.vd)<(Z.data.vd)) PUSH(stk, P);
        else PUSH(stk, Z);
    }
    if (P.tipo == STRING && Z.tipo == STRING)
    {
        P = POP(stk);
        Z = POP(stk);
        if(strcmp(Z.data.vs, P.data.vs) < 0) PUSH(stk, Z);
        else PUSH(stk, P);
        r=1;

    }
    return r;
}

/**
 * \brief Esta é a função auxiliar que coloca na stack o maior de 2 valores
 *
 * @param stk : stack
 */
int maiorDe2(STACK *stk)
{
    int r = 0;

    DADOS P, Z;
    P.tipo = stk->comp[stk->count - 1].tipo;
    Z.tipo = stk->comp[stk->count - 2].tipo;


    if (P.tipo == LONG && Z.tipo == LONG)
    {
        r = 1;
        P = POP(stk);
        Z = POP(stk);
        if ((P.data.vl)>(Z.data.vl)) PUSH(stk, P);
        else PUSH(stk, Z);
    }
    if (P.tipo == LONG && Z.tipo == DOUBLE)
    {
        r = 1;
        P = POP(stk);
        Z = POP(stk);
        if ((P.data.vl)>(Z.data.vd)) PUSH(stk, P);
        else PUSH(stk, Z);
    }
    if (P.tipo == DOUBLE && Z.tipo == LONG)
    {
        r = 1;
        P = POP(stk);
        Z = POP(stk);
        if ((P.data.vd)>(Z.data.vl)) PUSH(stk, P);
        else PUSH(stk, Z);
    }
    if (P.tipo == DOUBLE && Z.tipo == DOUBLE)
    {
        r = 1;
        P = POP(stk);
        Z = POP(stk);
        if ((P.data.vd)>(Z.data.vd)) PUSH(stk, P);
        else PUSH(stk, Z);
    }
    if (P.tipo == STRING && Z.tipo == STRING)
    {
        r=1;
        P = POP(stk);
        Z = POP(stk);
        if(strcmp(Z.data.vs, P.data.vs) < 0) PUSH(stk, P);
        else PUSH(stk, Z);


    }
    return r;
}
/**
 * \brief Esta é a função auxiliar que verifica a condição if-then-else de 3 elementos da stack
 *
 * @param stk : stack
 */
int ifThenElse(STACK *stk)
{
    DADOS P = POP(stk);
    DADOS Z = POP(stk);
    DADOS T = POP(stk);

    if (T.tipo == LONG && T.data.vl == 0) PUSH(stk, P);
    else if (T.tipo == DOUBLE && T.data.vd == 0) PUSH(stk, P);
    else if (T.tipo == CHAR && T.data.vc == '\0') PUSH(stk, P);
    else if (T.tipo == STRING && strlen(T.data.vs) == 0) PUSH(stk, P);
    else if (T.tipo == ARRAY)
    {
        STACK *array = T.data.va;
        int x = array->count;
        if (x == 0) PUSH(stk, P); else PUSH(stk, Z);
    }
    else PUSH(stk, Z);

    return 1;
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
 * @param stk : stack
 */
void variableOut (STACK *arrayList[], char *t, DADOS variaveis[26], int *flag)
{
    char k;
    k = t[0];
    DADOS P;
    int i = k - 65;
    P = variaveis[i];
    PUSH(arrayList[*flag], P);
}

/**
 * \brief Esta é a função auxiliar que verifica o elemento do topo da stack e o guarda na variável pretendida
 *
 * @param t : string com o token
 * @param variaveis : variáveis passíveis de serem colocadas (alfabeto maiúsculo)
 * @param stk : stack
 */
void variableIn (STACK *arrayList[], char *t, DADOS variaveis[26], int *flag)
{
    char k;
    k = t[1];
    DADOS P = TOP(arrayList[*flag]);

    variaveis[k-65] = P;
}

int checkInt(STACK *stk)
{
    DADOS P = TOP(stk);
    long soma = 0;

    for (unsigned int i=0; i < strlen(P.data.vs); i++)
    {
        soma += P.data.vs[i];
    }
    return soma;
}

int stringSize(STACK *stk)
{
    int r = 0;

    DADOS P = TOP(stk);
    if (P.tipo == STRING)
    {
        P = POP(stk);
        unsigned long x = strlen(P.data.vs);
        PUSHL(stk, x);
        r = 1;
    }

    return r;
}

/*
int newLine(STACK *stk)
{
    int r;
    DADOS P = POP(stk);
    int x = strlen(P.data.vs);
    char *s = malloc(x*sizeof(char));

    for ( int i=0; i < x-1; i++)
    {
        if (P.data.vs[i] == ' ' || P.data.vs[i] == '\0')  s[i] = '\n';
        else s[i] = P.data.vs[i];
    }

    PUSHS(stk, s);
    r=1;

    return r;
}*/

/*
int spaces (STACK *stk)
{

}*/
