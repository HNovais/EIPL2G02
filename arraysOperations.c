/**
 * @file arraysOperations.c Ficheiro que contém as funções referentes às operações na stack do parser
 */
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>


/**
 * \brief Esta é a função auxiliar da arrayOperations que redireciona para as operações nos Arrays
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
*/
void aritArrayOperations (char *token, STACK *stackPointer[], int *flag)
{
    if (strcmp(token,"~") == 0) arrayToStack    (stackPointer[*flag], stackPointer[*flag+1]);
    if (strcmp(token,"=") == 0) indexArray      (stackPointer[*flag], stackPointer[*flag+1]);
    if (strcmp(token,",") == 0) range           (stackPointer, flag);
    if (strcmp(token,"*") == 0) replicate       (stackPointer, flag);
}

/**
 * \brief Esta é a função auxiliar da arrayOperations que redireciona para operações com os elementos do Array
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
*/
void elemArrayOperations (char *token, STACK *stackPointer[], int *flag)
{
    if (strcmp(token,"(") == 0) removeFirst     (stackPointer, flag);
    if (strcmp(token,")") == 0) removeLast      (stackPointer, flag);
    if (strcmp(token,"<") == 0) firstElements   (stackPointer, flag);
    if (strcmp(token,">") == 0) lastElements    (stackPointer, flag);
}


/**
 * \brief Esta é a função auxiliar da aritArrayOperations que coloca na stack todos os elementos do array
 *
 * @param stack : stack
 * @param array : local onde está o array
 */
void arrayToStack(STACK *stack, STACK *array)
{
    int i;
    int x = array->count;

    DADOS P[x];

    x = sizeof(P)/sizeof(P[0]);

    for (i = 0; i < x; i++)
    {
        P[i] = POP(array);
    }

    stack->count--;

    for (i = 0; i < x; i++)
    {
        PUSH(stack, P[x-i-1]);
    }
}

/**
 * \brief Esta é a função auxiliar da aritArrayOperations que dá o tamanho do array
 *
 * @param stack : stack
 * @param array : local onde está o array
 */
void size(STACK *stack, STACK *array)
{
    POP(stack);
    PUSHL(stack, array->count);
}

/**
 * \brief Esta é a função auxiliar da aritArrayOperations que vai buscar o valor por índice
 *
 * @param stack : stack
 * @param array : local onde está o array
 */
void indexArray(STACK *stack, STACK *array)
{
    DADOS Z = POP(stack);
    int i;
    DADOS P;

    for (i=array->count; i > Z.data.vl; i--)
    {
        P = POP(array);
    }

    POP(stack);
    PUSH(stack, P);
}

/**
 * \brief Esta é a função auxiliar da aritArrayOperations que cria um array com x número de elementos
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void range (STACK *stackPointer[], int *flag)
{
    DADOS P = POP(stackPointer[*flag]);

    if (P.tipo == LONG)
    {
        criarArray(stackPointer, flag);

        for (long i=0; i < P.data.vl; i++)
        {
            PUSHL(stackPointer[*flag], i);
        }
        (*flag)--;
    }
    else
    {
        PUSHL(stackPointer[*flag], stackPointer[*flag+1]->count);
    }
}

/**
 * \brief Esta é a função auxiliar da aritArrayOperations que repete um array
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void replicate (STACK *stackPointer[], int *flag)
{
    DADOS P = POP(stackPointer[*flag]);
    STACK *array = stackPointer[*flag+1];
    int x = array->count;
    int i;

    for (i=0; i < (P.data.vl-1)*x; i++)
    {
        PUSH(array, array->comp[i]);
    }
}

/**
 * \brief Esta é a função auxiliar da elemArrayOperations que remove o primeiro elemento e o coloca na stack
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void removeFirst (STACK *stackPointer[], int *flag)
{
    STACK *array = stackPointer[*flag+1];
    DADOS P = array->comp[0];
    int x = array->count;

    for (int i=0; i < x; i++)
    {
        array->comp[i] = array->comp[i+1];
    }

    array->count--;
    PUSHA(stackPointer[0], array);
    PUSH(stackPointer[0], P);
}

/**
 * \brief Esta é a função auxiliar da elemArrayOperations que remove o último elemento e o coloca na stack
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void removeLast (STACK *stackPointer[], int *flag)
{
    STACK *array = stackPointer[*flag+1];
    DADOS P = POP(array);


    PUSHA(stackPointer[0], array);
    PUSH(stackPointer[0], P);
}

/**
 * \brief Esta é a função auxiliar da elemArrayOperations que vai buscar x valores do ínicio de um array
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void firstElements(STACK *stackPointer[], int *flag)
{
    DADOS P = POP(stackPointer[*flag]);
    STACK *array = stackPointer[*flag+1];

    unsigned int i;

    for (i = array->count; i > P.data.vl ; i--)
    {
       POP(array);
    }
}

/**
 * \brief Esta é a função auxiliar da elemArrayOperations que vai buscar x valores do fim de um array
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void lastElements(STACK *stackPointer[], int *flag)
{
    DADOS P = POP(stackPointer[*flag]);
    STACK *array = stackPointer[*flag+1];
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

/**
 * \brief Esta é a função auxiliar da aritArrayOperations que concatena arrays e/ou outros elementos
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void concatenarArrays(STACK *stackPointer[], int *flag)
{
    DADOS P = TOP(stackPointer[*flag]);

    if (P.tipo == ARRAY) concatenaResto(stackPointer, flag);
    else concatenaArrNum(stackPointer, flag);

}

/**
 * \brief Esta é a função auxiliar da concatenarArrays que concatena um array e um número
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void concatenaArrNum(STACK *stackPointer[], int *flag)
{
    DADOS P = POP(stackPointer[*flag]);

    PUSH(stackPointer[*flag+1], P);
}

/**
 * \brief Esta é a função auxiliar da concatenarArrays que concatena dois arrays ou um número e um array
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void concatenaResto(STACK *stackPointer[], int *flag)
{
    int x = somaTiposTop(stackPointer[*flag]);
    DADOS P = POP(stackPointer[*flag]);
    DADOS Z = POP(stackPointer[*flag]);
    STACK *arrayP = P.data.va;

    if (x == 17 || x == 18) concatenaNumArr(arrayP, stackPointer, flag, Z);
    else concatenaArrArr(arrayP, stackPointer, flag, Z);
}

void concatenaNumArr (STACK *array, STACK *stackPointer[], int *flag, DADOS P)
{
    criarArray(stackPointer, flag);
    (*flag)--;

    PUSH(stackPointer[*flag+1], P);

    for (int i=0; i<array->count; i++)
    {
        PUSH(stackPointer[*flag+1], array->comp[i]);
    }
}

void concatenaArrArr (STACK *array, STACK *stackPointer[], int *flag, DADOS P)
{
    criarArray(stackPointer, flag);
    (*flag)--;

    STACK *arrayP = P.data.va;

    for (int i=0; i < arrayP->count; i++)
    {
        PUSH(stackPointer[*flag+1], arrayP->comp[i]);
    }
    for (int i=0; i<array->count; i++)
    {
        PUSH(stackPointer[*flag+1], array->comp[i]);
    }
}

/**
 * \brief Esta é a função auxiliar da parserBloco que executa um bloco
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 * @param bloco : indicador de que possuímos um bloco (abertura de {)
 * @param addressBloco : stack onde vai ser guardado o bloco
 */
void executaBloco(STACK *stackPointer[], int *flag, int *bloco, STACK *addressBloco)
{
    int x = addressBloco->count;
    DADOS block = POP(stackPointer[*flag]);
    STACK *bl = block.data.vb;

    for (int i = 0; i < x; i++)
    {

        if (bl->comp[i].tipo == LONG) PUSH(stackPointer[*flag], bl->comp[i]);
        else {
            DADOS P = bl->comp[i];
            decideOperations(P.data.vs, stackPointer, flag, bloco, addressBloco);
        }
    }
}

/**
 * \brief Esta é a função auxiliar da parserBloco que aplica o bloco a todos os elementos de um array
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 * @param addressBloco : stack onde vai ser guardado o bloco
 */
void aplicaBloco(STACK *stackPointer[], int *flag, STACK *addressBloco)
{
    int x = addressBloco->count;
    int k;

    DADOS block = POP(stackPointer[*flag]);
    STACK *bl = block.data.vb;
    DADOS n;
    DADOS array = POP(stackPointer[*flag]);
    STACK *arr = array.data.va;

    k = arr->count;

    for (int i = 0; i < x; i++){
        if (bl->comp[i].tipo == LONG)
        {
            n = bl->comp[i];
        }
        else {
            criarArray(stackPointer, flag);
            for (int j = 0; j < k; j++)
            {
                PUSH(stackPointer[*flag], arr->comp[j]);
                PUSH(stackPointer[*flag], n);
                PUSH(stackPointer[*flag], bl->comp[i]);
                char *t = POPS(stackPointer[*flag]);
                parserOperations(t, stackPointer[*flag]);
            }
        }
    }
}

/**
 * \brief Esta é a função auxiliar da parserBloco que faz o fold sobre um array ou string usando o bloco
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 * @param bloco : indicador de que possuímos um bloco (abertura de {)
 * @param addressBloco : stack onde vai ser guardado o bloco
 */
void foldBloco(STACK *stackPointer[], int *flag)
{
    DADOS block = POP(stackPointer[*flag]);
    STACK *bl = block.data.vb;

    DADOS array = POP(stackPointer[*flag]);
    STACK *arr = array.data.va;
    int k = arr->count;

    for (int i = 0; i < k; i++){
        if (i == 0) {
            PUSH(stackPointer[*flag], arr->comp[i]);
            PUSH(stackPointer[*flag], arr->comp[i + 1]);
            PUSH(stackPointer[*flag], bl->comp[0]);
            char *t = POPS(stackPointer[*flag]);
            parserOperations(t, stackPointer[*flag]);
        } else {
            PUSH(stackPointer[*flag], arr->comp[i + 1]);
            PUSH(stackPointer[*flag], bl->comp[0]);
            char *t = POPS(stackPointer[*flag]);
            parserOperations(t, stackPointer[*flag]);
        }
    }
}

