/**
 * @file Ficheiro que contém as funções que definem a stack
 */

void auxPrint(int ii, int numchar[], char stackAux[][10240], double stack[]) ;
void printStack(int *top, int numchar[], char stackAux[][10240], double stack[]); 
void push(double num, int *top, double stack[]);
void pushs(int *top, int *topS, double stack[], char stackAux[][10240], int numchar[], char aux[]);
double pop(int *top, double stack[]);
int popR (int *top,int *end, int numchar[]);
