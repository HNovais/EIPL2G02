/**
 * @file parser.h Ficheiro que contém as funções referentes ao parser.
 */

/**
 * @brief Estrutura de Dados que define o tipo DADOS
 * @var tipo Define o tipo da estrutura de dados (1 para long, 2 para double, 3 para char e 4 para strings)
 * @var vl Contém o valor da variável caso esta seja do tipo long
 * @var vd Contém o valor da variável caso esta seja do tipo double
 * @var vc Contém o valor da variável caso esta seja do tipo char
 * @var *vs Contém o valor da variável caso esta seja do tipo string
 */
typedef struct {
    int tipo;
    long vl;
    double vd;
    char vc;
    char *vs;
} DADOS;

void parse (char *line);
void print_DADOS (DADOS d);
void PRINT_STACK(int x);
long POPL();
double POPD();
char POPC();
char *POPS();
DADOS POP();
void PUSHL(long x);
void PUSHD(double x);
void PUSHC(char x);
void PUSHS(char *x);
void PUSH(DADOS P);
DADOS longTOdados (long x);
DADOS doubleTOdados (double x);
DADOS charTOdados (char x);
long dadosTOlong (DADOS P);
double dadosTOdouble (DADOS P);
