#include <stdlib.h>

/**
 * @file parser.h Ficheiro que contém as funções referentes ao parser.
 */

/**
 * @brief Estrutura de Dados que define o tipo DADOS
 */
typedef struct {
    int    tipo; /**< Define o tipo da estrutura de dados (1 para long, 2 para double, 3 para char e 4 para strings) */
    long   vl;   /**< Contém o valor da variável caso esta seja do tipo long */
    double vd;   /**< Contém o valor da variável caso esta seja do tipo double */
    char   vc;   /**< Contém o valor da variável caso esta seja do tipo char */
    char  *vs;   /**< Contém o valor da variável caso esta seja do tipo string */
} DADOS;

/**
 * @brief Estrutura de Dados que define a Stack
 */
typedef struct{
    DADOS comp[10240]; /**< Define a stack e o seu tamanho */
    int count;         /**< Variável que conta o número de elementos da stack */
}STACK;

void parse (char *line);
void doNothing();
void print_DADOS (DADOS d);
void PRINT_STACK(STACK *stk);
long POPL();
double POPD();
char POPC();
char *POPS();
DADOS POP();
void PUSHL(STACK *stk, long x);
void PUSHD(STACK *stk, double x);
void PUSHC(STACK *stk, char x);
void PUSHS(STACK *stk, char *x);
void PUSH(STACK *stk, DADOS P);
DADOS longTOdados (long x);
DADOS doubleTOdados (double x);
DADOS charTOdados (char x);
long dadosTOlong (DADOS P);
double dadosTOdouble (DADOS P);
void soma();
void subtracao();
void multiplicacao();
void divisao();
void incrementar();
void decrementar();
void restoDivInt();
void exponenciacao();
void and();
void or();
void xor();
void not();
void duplicar();
void lastOut();
void switchTwo();
void rotateThree();
void copyN();
void convInteiro();
void convDouble();
void convCaracter();
void convString();
void lerLinha();
void igual();
void menor();
void maior();
void nao();
void conjuncao();
void disjuncao();
void menorDe2();
void maiorDe2();
void ifThenElse();
int variableTeste (char *t);
int twoPointsTeste (char *t);
void variableOut (STACK *stk, char *t, DADOS variaveis[26]);
void variableIn (STACK *stk, char *t, DADOS variaveis[26]);
