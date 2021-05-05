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
STACK *novaStack() {
    return malloc(sizeof(STACK));
}

/**
 * \brief Esta é a função que vai fazer o parser de uma linha
 *
 * Esta função recebe uma string, faz o parser e redireciona para as devidas operações.
 *
 * @param line : A linha que foi lida e da qual se vai fazer o parser.
 */
void parser(char *line)
{
    int flag = 0;
    int bloco = 0;
    char *delims = " \t\n";

    DADOS variaveis [26];
    atribuicao(variaveis);

    STACK *stack = novaStack();
    iniciarStack(stack);
    STACK *endBloco = novaStack();
    STACK *chose;

    STACK *arrayList[100];
    arrayList[0] = stack;

    for (char *token = strtok(line, delims); token != NULL; token = strtok(NULL, delims))
    {
        char *sobra;
        long val_i = strtol(token, &sobra, 10);

        if(bloco == 1) chose = endBloco;
        else chose = arrayList[flag];

        if (strlen(sobra) == 0)
        {
            PUSHL(chose, val_i);
        }
        else
        {
            double val_d = strtod(token, &sobra);
            if (strlen(sobra) == 0)
            {
                PUSHD(chose, val_d);
            }
            else
            {
                ((chose->comp[chose->count-1].tipo == BLOCO)&&(strstr("+-*/()%#&|^~e&e|_;\\@$clifts<>=!?e<e>,", token)  != NULL)) ? parserBloco(token, arrayList, &flag, &bloco, endBloco):
                (strstr("[]{}", token)                                    != NULL) ? parserArray(token, arrayList, &flag, &bloco, endBloco):
                (strstr("+-*/()%#&|^~e&e|_;\\@$clifts<>=!?e<e>,", token)  != NULL) ? decideOperations(token, arrayList, &flag, &bloco, endBloco):
                (strchr(token,34)                                        != NULL)  ? criarString(token, arrayList, &flag):
                (variableTeste(token)                                    ==0)      ? variableOut(arrayList, token, variaveis, &flag):
                (twoPointsTeste(token)                                   ==0)      ? variableIn (arrayList, token, variaveis, &flag):
                exit(0);
            }
        }
    }

    PRINT_STACK(stack);
    putchar('\n');
}

//falta documentar
void parserArray(char *t, STACK *arrayList[], int *flag, int *bloco, STACK *endBloco)
{
    if (strstr("[",t) != NULL) criarArray(arrayList, flag);
    if (strstr("]",t) != NULL) (*flag)--;
    if (strstr("{",t) != NULL) {criarBloco(arrayList, flag, endBloco); (*bloco) = 1;}
    if (strstr("}",t) != NULL) {(*bloco) = 0;}
}


void parserBloco(char *t, STACK *arrayList[], int *flag, int *bloco, STACK *endBloco)
{
    if (strstr("~",t) != NULL) executaBloco(arrayList, flag, bloco, endBloco);
    //if (strstr("%",t) != NULL) aplicaBloco(arrayList, flag, endBloco);
}

/**
 * \brief Esta é a função auxiliar ao parser que redireciona para as respetivas operações da stack
 *
 * @param token : sinal respetivo a cada operação
 */
int parserOperations(char *t, STACK *stk)
{
    int r = 0;

    if (strstr("+-*/()%#" ,t)   != NULL) (r = aritmeticas(t,stk));
    if (strstr("&|^~e&e|" ,t)   != NULL) (r = logicas    (t,stk));
    if (strstr("_;\\@$,N/S/"  ,t) != NULL) (r = opStack    (t,stk));
    if (strstr("clifst"    ,t)   != NULL) (r = convertions(t,stk));
    if (strstr("<>=!?e<e>",t)   != NULL) (r = comparison (t,stk));



    return r;
}

//falta documentar
void arrayOperations(char *t, STACK *arrayList[], int *flag)
{
    if (strcmp(t,"~") == 0) arrayToStack(arrayList[*flag], arrayList[*flag+1]);
    if (strcmp(t,"=") == 0) indexArray(arrayList[*flag], arrayList[*flag+1]);
    if (strcmp(t,",") ==0) range(arrayList, flag);
    if (strcmp(t,"*") ==0) replicate(arrayList, flag);
    if (strcmp(t,"(") ==0) removeFirst(arrayList, flag);
    if (strcmp(t,")") ==0) removeLast(arrayList, flag);
    if (strcmp(t,"<") ==0) firstElements(arrayList, flag);
    if (strcmp(t,">") ==0) lastElements(arrayList, flag);
    if (strcmp(t,"+") ==0) concatenarArrays(arrayList, flag);
}

//falta documentar
void decideOperations(char *t, STACK *arrayList[], int *flag, int *bloco, STACK *endBloco)
{
    if (*bloco == 1) PUSHS(endBloco, t);
    else
    {
        int r = parserOperations(t,arrayList[*flag]);
        if (r==0) arrayOperations(t,arrayList, flag);
    }
}

void criarString(char *t, STACK *arrayList[], int *flag)
{
    for (unsigned int i = 0; i < strlen(t)-2; i++)
    {
        if (t[i] == '.') t[i] = ' ';
    }

    for (unsigned int i = 0; i < strlen(t)-1; i++)
    {
        t[i] = t[i+1];
    }

    for (int i=0; i<2; i++)
    {
        t[strlen(t)-1]='\0';
    }

    int x = strlen(t);
    char *p = malloc((x+1) * sizeof(char));
    strcpy(p,t);
    PUSHS(arrayList[*flag], p);
}


/**
 * \brief Esta é a função que atribui os valores por omissão às diferentes variáveis
 *
 * @param variaveis : o array que irá conter as variáveis do alfabeto maiúsculo introduzido
 */
void atribuicao (DADOS *variaveis)
{
    int i=10;
    for (char a='A'; a<='F'; a++, i++)
    {
        variaveis[a-65].tipo=1;
        variaveis[a-65].data.vl=i;
    }
    for (char a='X', i=0; a<='Z'; a++, i++)
    {
        variaveis[a-65].tipo=1;
        variaveis[a-65].data.vl=i;
    }
    variaveis['S'-65].tipo=4;
    variaveis['S'-65].data.vc=' ';
    variaveis['N'-65].tipo=4;
    variaveis['N'-65].data.vc='\n';
}

/**
 * \brief Esta é a função auxiliar da PRINT_STACK que imprime um elemento dos diferentes tipos de dados
 *
 * @param d : É o elemento a ser imprimido
 */
void print_DADOS (DADOS d)
{
    switch (d.tipo)
    {
        case LONG : printf("%ld", d.data.vl); break;
        case DOUBLE : printf("%g", d.data.vd); break;
        case CHAR : printf("%c", d.data.vc); break;
        case STRING : printf("%s", d.data.vs); break;
        case ARRAY : PRINT_STACK(d.data.va); break;
        case BLOCO : PRINT_BLOCO(d.data.vb); break;
    }
}

/**
 * \brief Esta é a função auxiliar da parser que imprime a stack
 *
 * @param stk: stack
 */
void PRINT_STACK(STACK *stk)
{
    int i;
    for (i = 0; i < stk->count; i++) {
        print_DADOS (stk->comp[i]);
    }

    //printf("\n\nCOUNT : %d\n", stk->count);
    //printf ("SIZE : %d\n", stk->size);
}

void PRINT_BLOCO(STACK *stk)
{
    int i;

    printf("{ ");
    for (i = 0; i < stk->count; i++) {
        print_DADOS (stk->comp[i]);
        putchar(' ');
    }
    printf("}");

    //printf("\n\nCOUNTB : %d\n", stk->count);
    //printf ("SIZEB : %d\n", stk->size);
}

/**
 * \brief Esta é a função auxiliar que retira o último elemento do tipo long da stack
 *
 * @param stk: stack
 *
 * @returns O último elemento da stack
 */
long POPL(STACK *stk)
{
    long x;
    x = stk->comp[stk->count -1].data.vl;
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
double POPD(STACK *stk)
{
    double x;
    if (stk->comp[stk->count-1].tipo == 1) x = stk->comp[stk->count -1].data.vl;
    else x = stk->comp[stk->count -1].data.vd;
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
char POPC(STACK *stk)
{
    char x;
    x = stk->comp[stk->count -1].data.vc;
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
    char *x = stk->comp[stk->count-1].data.vs;
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

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo long na stack
 *
 * @param x : É o elemento que queremos colocar na stack
 * @param stk: stack
 */
void PUSHL(STACK *stk, long x)
{
    if (stk->count == stk->size) realocarM(stk);

    stk->comp[stk->count].tipo = 1;
    stk->comp[stk->count].data.vl = x;
    stk->count++;
}

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo double na stack
 *
 * @param x : É o elemento que queremos colocar na stack
 * @param stk: stack
 */
void PUSHD(STACK *stk, double x)
{
    if (stk->count == stk->size) realocarM(stk);

    stk->comp[stk->count].tipo = 2;
    stk->comp[stk->count].data.vd = x;
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
    if (stk->count == stk->size) realocarM(stk);

    stk->comp[stk->count].tipo = 4;
    stk->comp[stk->count].data.vc = x;
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
    if (stk->count == stk->size) realocarM(stk);

    stk->comp[stk->count].tipo = 8;
    stk->comp[stk->count].data.vs = x;
    stk->count++;
}

//falta documentar
void PUSHA(STACK *stk, STACK *x)
{
    if (stk->count == stk->size) realocarM(stk);

    stk->comp[stk->count].tipo = 16;
    stk->comp[stk->count].data.va = x;
    stk->count++;
}

void PUSHB (STACK *stk, STACK *x)
{
    if (stk->count == stk->size) realocarM(stk);

    stk->comp[stk->count].tipo = 32;
    stk->comp[stk->count].data.vb = x;
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
    if (stk->count == stk->size) realocarM(stk);

    stk->comp[stk->count] = P;
    stk->count++;
}


/**
 * \brief Esta é a função auxiliar que verifica os tipos dos dois últimos elementos no topo da stack
 *
 * @param stk: stack
 *
 * @returns O valor da soma dos tipos dos dois elementos
 */
int tipoTop(STACK *stk)
{
    TIPO x = stk->comp[stk->count - 1].tipo;
    TIPO y = stk->comp[stk->count - 2].tipo;
    return (x+y);
}

//falta documentar
int areNumbers(STACK *stk)
{
    int r = 0;

    TIPO x = stk->comp[stk->count - 1].tipo;
    TIPO y = stk->comp[stk->count - 2].tipo;

    if((x == LONG || x == DOUBLE || x == CHAR ) && (y == LONG || y == DOUBLE || y == CHAR)) r = 1;

    return r;
}

//falta documentar
void criarArray(STACK *arrayList[],  int *flag)
{
    STACK *array = novaStack();
    iniciarStack(array);
    PUSHA(arrayList[*flag], array);
    (*flag)++;
    arrayList[*flag] = array;
}

void criarBloco(STACK *arrayList[], int *flag, STACK *endBloco)
{
    iniciarStack(endBloco);
    PUSHB(arrayList[*flag], endBloco);
}

//falta documentar
void iniciarStack(STACK *stk)
{
    stk->count = 0;
    stk->size  = 5;
    stk->comp = malloc (stk->size * sizeof(DADOS));
}

//falta documentar
void realocarM (STACK *stk)
{
    DADOS *t = realloc (stk->comp, 2*stk->size*sizeof(DADOS));

    stk->comp = t;
    stk->size*=2;
}
