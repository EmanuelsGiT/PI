/**
 * @file Ficheiro que contém a função que determina o que
 * estará no final do calculo na stack
 */

int IsNumber(char n[], int a, int top, double stack[], int numchar[], int *letrasl);
int eLetra(char c1, char c2, double arrayAZ[][20], double numAZ[], int ncArrAZ[][20], int indAZ[], int top, int topS, double stack[], int numchar[], char stackAux[][10240]);
void calcular(char n[], char nSeguro[]);