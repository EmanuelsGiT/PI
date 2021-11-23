/**
 * @file Ficheiro com função de analisar a lista de digitos e operadores, colocá-los numa stack e chamar as devidas funções de cálculo.
 */

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "funcoesMat.h"
#include "stack.h"


/**
 * \brief Esta coloca os numeros na stack
 * 
 * @param n[] Array n recebido
 * @param a Posição no array n
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param *letrasl Apontador para o a
 */
int IsNumber(char n[], int a, int top, double stack[], int numchar[], int *letrasl)
{
    int mult=1, exp=0;
    double m=0;

    if(n[a]=='-' && isdigit(n[a+1]))
    {
        mult=-1;
        a++;
    }

    if (isdigit (n[a]))
    { 
        m=n[a]-48; 
        a++;
        while(isdigit(n[a])||n[a]=='.')
        {
            if(n[a]=='.')
                exp=1;
            else
            {
                m=m*10+(n[a]-48);
                exp=exp*10;
            }
            a++;  
        }
        if(exp==0) 
        {
            exp=1;
            numchar[top+1]=2; //o elemento é do tipo int
        }
        else
            numchar[top+1]=3; //o elemento é do tipo double
        push((m*mult)/exp, &top, stack);
        mult = 1;  
        exp  = 0;
    }

    *letrasl = a;

    return top;
}


/**
 * \brief Esta coloca os numeros na stack
 * 
 * @param c1 Corresponde a n[a]
 * @param c2 Corresponde a n[a+1]
 * @param arrayAZ[][] conterá os arrays associados às letras de A a Z
 * @param numAZ[] terá os valores associados às letras de A a Z
 * @param ncArrAZ[][] conterá os numchars associados às letras de A a Z
 * @param indAZ determina se o valor que está na numAZ é indice(1), int(2) ou double(3), array(4 e 6), string vazia(5), bloco(7 e 8)
 * @param top Top da Stack
 * @param topS Top da StackAux
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[] Stack de strings recebida
 */
int eLetra(char c1, char c2, double arrayAZ[][20], double numAZ[], int ncArrAZ[][20], int indAZ[], int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    int i,j;
    char aux[10240];
    char auxFin[10240];
    char auxCop[10240];
    char arrAZ[27]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if(c1>64 && c1<91 && c2!='/')
    {
        i=procura(c1,arrAZ,26);

        if(indAZ[i]==3)
        {
            push(numAZ[i], &top, stack);
            numchar[top]=indAZ[i];
        }

        else if(indAZ[i]==9)
        {
            for(j=0;ncArrAZ[i][j]!=6;j++)
            {
                push(arrayAZ[i][j], &top, stack);
                numchar[top]=ncArrAZ[i][j];
            }
            push(arrayAZ[i][j], &top, stack);
            numchar[top]=ncArrAZ[i][j];
        }

        else
        {  
            if(indAZ[i]==7)
            {
                aux[0]='{';
                aux[1]='\0';
                strcpy(auxCop,stackAux[(int)numAZ[i]]);
                strcat(aux,auxCop);
                auxFin[0]='}';
                auxFin[1]='\0';
                strcat(aux,auxFin);
                pushs(&top, &topS,stack, stackAux, numchar, aux);
            }
            else
            {
                strcpy(aux,stackAux[(int)numAZ[i]]);
                pushs(&top, &topS,stack, stackAux, numchar, aux);
            }
        }
    }

    return top;
}



/**
* \brief Esta função irá analisar todos os digitos e operadores enviados pela função main e colocá-los numa stack à medida que estes são analisados. 
*  Para além disto, de acordo com o operador inserido, a função em conjunto com  a stack criada, vai efetuar as funções de cálculo.
*
*  @param n[] Lista de chars recebida da função main. 
*  @param nSeguro[] Lista de chars segura. 
*/

void calcular(char n[], char nSeguro[])
{
    /**
    * \brief Definir inteiros que ajudaram no procedimento dos calculos
    */
    int a=0, xi,i;

    /**
    * \brief Definir doubles que ajudaram no procedimento dos calculos
    */
    double x;

    /**
    * \brief Definir char que ajudará no procedimento dos calculos
    */
    char c1, c2;


    /**
    * \brief Definir em que posição da stack o top começa(-1)
    */
    static int top = -1;

    /**
    * \brief Definir em que posição da stackAux o topS começa(0)
    */
    static int topS = 0;


    /**
     * \brief Defenir a stack
     */
    static double stack[500];
    
    /**
     *  \brief Defenir array que determina se o valor que está na stack é indice(1), int(2) ou double(3), array(4 e 6), string vazia(5), bloco(7 e 8)
     */
    static int numchar[500];
    
    
    /**
     * \brief Defenir a stack auxiliar que irá conter strings
     */
    static char stackAux[500][10240];
    
    /**
     * \brief Defenir o array auxiliar que irá conter a string a trabalhar 
     */
    char aux[10240];
    
    /**
     * \brief Defenir array que terá os valores associados às letras de A a Z
     */    
    double numAZ[26];

    /**
     *  \brief Defenir array que determina se o valor que está na numAZ é indice(1), int(2) ou double(3), array(4 e 6), string vazia(5), bloco(7 e 8)
     */
    int indAZ[26];

    /**
     * \brief Defenir matriz de A a Z que conterá os arrays associados às letras de A a Z
     */
    double arrayAZ[26][20];

    /**
     * \brief Defenir matriz de A a Z que conterá os numchars associados às letras de A a Z
     */
    int ncArrAZ[26][20];


    /**
     * \brief Colocar valores por omissão
     */
    for(i=0;i<6;i++)
    {
        numAZ[i]=10+i;
        indAZ[i]=3;
    }

    for(i = 23; i < 26; i++)
    {
        numAZ[i]=i-23;
        indAZ[i]=3;
    }

    aux[0]=10;
    aux[1]='\0';
    pushs(&top, &topS,stack, stackAux, numchar, aux);
    x = pop(&top, stack);
    numAZ[13]=x;
    indAZ[13]=1;


    aux[0]=' ';
    aux[1]='\0';
    pushs(&top, &topS,stack, stackAux, numchar, aux);
    x = pop(&top, stack);
    numAZ[18]=x;
    indAZ[18]=1;

    int letrasl=0;
    int aDepois=0;
    int topSDepois=0;

    
    aDepois=a;
    topSDepois=topS;



    while(n[a]) 
    {
        xi=top;
        top=IsNumber(n,a,top,stack,numchar,&letrasl);
        a=letrasl;
    
        c1=n[a];
        c2=n[a+1];
        top=eLetra(c1,c2,arrayAZ,numAZ,ncArrAZ,indAZ,top,topS,stack,numchar,stackAux);

        top=arrays(&aDepois,&topSDepois,a,n,top,topS,stack,numchar,stackAux);

        top=expressoesMat(&topSDepois,a,n,top,topS,stack,numchar,stackAux);
        
        top=funcoesLogicas(&topSDepois,&aDepois,a,n,top,topS,stack,numchar,stackAux);
        
        top=conversoes(&topSDepois,a,n,top,topS,stack,numchar,stackAux);
        
        top=InputOutput(&topSDepois,a,n,top,topS,stack,numchar,stackAux);

        top=funcoesrecursivas(&topSDepois,a,n,top,topS,stack,numchar,stackAux,nSeguro);

        a=aDepois;
        topS=topSDepois;

        if (n[a]=='~')
        {                   
            if(numchar[top]==6)
            {
                xi=top;
                while(numchar[xi]!=4) xi--;
                removeElemStack(stack,top,numchar,xi);
                top-=2;
            }
            else top=simbTil(top,stack,numchar,stackAux,nSeguro);     
        }
        if (n[a]==':')
        {
            a++;
            c1=n[a];
            simbDoisPontos(c1,arrayAZ,numAZ,ncArrAZ,indAZ,top,stack,numchar);
        }
        if(n[a]=='"')
        {
            a=simbDuasAspas(&topSDepois,a,n,top,topS,stack,numchar,stackAux);
            top++;
            topS=topSDepois;
        }
        if(n[a]=='{')
        {              
            push(1, &top, stack);
            numchar[top]=7;
            a+=2;
            aux[0]=' ';
            i=1;
            while(n[a+1]!='}')
            {
                aux[i++]=n[a++];
            }
            aux[i]=' ';
            aux[i+1]='\0';

            pushs(&top, &topS, stack, stackAux, numchar,aux);
            push(2, &top, stack);
            numchar[top]=8;
            a++;
        }

        a++;
    }

    /**
    * \brief A função printStack irá imprimir no ecrã a solução final. 
    */
    if(strcmp(n,nSeguro)==0)
    {
        printStack(&top, numchar, stackAux, stack); 
    }

}