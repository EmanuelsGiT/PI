/**
 *  @file Ficheiro que contém as funções que definem a stack
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "funcoesMat.h"
#include "calculosG1.h"
#include "stack.h"


/**
 * \brief Esta função auxilia a função que imprime a stack
 *
 * Teve de ser criada por causa da recursividade da função calcular
 *
 * @param ii Valor da posição da stack que é para imprimir
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 * @param stack[] Stack recebida
 */
void auxPrint(int ii, int numchar[], char stackAux[][10240], double stack[]) 
{
    int j,l,ri;
    double r;

    if(numchar[ii]==3 || numchar[ii]==2)
    {
        r=stack[ii];
        if((r>1000000||r<-1000000)&&numchar[ii]==2) 
        {
            ri=(int)r;
            printf("%d",ri);
        }
        else printf("%g", r);
    }
    else if (numchar[ii]==4 || numchar[ii]==5 || numchar[ii]==6) 
    {
        //ignora
    }
    else if(numchar[ii]==7)
        printf("{");
    else if(numchar[ii]==8)
        printf("}");
    else 
    {   
        ri = (int)stack[ii];
        l=strlen(stackAux[ri]);
        for(j=0;stackAux[ri][j];j++)
            printf("%c", stackAux[ri][j]);
        if(stackAux[ri][l-2]=='*') printf("%c",'}');
    }   
    //printf(".");      
    
}


/**
 * \brief Esta função imprime a stack
 * 
 * @param *top Top da Stack
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 * @param stack[] Stack recebida
 */

void printStack(int *top, int numchar[], char stackAux[][10240], double stack[]) 
{
    int i=0, ri;

    for(ri=0;ri<=*top;ri++)
    {
        if(numchar[ri]==-1) i=ri+1;
    }


    for ( ; i<=*top; i++)
    {
        auxPrint(i,numchar,stackAux,stack);
    }
    printf("\n");
}

/**
 * \brief Esta função acrescenta um número à stack e aumenta a variável *top
 *
 * @param num Número que será acrescentado à stack
 * @param *top Top da Stack
 * @param stack[] Stack recebida
 *
 */

void push(double num, int *top, double stack[])
{ 
	if(*top!=500-1)
	{
		*top=*top+1;
		stack[*top]=num;
	}
}


/**
 * \brief Esta função acrescenta uma string à stack e aumenta a variável *top
 *
 * A string é acrescentada à stack utilizando uma stackAux onde estará a string em si,
 * sendo colocado na stack o indice da posição da string na stackAux
 *
 * @param *top Top da Stack
 * @param *top Top da Stack de strings
 * @param stack[] Stack recebida
 * @param stackAux[][] Stack de strings recebida
 * @param numchar[] Array numchar recebido
 * @param aux[] Array que será acresentado à stack
 *
 */

void pushs(int *top, int *topS, double stack[], char stackAux[][10240], int numchar[], char aux[])
{
    if(*topS!=499 && *top!=499)
    {
        int i;
        
        *top=*top+1;
        *topS=*topS+1;

        // copia se a string no array para uma posição k da stackAux
        for (i = 0; aux[i]; i++)
        {
            stackAux[*topS][i]=aux[i];
        }
        stackAux[*topS][i]='\0';

        //apaga a aux
        aux[0]='\0'; 

        // coloca se na stack o valor do indice da posição
        stack[*top]=*topS;

        //ativa-se o alarme que o numero na stack principal é uma posição
        numchar[*top]=1;
        
    }
}


/**
 * \brief Esta função retira um número da stack e diminui a variável *top
 *
 * @param *top Top da Stack
 * @param stack[] Stack recebida
 */
 
double pop(int *top, double stack[])
{   
    double r;
    r = stack[*top];

	if(*top>=0)
	{
        *top=*top-1;
	}
    return r;
} 


/**
 * \brief Esta função retira um array da stack, diminui a variável *top e indica aonde o array termina
 *
 * @param *top Top da Stack
 * @param *end Fim do array na stack
 * @param numchar[] Array numchar recebido
 */
int popR (int *top,int *end, int numchar[]){
    int i = *top,c=0;
    *end=*top-1;
    
    while (numchar[i]!=4 && i>=0 )
    {
        i--;
        c++;
    }
	if(*top>=0)
	{
        *top=*top-c;
	}
    return i+1;
}