/**
 * @file parser.h Ficheiro que contém as funções referentes ao parser.
 */
#include <stdlib.h>

/**
 * @brief Tipo Enum que enumera os tipos de variáveis possíveis
 */
typedef enum {
    LONG = 1,      /**< Define o tipo LONG */
    DOUBLE = 2,    /**< Define o tipo DOUBLE */
    CHAR = 4,      /**< Define o tipo CHAR */
    STRING = 8,    /**< Define o tipo STRING */
    ARRAY = 16,
    BLOCO = 32,
} TIPO;

/**
 * @brief Estrutura de Dados que define o tipo DADOS
 */
typedef struct {
    TIPO    tipo; /**< Define o tipo da estrutura de dados (2 para long, 4 para double, 8 para char e 16 para strings) */
    union {
        long   vl;   /**< Contém o valor da variável caso esta seja do tipo long */
        double vd;   /**< Contém o valor da variável caso esta seja do tipo double */
        char   vc;   /**< Contém o valor da variável caso esta seja do tipo char */
        char  *vs;   /**< Contém o valor da variável caso esta seja do tipo string */
        struct stack *va; // Isto é o array
        struct stack *vb; // Isto é o bloco
    } data;
} DADOS;

/**
 * @brief Estrutura de Dados que define a Stack
 */
typedef struct stack{
    DADOS *comp;   /**< Define a stack e o seu tamanho */
    int count;     /**< Variável que conta o número de elementos da stack */
    int size;     //falta documentar
}STACK, *ptrStack;

void parser(char *line);
void parserArray(char *t, STACK *arrayList[], int *flag, int *bloco, STACK *endBloco);
int parserOperations(char *t, STACK *stk);
void arrayOperations(char *t, STACK *arrayList[], int *flag);
void decideOperations(char *t, STACK *arrayList[], int *flag, int *bloco, STACK *endBloco);
void criarString(char *t, STACK *arrayList[], int *flag);
void iniciarStack(STACK *stk);
void realocarM (STACK *stk);
void print_DADOS (DADOS d);
void PRINT_STACK(STACK *stk);
void PRINT_BLOCO(STACK *stk);
long POPL(STACK *stk);
double POPD(STACK *stk);
char POPC(STACK *stk);
char *POPS(STACK *stk);
DADOS POP(STACK *stk);
DADOS TOP(STACK *stk);
void PUSHL(STACK *stk, long x);
void PUSHD(STACK *stk, double x);
void PUSHC(STACK *stk, char x);
void PUSHS(STACK *stk, char *x);
void PUSHA(STACK *stk, STACK *x);
void PUSHB(STACK *stk, STACK *x);
void PUSH(STACK *stk, DADOS P);
int tipoTop(STACK *stk);
int areNumbers(STACK *stk);
int soma(STACK *stk);
int subtracao(STACK *stk);
int multiplicacao(STACK *stk);
int divisao(STACK *stk);
int incrementar(STACK *stk);
int decrementar(STACK *stk);
int restoDivInt(STACK *stk);
int exponenciacao(STACK *stk);
int and(STACK *stk);
int or(STACK *stk);
int xor(STACK *stk);
int not(STACK *stk);
int conjuncao(STACK *stk);
int disjuncao(STACK *stk);
int duplicar(STACK *stk);
int lastOut(STACK *stk);
int switchTwo(STACK *stk);
int rotateThree(STACK *stk);
int copyN(STACK *stk);
int convInteiro(STACK *stk);
int convDouble(STACK *stk);
int convCaracter(STACK *stk);
//int convString(STACK *stk);
int lerLinha(STACK *stk);
int lerTudo(STACK *stk);
int igual(STACK *stk);
void range(STACK *arrayList[], int *flag);
int nao(STACK *stk);
int menorDe2(STACK *stk);
int maiorDe2(STACK *stk);
int ifThenElse(STACK *stk);
int variableTeste (char *t);
int twoPointsTeste (char *t);
void variableOut (STACK *arrayList[], char *t, DADOS variaveis[26], int *flag);
void variableIn (STACK *arrayList[], char *t, DADOS variaveis[26], int *flag);
int menor(STACK *stk);
int maior(STACK *stk);
int aritmeticas(char *t, STACK *stk);
int logicas(char *t, STACK *stk);
int opStack(char *t, STACK *stk);
int convertions(char *t, STACK *stk);
int comparison(char *t, STACK *stk);
void atribuicao(DADOS *variaveis);
void criarArray(STACK *arrayList[],  int *flag);
void criarBloco(STACK *arrayList[],  int *flag, STACK *endBloco);
void arrayToStack(STACK *stk, STACK *array);
void size(STACK *stk, STACK *array);
void indexArray(STACK *stk, STACK *array);
void replicate(STACK *arrayList[], int *flag);
void removeFirst(STACK *arrayList[], int *flag);
void removeLast(STACK *arrayList[], int *flag);
void firstElements(STACK *arrayList[], int *flag);
void lastElements(STACK *arrayList[], int *flag);
void concatenarArrays(STACK *arrayList[], int *flag);
void concatenaArrNum(STACK *arrayList[], int *flag);
void concatenaArrArr(STACK *arrayList[], int *flag);
int checkInt(STACK *stk);
int stringSize(STACK *stk);
void executaBloco(STACK *arrayList[], int *flag, int *bloco, STACK *endBloco);
void parserBloco(char *t, STACK *arrayList[], int *flag, int *bloco, STACK *endBloco);
//void aplicaBloco(STACK *arrayList[], int *flag, STACK *endBloco);
//int spaces(STACK *stk);
//int newLine(STACK *stk);

