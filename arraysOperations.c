/**
 * @file arraysOperations.c Ficheiro que contém as funções referentes às operações na stack do parser
 */
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

//falta documentar
void arrayToStack(STACK *stk, STACK *array)
{
    int i;
    int x = array->count;

    DADOS P[x];

    x = sizeof(P)/sizeof(P[0]);

    for (i = 0; i < x; i++)
    {
        P[i] = POP(array);
    }

    stk->count--;

    for (i = 0; i < x; i++)
    {
        PUSH(stk, P[x-i-1]);
    }
}

void size(STACK *stk, STACK *array){
    POP(stk);
    PUSHL(stk, array->count);
}

void indexArray(STACK *stk, STACK *array)
{
    DADOS Z = POP(stk);
    int i;
    DADOS P;

    for (i=array->count; i > Z.data.vl; i--)
    {
        P = POP(array);
    }

    POP(stk);
    PUSH(stk, P);
}

//falta documentar
void range (STACK *arrayList[], int *flag)
{
    DADOS P = POP(arrayList[*flag]);

    if (P.tipo == LONG)
    {
        criarArray(arrayList, flag);

        for (long i=0; i < P.data.vl; i++)
        {
            PUSHL(arrayList[*flag], i);
        }
        (*flag)--;
    }
    else
    {
        PUSHL(arrayList[*flag], arrayList[*flag+1]->count);
    }
}


//falta documentar
void replicate (STACK *arrayList[], int *flag)
{
    DADOS P = POP(arrayList[*flag]);
    STACK *array = arrayList[*flag+1];
    int x = array->count;
    int i;

    for (i=0; i < (P.data.vl-1)*x; i++)
    {
        PUSH(array, array->comp[i]);
    }
}

//falta documentar
void removeFirst (STACK *arrayList[], int *flag)
{
    STACK *array = arrayList[*flag+1];
    DADOS P = array->comp[0];
    int x = array->count;

    for (int i=0; i < x; i++)
    {
        array->comp[i] = array->comp[i+1];
    }

    array->count--;
    PUSHA(arrayList[0], array);
    PUSH(arrayList[0], P);
}

void removeLast (STACK *arrayList[], int *flag)
{
    STACK *array = arrayList[*flag+1];
    DADOS P = POP(array);


    PUSHA(arrayList[0], array);
    PUSH(arrayList[0], P);
}

void firstElements(STACK *arrayList[], int *flag)
{
    DADOS P = POP(arrayList[*flag]);
    STACK *array = arrayList[*flag+1];

    unsigned int i;

    for (i = array->count; i > P.data.vl ; i--)
    {
       POP(array);
    }
}

void lastElements(STACK *arrayList[], int *flag)
{
    DADOS P = POP(arrayList[*flag]);
    STACK *array = arrayList[*flag+1];
    int x = array->count;
    int i;

    for (i=0; i < P.data.vl; i++)
    {
        array->comp[i] = array->comp[x-P.data.vl+i];
    }

    for (i=0; i < x-P.data.vl; i++)
    {
        POP(array);
    }
}

void concatenarArrays(STACK *arrayList[], int *flag)
{
    DADOS P = TOP(arrayList[*flag]);
    if (P.tipo == ARRAY) concatenaArrArr(arrayList, flag);
    else concatenaArrNum(arrayList, flag);

}

void concatenaArrNum(STACK *arrayList[], int *flag)
{
    DADOS P = POP(arrayList[*flag]);
    PUSH(arrayList[*flag+1], P);
}

void concatenaArrArr(STACK *arrayList[], int *flag)
{
    int x = tipoTop(arrayList[*flag]);
    DADOS P = POP(arrayList[*flag]);
    DADOS Z = POP(arrayList[*flag]);
    STACK *arrayP = P.data.va;
    if (x==17 || x == 18)
    {
        criarArray(arrayList, flag);
        (*flag)--;
        PUSH(arrayList[*flag+1], Z);

        for (int i=0; i<arrayP->count; i++)
        {
            PUSH(arrayList[*flag+1], arrayP->comp[i]);
        }
    }
    else
    {
        criarArray(arrayList, flag);
        (*flag)--;
        STACK *arrayZ = Z.data.va;
        for (int i=0; i < arrayZ->count; i++)
        {
            PUSH(arrayList[*flag+1], arrayZ->comp[i]);
        }
        for (int i=0; i<arrayP->count; i++)
        {
            PUSH(arrayList[*flag+1], arrayP->comp[i]);
        }
    }

}

void executaBloco(STACK *arrayList[], int *flag, int *bloco, STACK *endBloco)
{
    int x = endBloco->count;

    DADOS block = POP(arrayList[*flag]);
    STACK *bl = block.data.vb;

    for (int i = 0; i < x; i++)
    {

        if (bl->comp[i].tipo == LONG) PUSH(arrayList[*flag], bl->comp[i]);
        else {
            DADOS P = bl->comp[i];
            decideOperations(P.data.vs, arrayList, flag, bloco, endBloco);
        }
    }
}

/*
void aplicaBloco(STACK *arrayList[], int *flag, STACK *endBloco)
{
    int x = endBloco->count;
    int k;

    DADOS block = POP(arrayList[*flag]);
    STACK *bl = block.data.vb;
    DADOS n;

    DADOS array = POP(arrayList[*flag]);
    STACK *arr = array.data.va;
    k = arr->count;

    for (int i = 0; i < x; i++){
        if (bl->comp[i].tipo == LONG) {
            n = bl->comp[i];
        }
        else {
            //  criarArray(arrayList, flag);
            for (int j = 0; j < k; j++) {
                PUSH(arrayList[*flag], arr->comp[j]);
                PUSH(arrayList[*flag], n);
                PUSH(arrayList[*flag], bl->comp[i]);
                char *t = POPS(arrayList[*flag]);
                parserOperations(t, arrayList[*flag]);
            }

            DADOS P[k];

            for (long m=0; i < k; i++)
            {
                P[m] = POP(arrayList[*flag]);
            }

            //PUSH(arrayList[*flag], P[k]);
            }
    }
}
 */

