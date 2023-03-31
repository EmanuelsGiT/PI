/**
 * @file Ficheiro que contém as funções matemáticas.
 */
#include <math.h>
#include <string.h>
#include "stack.h"
#include <ctype.h> 
#include <stdio.h>
#include "calculosG1.h"
#include <assert.h>



/**
 * \brief Esta função determina se o valor recebido é um inteiro
 *
 * @param a Valor que será avaliado
 * @param nummchar Array numchar recebido
 *
 * @return True(1) or False(0) Consoante se é inteiro ou não
 */

int isInt(int i, int numchar[])
{
    return(numchar[i]==2);
}


/**
 * \brief Esta função troca dois elementos dentro de um array de inteiros
 *
 * @param a[] Array recebido
 * @param i, @param j  Elementos recebidos
 *
 * Não retorna nada.
 */

void swap(int a[], int i, int j)
{
    int aux = a[i];
    a[i]=a[j];
    a[j]=aux;
}

/**
 * \brief Esta função troca dois elementos dentro de um array de doubles
 *
 * @param a[] Array recebido
 * @param i, @param j  Elementos recebidos
 *
 * Não retorna nada.
 */
void swapd(double a[], int i, int j)
{
    double aux = a[i];
    a[i]=a[j];
    a[j]=aux;
}


/**
 * \brief Esta função procura um certo elemento dentro de um array (Procura binária)
 *
 * @param x Elemento a procurar
 * @param t[] Array recebido
 * @param N Tamanho do array recebido
 *
 * @return l Indice do elemento no array (se o elemento não existir no array retorna (-1))
 */
int procura(char x, char t[], int N)
{
    int l=0, r=N-1, mid;

    while(r>l)
    {
        mid=(l+r)/2;
        if(t[mid]>=x) r=mid;
        else l=mid+1;
    }
    if(t[l]==x) return l;
    else return -1;

}


/**
 * \brief Esta função remove elemento da stack numa certa posição
 *
 * @param stack[] Stack recebida
 * @param top Top da Stack
 * @param numchar[] Array numchar recebido
 * @param pos Posição do elemento a retirar da stack
 *
 * @return l Indice do elemento no array (se o elemento não existir no array retorna (-1))
 */
void removeElemStack(double stack[], int top, int numchar[], int pos)
{
    pos++;
    while(pos<top && pos>0)
    {
        swap(numchar, pos, pos-1) ;
        swapd(stack,pos, pos-1);
        pos++;
    }
}

/**
 * \brief Converte double para char
 *
 * @param i Valor a ser convertido
 * @param t[] Array onde será colocado o char
 *
 * Não retorna nada
 */
void longtoa(double i, char t[])
{
    double d = 1, ii=i, rst;
    int pos=0,vv;

    if (ii==0)
    {
        t[pos]='0';
        pos++;
    }
    else
    {
        if (ii<0)
        {
            t[pos]='-';
            pos++;
            ii = -ii;
        }

        while(ii>=d) d=d*10;
        d=d/10;

        while (d>0.5)
        {
            vv = (int)(ii / d);
            rst=ii - vv*d;
            t[pos]=48+vv;
            pos++;
            ii=rst;
            d=d/10;
        }
    }
    t[pos]='\0';

}


/**
 * \brief Esta função concatena arrays ou array com outro elemento, dependendo do que recebe
 *
 * @param x Posição inicio do Array
 * @param end Posição final do Array
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 *
 * @return top Retorna topo da stack
 */
int concatenarSomaComArray(int x, int end, int top, double stack[], int numchar[])
{
    int xi, i;
    double y, z=top;
    if (numchar[(int)x-2]==6) 
    {
        //os dois elementos são arrays

        top=end+1;
        removeElemStack(stack,top,numchar,(int)x-1);
        top--;
        removeElemStack(stack,top,numchar,(int)x-2);
        top--;

    } 
    else 
    {
        top=end+1;
        xi=numchar[top];
        y = popR(&top, &end, numchar);
                                    
        if(xi==6)
        {
            //o primeiro elemento não é array
            swap(numchar,(int)y-1, (int)y-2);
            swapd(stack,(int)y-1, (int)y-2);
                                    
            for(i=y; i<=z; i++)
            {
                if(numchar[i]==1) 
                    top++;
                else 
                    push(stack[i], &top, stack);
            }

            top=end+1;

        }
        else
        {
            //o segundo elemento não é array
            top=end+2;
            removeElemStack(stack,top,numchar,xi);
            top--;
        }
                                    
    }
    return top;
}

/**
 * \brief Esta função soma ou concatena elementos
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int soma(int top, double stack[], int numchar[], char stackAux[][10240])
{
    int end, xi;
    double y , z=top;
    double x = popR(&top, &end, numchar);


    if (numchar[(int)x-1]==4 && x<=end && x>=0 && numchar[end+1]==6) 
    {
        top=concatenarSomaComArray(x,end,top,stack,numchar);
    }
                            
    else if(numchar[(int)x]==1)
    {
        top=end+1;
        x = pop(&top, stack);
        y = pop(&top, stack);
        //printf("%s %s\n", stackAux[(int)y], stackAux[(int)x]);
        strcat(stackAux[(int)y], stackAux[(int)x]);
        top++;
    }

    else
    {
        top=z;
        x = pop(&top, stack);

        if(numchar[top]==6)
        {
            xi=numchar[top+1];
            top--;
            push(x, &top, stack);
            numchar[top]=xi;
            push(x, &top, stack);
            numchar[top]=6;
        }
        else
        {
            y = pop(&top, stack);
            push(x+y, &top, stack);
        }

    }

    return top;
}

/**
 * \brief Esta função concatena n vezes um certo array
 *
 * @param ***topSDepois Apontador para topS - topo da stackAux
 * @param x Numero de vezes que array concatena
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param y Posição do inicio do Array
 * @param end Posição do final do array
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int concatenarNArrays(int ***topSDepois, double x, int top, int topS, double y, int end, double stack[], int numchar[], char stackAux[][10240])
{
    char aux[10240];
    int ri, i;
    for (ri=1; ri<x ;ri++)
    {
        for(i=(int)y; i<=end; i++)
        {
            if(numchar[i]==1 && ri<x)
            {
                strcpy(aux,stackAux[(int)stack[i]]);
                pushs(&top, &topS, stack, stackAux, numchar,aux);
            }
            else 
            {   
                numchar[top+1]=numchar[i];
                push(stack[i], &top, stack);
            }
        }
    }
                                
    push(1, &top, stack);
    numchar[top]=6;
    ***topSDepois=topS;

    return top;
}


/**
 * \brief Esta função concatena n vezes um certo array
 *
 * @param x Numero de vezes que array concatena
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int concatenarNStrings(int x,int top, double stack[], char stackAux[][10240])
{
    char aux[10240];
    double y=pop(&top, stack);
    int ri;
    strcpy(aux,stackAux[(int)y]);
    for (ri=1; ri<x ;ri++)
    {
        strcat(aux,stackAux[(int)y]);
    }
    strcpy(stackAux[(int)y],aux);
    top++;
    return top;
}


/**
 * \brief Esta função divide string por uma substring e coloca num array
 *
 * @param ***topSDepois Apontador para topS - topo da stackAux
 * @param x Posição do array na stackAux
 * @param y Posição do outro array na stackAux
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int subStringPorSubstring(int ***topSDepois, double x, double y, int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    int xi,yi, i, ri;
    char aux[10240];
    char auxCop[10240];
    char auxFin[10240];
    char *ret;

    xi=(int)x;
    yi=(int)y;

    strcpy(aux,stackAux[xi]);
    strcpy(auxCop,stackAux[yi]);

    push(1, &top, stack);
    numchar[top]=4;

    i=0;
    ret = strstr(auxCop+i,aux); //ret aponta para primeira ocorrência de qq

    while(ret!=NULL && auxCop[i])
    {
        for (ri=0; auxCop+i < ret; i++, ri++)
        {
            auxFin[ri]=auxCop[i];
        }
        auxFin[ri]='\0';
        pushs(&top, &topS, stack, stackAux, numchar,auxFin);
        i+=strlen(aux);
        ret = strstr(auxCop+i,aux);
    }
                                
    if((auxCop+strlen(auxCop))-(ret+strlen(aux))>0)
    {
        strcpy(auxFin,auxCop+i);
        pushs(&top, &topS, stack, stackAux, numchar,auxFin);
    }

    if(strcmp(auxCop + strlen(auxCop)-strlen(aux),aux )==0) top--;
  
    push(1, &top, stack);
    numchar[top]=6;
    ***topSDepois=topS;
    return top;
}


/**
 * \brief Esta função coloca o primeiro elemento do array no final desse mesmo array
 *
 * @param ***topSDepois Apontador para topS - topo da stackAux
 * @param x Posição do inicio do array
 * @param end Posição do final do array
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int eliminaPrimeiroElemArray(int ***topSDepois, double x, int end, int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    int i, yi=numchar[(int)x];
    double y=stack[(int)x];
    char aux[10240];

    if (yi==1) strcpy(aux, stackAux[(int)y]);

    numchar[1]=numchar[2];

    for(i=(int)x+1; i<=end; i++) 
    {
        numchar[i]=numchar[i+1]; 
        push(stack[i], &top, stack);
    }

    push(1,&top, stack);
    numchar[top]=6;

    push(2,&top, stack);
    numchar[top]=4;
                                
    if (yi==2 || yi==3) 
    {
        push(y, &top, stack);
    }
    else pushs(&top, &topS, stack, stackAux, numchar, aux);
    if (yi==2) numchar[top]=2; 
    if (yi==3) numchar[top]=3;

    push(1,&top, stack);
    numchar[top]=6;
    ***topSDepois=topS;                  
    return top;
}

/**
 * \brief Esta função coloca o primeiro caracter da string no final dessa string
 *
 * @param ***topSDepois Apontador para topS - topo da stackAux
 * @param k Posição da string na stackAux
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return topS Retorna topo da stackAux
 */
int eliminaPrimeiroElemString(int ***topSDepois, double k, int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    int i;
    char aux[10240];
    char auxCop[10240];
    char auxFin[10240];
    char c;

    auxFin[0]='\0';
    strcpy(aux,stackAux[(int)k]);
    c= aux[0];
    i=1;
    while(aux[i])
    {
        auxCop[0]=aux[i];
        auxCop[1]='\0';
        strcat(auxFin, auxCop);
        i++;
    }
    
    pushs(&top, &topS, stack, stackAux, numchar,auxFin);
    
    auxFin[0]=c;
    auxFin[1]='\0';
                                       
    pushs(&top, &topS, stack, stackAux, numchar,auxFin);
    ***topSDepois=topS;
    
    return topS;
}


/**
 * \brief Esta função coloca o primeiro elemento do array no final desse mesmo array
 *
 * @param x Posição do inicio do array
 * @param end Posição do final do array
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 *
 * @return top Retorna topo da stack
 */
int eliminaUltimoElemArray(double x, int end, int top, double stack[], int numchar[])
{
    double y,z;
    int yi, i,xi;

    xi=numchar[(int)x];
    z=stack[(int)x];
                       
    for(i=(int)x; i<end; i++) 
    {
        numchar[i+1]=numchar[i]; 
        yi=numchar[i+1];
        y=stack[i+1];
        push(z, &top, stack);
        numchar[top]=xi;
        xi=yi;
        z=y;                                    
    }

    yi=numchar[end];
    y=stack[end];

    push(1,&top, stack);
    numchar[top]=6;

    push(2,&top, stack);
    numchar[top]=4;

    push(y,&top, stack);
    numchar[top]=yi;

    push(1,&top, stack);
    numchar[top]=6;

    return top;
}


/**
 * \brief Esta função coloca o primeiro caracter da string no final dessa string
 *
 * @param ***topSDepois Apontador para topS - topo da stackAux
 * @param k Posição da string na stackAux
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return topS Retorna topo da stackAux
 */
int eliminaUltimoElemString(int ***topSDepois,double k, int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    int xi;
    char aux[10240];
    char auxCop[10240];
    char c;

    strcpy(aux,stackAux[(int)k]);
    xi=strlen(aux)-1;

    c=aux[xi];
                                    
    aux[xi]='\0';
    pushs(&top, &topS, stack, stackAux, numchar,aux);
    auxCop[0]=c;
    auxCop[1]='\0';
    pushs(&top, &topS, stack, stackAux, numchar,auxCop);
    ***topSDepois=topS;
    
    return topS;
}


/**
 * \brief Esta função coloca na stack o tamanho da string/array ou cria array com o certo range
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int tamanhoOuRange(int top, double stack[], int numchar[], char stackAux[][10240])
{
    int end, i;
    double x = popR(&top, &end, numchar);
    char aux[10240];

    if (numchar[(int)x-1]==4 && x<=end && x>=0 && numchar[end+1]==6) 
    {
        top--;
        push(end-x+1, &top, stack);
        numchar[top] = 2;
    }
                            
    else 
    {
        top=end+1;
        x = pop(&top, stack);

        if (numchar[top+1]==1) 
        {
            strcpy(aux, stackAux[(int)x]);
            i=0;
            while (aux[i]) 
            {
                i++;
            }
            push(i, &top, stack);
            numchar[top] = 2;
        } 

        else if (numchar[top+1]==2 || numchar[top+1]==3) 
        {
            i=0;
            push(1, &top, stack);
            numchar[top] = 4;

            while (i<(int)x) 
            {
                push(i, &top, stack);
                numchar[top] = 2;
                i++;
            }
            push(1, &top, stack);
            numchar[top] = 6;
        }
    } 
    return top;
}


/**
 * \brief Esta função coloca na stack o tamanho da string/array ou cria array com o certo range
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int cardinal(int top, double stack[], int numchar[], char stackAux[][10240])
{
    double x = pop(&top, stack);
    double y = pop(&top, stack);
    char aux[10240];
    char auxCop[10240];
    char *ret;
    int xi;

    if (numchar[top+1]==1) 
    {
        strcpy(aux,stackAux[(int)y]);
        strcpy(auxCop,stackAux[(int)x]);
        ret=strstr(aux, auxCop);
        xi=ret-aux;
        numchar[top+1]=2;
        push(xi,&top, stack);
    }
    else push(pow(y,x), &top, stack);

    return top;
}

/**
 * \brief Esta função copia n-ésimo elemento para o topo da stack
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int dolar(int top, double stack[], int numchar[], char stackAux[][10240])
{
    int i, xi, j;
    double y, x;
    long unsigned int xii;

    if(numchar[top]==8)
    {
        if (numchar[top]==1)
        {
            for (i = 0; i <= top; i++) 
            {
                xii = strlen(stackAux[(int)stack[i]]);
                x = stack[i];
                j = i - 1;
                while (j >= 0 && strlen(stackAux[(int)stack[j]]) > xii) 
                {
                    stack[j+1] = stack[j];
                    numchar[j+1] = numchar[j];
                    j = j - 1;
                }
                stack[j+1] = x;
                numchar[j+1]=1;
            }
        }
        else if (numchar[top]==2 || numchar[top]==3)
        {
            for (i = 0; i <= top; i++) 
            {
                x = stack[i];
                j = i - 1;
                while (j >= 0 && stack[j] > x) 
                {
                    stack[j + 1] = stack[j];
                    j = j - 1;
                }
                stack[j + 1] = x;
            }
        }
    }

    else 
    {
        xi  = (int)pop(&top,stack);
        y   = stack[top-xi];
        push(y, &top, stack);
    }
    return top;
}


/**
 * \brief Esta função faz um pop
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 *
 * @return top Retorna topo da stack
 */
int pontoEVirgula(int top, double stack[], int numchar[])
{
    if(top==0) numchar[top]=0;

    else if (numchar[top]==6) 
    {
        if(numchar[top-1]==6)
        {
            top--;
            for(;top>=0 && numchar[top]==6;top--)
            {
                while(numchar[top]!=4 && top>=0) top--;
            }
        }
        else
        {
            int end = popR(&top , &end, numchar);
            top--;
        }
    }

    else if(numchar[top]==8)
    {
        while(numchar[top]!=7 && top>=0) top--;
        top--;
    }

    else pop(&top, stack);

    return top;
}


/**
 * \brief Esta função converte o topo da stack num inteiro
 *
 * @param c Serve para testar se o simbolo anterior ao 'i' é o 'l'
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int converteInteiro(char c, int top, double stack[], int numchar[], char stackAux[][10240])
{
    char aux[10240];
    double m=0;
    int exp=0, mult=1, k, i;

    k = pop(&top, stack);
    
    if(numchar[top+1]==1)
    {
         //k é o indice da string na stackAux
         // é copiado para o array aux a string
         strcpy(aux,stackAux[k]);
    
        if(c!='l')
        {
            k = (int)aux[0];
            push(k, &top, stack);
            numchar[top]=2;
        }
        else
        {
            i=0;
    
            if(aux[i]=='-' && isdigit(aux[i+1]))
            {
                mult=-1;
                i++;
            }
    
            if (isdigit (aux[i]))
            { 
                m=aux[i]-48; 
                i++;
    
                while(isdigit(aux[i])||aux[i]=='.')
                {
                    if(aux[i]=='.')
                        exp=1;
    
                    else
                    {
                        m=m*10+(aux[i]-48);
                        exp=exp*10;
                    }
                            
                    i++;
                }
            }
    
            if(exp==0) exp=1;
    
            numchar[top+1]=2; //o elemento é do tipo int
            m=((m*mult)/exp);
            k=(int)m;
            push(k, &top, stack);
                                    
            mult = 1;  
            exp  = 0;
        }
    }
                                
    else
    {
        push(k, &top, stack);
        numchar[top]=2;
    }

    return top;
}


/**
 * \brief Esta função duplica o elemento que está no topo da stack
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 *
 * @return top Retorna topo da stack
 */
int duplicar(int top, double stack[], int numchar[])
{
    int i, end;
    double x;

    if(numchar[top]==6)
    {
        x = popR(&top, &end, numchar);
        top=end+1;

        for(i=x-1;i<=end+1;i++)
        {
            push(stack[i], &top, stack);
            numchar[top]=numchar[i];
        }
    }
    else
    {
        i = numchar[top];
        x = pop(&top,stack);
        push(x, &top, stack);
        push(x, &top, stack);
        numchar[top]=i;
    }

    return top;
}


/**
 * \brief Esta função troca um elemento não array com um array
 *
 * @param x Posição do inicio do array
 * @param end Posição do final do array
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 *
 * O numero ou string fora do array está em x-2
 *
 * @return top Retorna topo da stack
 */
int trocaElemComArray(double x, int end, int top, double stack[], int numchar[])
{
    //o primeiro não é um array
    //o numero ou string fora do array está em x-2

    double y;
    int xi, j;

    pop(&top,stack); //pop do '['
    y = pop(&top,stack);
    xi=numchar[top+1];

    for(j=x-1; j<=end+1; j++)
    {
        push(stack[j], &top, stack);
        numchar[top]=numchar[j];
    }
    push(y, &top, stack);
    numchar[top]=xi;

    return top;
}


/**
 * \brief Esta função troca um array com um elemento que não é array
 *
 * @param x Posição do inicio do array
 * @param end Posição do final do array
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 *
 * @return top Retorna topo da stack
 */
int trocaArrayComElem(double x, int end, int top, double stack[], int numchar[])
{
    int xi, j;

    top=end+1;

    x = pop(&top,stack);
    xi=numchar[top+1];

    popR(&top, &end, numchar);
                                        
    top+=1;
                                        
    for(j=end+2; j>=top; j--)
    {
        stack[j]=stack[j-1];
        numchar[j]=numchar[j-1];
    }
    
    stack[top-1]=x;
    numchar[top-1]=xi;
    top=end+2;

    return top;
}


/**
 * \brief Esta função troca um bloco com um elemento que não é bloco
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 *
 * @return top Retorna topo da stack
 */
int trocaBlocoComElem(int top, double stack[], int numchar[])
{
    double x,z;
    int xi;

    x = pop(&top,stack);
    xi=numchar[top+1];
    pop(&top,stack);
    z = pop(&top,stack);
    while(numchar[top]!=7 && top>=0) top--;
    top--;

    push(x, &top, stack);
    numchar[top]=xi;

    push(1, &top, stack);
    numchar[top]=7;

    push(z, &top, stack);
    numchar[top]=1;

    push(1, &top, stack);
    numchar[top]=8;

    return top;
}


/**
 * \brief Esta função converte o topo da stack num float
 *
 * @param c Serve para testar se o simbolo anterior ao 'f' é o 'l'
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int converteFloat(char c, int top, double stack[], int numchar[], char stackAux[][10240])
{
    char aux[10240];
    double m=0, x;
    int exp=0, mult=1, k, i;

    x = pop(&top, stack);
    k=(int)x;

    if(numchar[top+1]==1)
    {
        //k é o indice da string na stackAux
        // é copiado para o array aux a string
        strcpy(aux,stackAux[k]);
        if(c!='l')
        {
            x = aux[0];
            push(x, &top, stack);
            numchar[top]=3;
        }
        else
        {
            i=0;
            if(aux[i]=='-' && isdigit(aux[i+1]))
            {
                mult=-1;
                i++;
            }
            if (isdigit (aux[i]))
            { 
                m=aux[i]-48; 
                i++;
                while(isdigit(aux[i])||aux[i]=='.')
                {
                    if(aux[i]=='.')
                        exp=1;
                    else
                    {
                        m=m*10+(aux[i]-48);
                        exp=exp*10;
                    }
                    i++;
                }
            }
            if(exp==0) 
            {
                exp=1;
            }
            numchar[top+1]=3; //o elemento é do tipo double
            m=((m*mult)/exp);
            push(m, &top, stack);
            mult = 1;  
            exp  = 0;
        }
    }

    else
    {
        push(x, &top, stack);
        numchar[top]=3;
    }  

    return top;
}


/**
 * \brief Esta função realiza operações lógicas
 *
 * @param c Serve para testar qual o simbolo a seguir do 'e'
 * @param top Top da Stack
 * @param stack[] Stack recebida
 *
 * @return top Retorna topo da stack
 */
int caseE (char c, int top, double stack[])
{
    double x,y;

    x = pop(&top, stack);
    y = pop(&top, stack);

    if(c=='&')
    {
        if (x!=0 && y!=0) 
        {
            push(x, &top, stack); 
        }
        else 
            push(0, &top, stack);
    }

    if(c=='|')
    {
        if (y) push(y, &top, stack);
        else
        {
            if (x) push(x, &top, stack);
            else push(0, &top, stack);
        }
    }

    if(c=='<')
    {
        if (x>=y) push(x, &top, stack); 
        else push(y, &top, stack);
    }
        
    if(c=='>')
    {
        if (x<=y) push(x, &top, stack); 
        else push(y, &top, stack);
    }

    return top;
}


/**
 * \brief Esta função iguala valores ou indica um certo valor dada uma posição do array
 *
 * @param **topSDepois Apontador para topS - topo da stackAux
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int simbIgual(int **topSDepois, int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    double x, y;
    int end;
    char aux[10240];
    char auxCop[10240];


    x = pop(&top, stack);
    y = popR(&top, &end, numchar);
    if (numchar[(int)y-1]==4 && numchar[end+1]==6 && y<=end && y>=0) 
    {
        top--;
        push(stack[(int)(y+x)], &top, stack);
        numchar[top]=numchar[(int)(y+x)];
    }
    else
    {
        top=end+1;
        y = pop(&top, stack);
        if(numchar[top+1]==1 && numchar[top+2]==1) 
        {
            if(strcmp(stackAux[(int)x], stackAux[(int)y])==0)
            {
                push(1, &top, stack);
                numchar[top]=2;
            }
            else 
            {
                push(0, &top, stack);
                numchar[top]=2;
            }

        }
        else if(numchar[top+1]==1)
        {
            strcpy(aux,stackAux[(int)y]);
            auxCop[0]=aux[(int)x];
            pushs(&top, &topS, stack, stackAux, numchar,auxCop);
        }
        else
        {
            if (y==x) 
            {
                push(1, &top, stack);
                numchar[top]=2;
            }
            else 
            {
                push(0, &top, stack);
                numchar[top]=2;
            }
        }
        
    }
    **topSDepois=topS;
    return top;
}

/**
 * \brief Não lógico
 *
 * @param c1 Serve para testar qual o simbolo antes do '!'
 * @param c2 Serve para testar se o elemento char é um '0'
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int simbPontoExclamacao(char c1, char c2, int top, double stack[], int numchar[], char stackAux[][10240])
{
    int k;
    double x, z = pop(&top, stack);

    if(numchar[top+1]==1)
    {
        k=(int)z;
        //k é o indice da string na stackAux
        x = stackAux[k][0];
        numchar[top+1]=2;
    }
    else x=z;

    if(c1=='c' && x==0 && c2!='0') 
        push(0, &top, stack);
    else 
    {
        if (x!=0) push(0, &top, stack);
        if (x==0) push(1, &top, stack); 
    }
    return top;
}



/**
 * \brief If-the-else
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 *
 * @return top Retorna topo da stack
 */
int simbPontoInterrogacao(int top, double stack[], int numchar[])
{
    double x,y,z,r;

    x = pop(&top, stack);
    y = pop(&top, stack);
    z = pop(&top, stack);

    if(z==5) 
    {
        z=0;
        if (z) r=y;
        else r= x;
    }
    else
    {
        if (z) r=y;
        else r= x;
    }

    push(r, &top, stack);
    numchar[top]=2;

    return top;
}


/**
 * \brief Esta função dá como resultado a maior string
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int simbMaiorStrings(int top, double stack[], int numchar[], char stackAux[][10240])
{
    double x,y;

    if(numchar[top]==1 && numchar[top-1]==1)
    {
        x = pop(&top,stack);
        y = pop(&top,stack);

        if(strcmp(stackAux[(int)x], stackAux[(int)y])<0)
        {
            push(1, &top, stack);
            numchar[top]=2;
        }
        else 
        {
            push(0, &top, stack);
            numchar[top]=2;
        }
    }
    return top;
}


/**
 * \brief Esta função é o maior lógico ou vai buscar n elems/carat ao fim da string/array
 *
 * @param **topSDepois Apontador para topS - topo da stackAux
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int simbMaior(int **topSDepois,int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    double x,y,z;
    int k,i,a=0;
    char aux[10240];
    char auxCop[10240];

    z = pop(&top, stack);
    
    if(numchar[top]==1 && numchar[top+1]==1)
    {
        top++;
        top=simbMaiorStrings(top,stack,numchar,stackAux);
    }

    else
    {
        x=z;
        z = pop(&top, stack);

        if(numchar[top+1]==1)
        {
            k=(int)z;
            //k é o indice da string na stackAux
            strcpy(aux,stackAux[k]);
            //k é o indice da string na stackAux
            if(aux[1])
            {
                for(i=0; i<x;i++)
                    auxCop[i]=aux[strlen(aux)-(int)x+i];
                auxCop[i]='\0';
                a=1;
            }
            else
            {
                y = stackAux[k][0];
                numchar[top+1]=2;
            }
        }
        else y=z;

        if(a==1) pushs(&top, &topS,stack, stackAux, numchar, auxCop);
        else
        {
            if (y>x) push(1, &top, stack);
            else push(0, &top, stack);
        }
    }
    **topSDepois=topS;

    return top;
}


/**
 * \brief Esta função dá como resultado a menor string
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int simbMenorStrings(int top, double stack[], int numchar[], char stackAux[][10240])
{
    double x,y;

    x = pop(&top,stack);
    y = pop(&top,stack);
    if(strcmp(stackAux[(int)x], stackAux[(int)y])>0)
    {
        push(1, &top, stack);
        numchar[top]=2;
    }
    else 
    {
        push(0, &top, stack);
        numchar[top]=2;
    }
    
    return top;
}


/**
 * \brief Esta função é o menor lógico ou vai buscar n elems/carat ao inicio da string/array
 *
 * @param **topSDepois Apontador para topS - topo da stackAux
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int simbMenor(int **topSDepois,int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    double x,y,z;
    int k,i,a=0;
    char aux[10240];
    char auxCop[10240];

    z = pop(&top, stack);

    if(numchar[top]==1 && numchar[top+1]==1)
    {
        top++;
        top=simbMenorStrings(top,stack,numchar,stackAux);
    }

    else
    {
        x=z;
        z = pop(&top,stack);

        if(numchar[top+1]==1)
        {
            k=(int)z;
            //k é o indice da string na stackAux
            strcpy(aux,stackAux[k]);
            if(aux[1])
            {
                for(i=0; i<x;i++)
                    auxCop[i]=aux[i];
                auxCop[i]='\0';
                a=1;
            }
            else
            {
                y = stackAux[k][0];
                numchar[top+1]=2;
            }
        }
        else y=z;

        if(a==1) pushs(&top, &topS,stack, stackAux, numchar, auxCop);
        else
        {
            if (y<x) push(1, &top, stack);
            else push(0, &top, stack);
        }
    }   
    **topSDepois=topS;
    return top;
}


/**
 * \brief Esta função converte o topo da stack para string
 *
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return topS Retorna topo da stackAux
 */
int converteParaString(int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    double x = pop(&top, stack);

    char aux[10240];

    if(numchar[top+1]!=1)
    {
        longtoa(x,aux);
        pushs(&top, &topS, stack, stackAux, numchar,aux); 
    }  

    return topS;
}


/**
 * \brief Esta função divide ou separa strings por substring
 *
 * @param **topSDepois Apontador para topS - topo da stackAux
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int simbBarra(int **topSDepois, int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    double r,x,y;
    int ri,xi,yi;

    x = pop(&top, stack);
    y = pop(&top, stack);

    if(isInt(top+1, numchar) && isInt(top+2, numchar))
    {
        xi=(int)x;
        yi=(int)y;
        ri=yi/xi;
        push(ri, &top, stack);
        numchar[top]=2;
    }
    else if(numchar[top+2]==5)
    {
        //aux é uma lista vazia
        xi=numchar[top+1];
        push(y, &top, stack);
        numchar[top]=xi;
    }
    else if(numchar[top+1]==1)
    {
        top=subStringPorSubstring(&topSDepois,x,y,top,topS,stack,numchar,stackAux);
    }
    else 
    {
        r=y/x;
        push(r, &top, stack);
        numchar[top]=3;
    }

    return top;
}


/**
 * \brief Esta função serve para decrementar um valor ou remover o 1º elem do array
 *
 * @param **topSDepois Apontador para topS - topo da stackAux
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int simAbrirParenteses(int **topSDepois,int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    int k, end, xi;
    double x;
    char aux[10240];

    x = popR(&top, &end, numchar);

    if (numchar[(int)x-1]==4 && x<=end && x>=0 && numchar[end+1]==6) 
    {
        top=eliminaPrimeiroElemArray(&topSDepois,x,end,top,topS,stack,numchar,stackAux);
    }

    else 
    {
        top=end+1;
        k = pop(&top, stack);

        if(numchar[top+1]==1)
        {
            strcpy(aux,stackAux[(int)k]);
            xi=strlen(aux)-1;
            if(xi==0)
            {
                aux[0]=stackAux[k][0]-1;
                aux[1]='\0';
                pushs(&top, &topS, stack, stackAux, numchar,aux);
            }
            else
            {
                topS=eliminaPrimeiroElemString(&topSDepois,k,top,topS,stack,numchar,stackAux);
                top=top+2;
            }
        }
        else
        {
            push(k-1, &top, stack);
        } 
    }

    return top;
}


/**
 * \brief Esta função serve para incrementar um valor ou remover o ultimo elem do array
 *
 * @param **topSDepois Apontador para topS - topo da stackAux
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int simbFecharParenteses(int **topSDepois,int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    int k, end, xi;
    double x;
    char aux[10240];

    x = popR(&top, &end, numchar);
    if (numchar[(int)x-1]==4 && x<=end && x>=0 && numchar[end+1]==6) 
    {
        top=eliminaUltimoElemArray(x,end,top,stack,numchar);
    }
    else 
    {
        top=end+1;
        k = pop(&top, stack);
        if(numchar[top+1]==1)
        {
            strcpy(aux,stackAux[(int)k]);
            xi=strlen(aux)-1;
            if(xi==0)
            {
                aux[0]=stackAux[k][0]+1;
                aux[1]='\0';
                pushs(&top, &topS, stack, stackAux, numchar,aux);
            }
            else
            {
                topS=eliminaUltimoElemString(&topSDepois,k,top,topS,stack,numchar,stackAux);
                top=top+2;
            }
        }
        else
            push(k+1, &top, stack); 
    }

    return top;
}


/**
 * \brief Esta função cria uma string
 *
 * @param *topSDepois Apontador para o top da stackAux
 * @param a Indice no array n
 * @param n Array n recebido
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return a Indice no array n depois de lida a string
 */
int simbDuasAspas(int *topSDepois, int a, char n[], int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    char aux[10240];
    
    a++;
    if(n[a]=='"')
    {
        //a string é vazia
        push(1, &top, stack);
        numchar[top]=5;
    }
    else
    {
        a--;
        if(n[a+1]!='"' && n[a+1]!='\0')
        {   
            a++;
            int i=0;
            while(n[a]!='"' && n[a]!='\0')
            {
                aux[i]=n[a];
                a++; i++;
            }
            aux[i]='\0';
            pushs(&top, &topS, stack, stackAux, numchar,aux);
        }
        *topSDepois = topS;
    }

    return a;
}


/**
 * \brief Esta associa a uma letra o elemento no topo da stack
 * 
 * @param c Letra a que se vai associar elemento
 * @param arrayAZ[][] conterá os arrays associados às letras de A a Z
 * @param numAZ[] terá os valores associados às letras de A a Z
 * @param ncArrAZ[][] conterá os numchars associados às letras de A a Z
 * @param indAZ determina se o valor que está na numAZ é indice(1), int(2) ou double(3), array(4 e 6), string vazia(5), bloco(7 e 8)
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 */
void simbDoisPontos(char c, double arrayAZ[][20], double numAZ[], int ncArrAZ[][20], int indAZ[], int top, double stack[], int numchar[])
{
    double x;
    int i,k,j,yi;
    char arrAZ[27]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    x = stack[top];
    i=procura(c,arrAZ,26);

    if(numchar[top]==3||numchar[top]==2) 
    {
        numAZ[i]=x;
        indAZ[i]=3;
    }
    else if(numchar[top]==6)
    {
        j=top;
        if(numchar[top-1]==6)
        {
            j--;
            for(yi=0;j>0 && numchar[j]==6 && j<=top;yi++)
            {
                while(numchar[j]!=4 && j>=0) j--;
                j--;
            }
            //o array tem yi subarrays -> [ [1] [2] [3] ]
            arrayAZ[i][0]=50;
            ncArrAZ[i][0]=4;
            j++; yi=1;
            while(j<=top && numchar[j]==4)
            {
                while(numchar[j]!=6 && j<=top) 
                {
                    arrayAZ[i][yi]=stack[j];
                    ncArrAZ[i][yi]=numchar[j];
                    j++; yi++;
                }
                j++; yi++;
            }
            arrayAZ[i][yi]=100;
            ncArrAZ[i][yi]=6;
        }
        else
        {
            while(numchar[j]!=4) j--;
            for(k=0;j<=top;j++,k++)
            {
                arrayAZ[i][k]=stack[j];
                ncArrAZ[i][k]=numchar[j];
            }
        }
        indAZ[i]=9;
    }
    else
    {
        if(numchar[top]==8) 
        {
            numAZ[i]=x+2;
            indAZ[i]=7;
        }
        else 
        {
            numAZ[i]=x;
            indAZ[i]=1;
        }
    }
}



/**
 * \brief Esta função serve para separar uma string por whitespace, colocando o resultado num array
 *
 * @param **topSDepois Apontador para topS - topo da stackAux
 * @param c Correspondente ao n[a]
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int simbS(int **topSDepois,char c, int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    double x;
    int xi,i,ri;
    char aux[10240];
    char auxCop[10240];

    if(c=='/')
    {
        x = pop(&top, stack);
        xi = (int)x; //xi é um indice
        strcpy(aux,stackAux[xi]);
        push(1, &top, stack);
        numchar[top]=4;
        i=0;
        while(aux[i]!='\0')
        {
            ri=0;
            while(aux[i]!=' ' && aux[i]!='\n' && aux[i]!='\0') //&& aux[i]!='\n'
            {
                auxCop[ri]=aux[i];
                i++;ri++;
            }
            auxCop[ri]='\0';
            pushs(&top, &topS, stack, stackAux, numchar,auxCop); 
            i++;
        }
        push(1, &top, stack);
        numchar[top]=6;
    }
    **topSDepois=topS;

    return top;

}


/**
 * \brief Esta função serve para separar uma string por newlines, colocando o resultado num array
 *
 * @param **topSDepois Apontador para topS - topo da stackAux
 * @param c Correspondente ao n[a]
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int simbN(int **topSDepois,char c, int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    double x;
    int xi,i,ri;
    char aux[10240];
    char auxCop[10240];

    if(c=='/')
    {
        x = pop(&top, stack);
        xi = (int)x; //xi é um indice
        strcpy(aux,stackAux[xi]);
        push(1, &top, stack);
        numchar[top]=4;
        i=0;
        while(aux[i]!='\0')
        {
            ri=0;
            while(aux[i]!='\n' && aux[i]!='\0')
            {
                auxCop[ri]=aux[i];
                i++;ri++;
            }
            auxCop[ri]='\0';
            pushs(&top, &topS, stack, stackAux, numchar,auxCop); 
            i++;
        }
        push(1, &top, stack);
        numchar[top]=6;
    }
    **topSDepois=topS;
    return top;
}


/**
 * \brief Funções Lógicas
 *
 * @param *topSDepois Apontador para topS - topo da stackAux
 * @param *aDepois Corresponde ao valor de a depois de percorridas as funções
 * @param a Indice do array n
 * @param n Array n recebido
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int funcoesLogicas(int *topSDepois,int *aDepois, int a, char n[], int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    char c;
    switch(n[a])
    {
        case '<' :

            top=simbMenor(&topSDepois,top,topS,stack,numchar,stackAux);
            break;
                                
        case '>' : 

            top=simbMaior(&topSDepois,top,topS,stack,numchar,stackAux);
            break;
    
        case '=' : 

            top=simbIgual(&topSDepois,top,topS,stack,numchar,stackAux);
            break;
    
        case '!' : 
                                
            top=simbPontoExclamacao(n[a-2],n[a-4],top,stack,numchar,stackAux);
            break;
                            
        case '?':
    
            top=simbPontoInterrogacao(top,stack,numchar);
            break;
    
        case 'e':
    
            a++;
            c=n[a];
            top=caseE(c,top,stack);

            break;
    }

    *aDepois=a;
    return top;
}


/**
 * \brief Conversões do topo da stack
 *
 * @param *topSDepois Apontador para topS - topo da stackAux
 * @param a Indice do array n
 * @param n Array n recebido
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int conversoes(int *topSDepois, int a, char n[], int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    char c;
    double x;
    char aux[10240];

    switch(n[a])
    {
        case 's':

            topS=converteParaString(top,topS,stack,numchar,stackAux);
            break;

        case 'f' :

            c = n[a-2];
            top=converteFloat(c,top,stack,numchar,stackAux);
            break;

        case 'c' : 

            x = pop(&top, stack);
            aux[0] = x;
            aux[1] = '\0';
            pushs(&top, &topS, stack, stackAux, numchar,aux);
            break;

        case 'i':
                            
            c = n[a-2];
            top=converteInteiro(c,top,stack,numchar,stackAux);
            break; 
    }

    *topSDepois=topS;
    //printf("%d\n",*topSDepois );
    return top;
}


/**
 * \brief Funções de Input/Output
 *
 * @param *topSDepois Apontador para topS - topo da stackAux
 * @param a Indice do array n
 * @param n Array n recebido
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int InputOutput(int *topSDepois,int a, char n[], int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    char aux[10240];
    char auxCop[10240];

    switch(n[a])
    {
        case 'l':
                            
            if(n[a+1]==' ')
            {
                assert(fgets(aux,10240,stdin));
                pushs(&top, &topS, stack, stackAux, numchar,aux );
            }
            break;

        case 't':

            
            while(fgets(aux,10240,stdin)!=NULL && aux[0]!='\n')
            {
                strcat(auxCop,aux);
            }
            pushs(&top, &topS,stack, stackAux, numchar, auxCop);
            break;

        case 'p':

            auxPrint(top,numchar,stackAux,stack);
            break;
    }
    *topSDepois=topS;

    return top;
}


/**
 * \brief Funções de Arrays e Strings
 *
 * @param *aDepois Corresponde ao valor de a depois de percorridas as funções
 * @param *topSDepois Apontador para topS - topo da stackAux
 * @param a Indice do array n
 * @param n Array n recebido
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int arrays(int *aDepois, int *topSDepois, int a, char n[], int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    char c;
    switch(n[a])
    {  
        /*case '"':
            printf("im\n");
                printStack(&top, numchar, stackAux, stack); 

            a=simbDuasAspas(&topSDepois,a,n,top,topS,stack,numchar,stackAux);
            top++;
            *aDepois=a;
            break; */

        case '[':

            push(50, &top, stack);
            numchar[top]=4;
            break;
                        
        case ']':

            push(100, &top, stack);
            numchar[top]=6;
            break;

                        
        case 'S':

            if(n[a+1]=='/')
            {
                a++;
                c=n[a];
                top=simbS(&topSDepois,c,top,topS,stack,numchar,stackAux);
                *aDepois=a+1;
            }

            break;

        case 'N':

            if(n[a+1]=='/')
            {
                a++;
                c=n[a];
                top=simbN(&topSDepois,c,top,topS,stack,numchar,stackAux);
                *aDepois=a+1;
            }

            break;
    }
    return top;
}



/**
 * \brief Funções de expressões matemáticas
 *
 * @param *topSDepois Apontador para topS - topo da stackAux
 * @param a Indice do array n
 * @param n Array n recebido
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 *
 * @return top Retorna topo da stack
 */
int expressoesMat(int *topSDepois, int a, char n[], int top, int topS, double stack[], int numchar[], char stackAux[][10240])
{
    double x,y;

    switch(n[a])
    {
        case ' ':break;
    
        case '+':

            top=soma(top,stack,numchar,stackAux);
            break; 

        case '-':

            x = pop(&top, stack);
            y = pop(&top, stack);
            push(y-x, &top, stack);
            break;
            
        case '/':

            top=simbBarra(&topSDepois,top,topS,stack,numchar,stackAux);
            break;
                            
        case '(': 

            top=simAbrirParenteses(&topSDepois,top,topS,stack,numchar,stackAux);
            break;
                            
        case ')':

            top=simbFecharParenteses(&topSDepois,top,topS,stack,numchar,stackAux);
            break;
        
        case '#':

            top=cardinal(top,stack,numchar,stackAux);
            break;
    
        case '&':

            x = pop(&top, stack);
            y = pop(&top, stack);
            push((int)y &(int)x, &top, stack);
            break;
    
        case '|':

            x = pop(&top, stack);
            y = pop(&top, stack);
            push((int)y | (int)x, &top, stack);
            break;
    
        case '^':

            x = pop(&top, stack);
            y = pop(&top, stack);
            push((int)y^(int)x, &top, stack);
            break;

        case '$':

            top=dolar(top,stack,numchar,stackAux);
            break;

    }

    return top;
}


/**
 * \brief Funções do simbolo '*'
 *
 * @param **topSDepois Apontador para topS - topo da stackAux
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 * @param nSeguro Array nSeguro recebido
 *
 * @return top Retorna topo da stack
 */
int simbVezes(int **topSDepois, int top, int topS, double stack[], int numchar[], char stackAux[][10240], char nSeguro[])
{
    int k, end, i;
    double x, y;
    char aux[10240];
    char auxCop[10240];
    char auxFin[10240];
    char bloco[10240];
    

    if (numchar[top]==8) 
    {
        //erro-> só funciona para arrays com 3 elementos
        k=top;
        strcpy(bloco,stackAux[(int)stack[k-1]]);
        while(numchar[k]!=7 && k>=0) k--;
        end= k-1;
        while(numchar[k-1]!=4 && k>0) k--;  
        
        push(top, &top, stack);
        numchar[top]=-1;

        longtoa(stack[end-1],aux);
        auxCop[0]=' ';
        auxCop[1]='\0';
        strcat(aux,auxCop);

        for (i=end-2;i>=k;i--)
        {
            if(numchar[i]==2) 
            {
                longtoa(stack[i],auxFin);
                strcat(aux,auxFin);
            }
            else strcpy(aux,stackAux[(int)stack[i]]);
            strcat(aux,bloco);
        }
        //printf("vai calcular\n");
        calcular(aux,nSeguro);
        //top=fold(top,stack,numchar,stackAux,nSeguro);
    }
    else 
    {
        x = pop(&top, stack); //n vezes que se concatena
        y = popR(&top, &end, numchar);
        if (numchar[(int)y-1]==4 && numchar[end+1]==6)
        {
            top=end;
            top = concatenarNArrays(&topSDepois,x,top,topS,y,end,stack,numchar,stackAux);
        } 
        else if(numchar[(int)y]==1)
        {
            top=end+1;
            top=concatenarNStrings(x,top,stack,stackAux);
        }
        else 
        {
            top=end+1;
            y = pop(&top, stack);
            push(x*y, &top, stack);
        }
    }
    return top;
}



/**
 * \brief Funções do simbolo ','
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 * @param nSeguro Array nSeguro recebido
 *
 * @return top Retorna topo da stack
 */
int simbVirgula(int top, double stack[], int numchar[], char stackAux[][10240], char nSeguro[])
{
    int k, end, i;
    double x;
    char aux[10240];
    char auxCop[10240];

    if (numchar[top]==8) 
    {
        k=top;
        while(numchar[k]!=7 && k>=0) k--;
        end= k-1;
        while(numchar[k-1]!=4 && k>0) k--;  
        push(k-2, &top, stack);
        numchar[top]=-1;
 
        for (i=k;i<end;i++)
        {
            if(numchar[i]==2 || numchar[i]==3)
            {
                longtoa(stack[i],aux);
                auxCop[0]=' ';
                auxCop[1]='\0';
                strcat(aux,auxCop);
            }
            if(numchar[i]==1)
            {
                aux[0]='"';
                aux[1]='\0';
                strcat(aux,stackAux[(int)stack[i]]);
                auxCop[0]='"';
                auxCop[1]='\0';
                strcat(aux,auxCop);
            }
            strcat(aux,stackAux[(int)stack[end+2]]);
            calcular(aux,nSeguro);
            aux[0]='\0';
        }
        push(k-2, &top, stack);
        numchar[top]=-1;
        i=0;
        while (k<end)
        {
            x = stack[end+5+i]; 
            if (x!=0)
            {
                push(stack[k], &top, stack);
                numchar[top]=2;
            }
            k++;
            i++;
        }
    }
    else
    {
        top=tamanhoOuRange(top,stack,numchar,stackAux);
    }

    return top;
}



/**
 * \brief Funções do simbolo '%'
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 * @param nSeguro Array nSeguro recebido
 *
 * @return top Retorna topo da stack
 */
int simbPercentagem(int top, double stack[], int numchar[], char stackAux[][10240], char nSeguro[])
{

    int k, end, i;
    double x,y;
    char aux[10240];
    char auxCop[10240];
    char auxFin[10240];

    if (numchar[top]==8) 
    {
        //errada
        k=top;
        while(numchar[k]!=7 && k>=0) k--;
        end= k-1;
        while(numchar[k-1]!=4 && k>0) k--;   
        push(k-3, &top, stack);
        numchar[top]=-1;
        /*
        //acrescenta elementos anteriores da stack ao array
        for (i=0;i<k-1;i++)
        {
            j=0;
            if(numchar[i]==2 || numchar[i]==3)
            {
                longtoa(stack[i],aux);
                strcat(aux," ");
            }
            if(numchar[i]==1)
            {
                aux[0]='"';
                aux[1]='\0';
                strcat(aux,stackAux[(int)stack[i]]);
                auxCop[0]='"';
                auxCop[1]=' ';
                auxCop[2]='\0';
                strcat(aux,auxCop);
            }
        }*/
        aux[0]=0;
        //acrescenta elemento que está dentro do array
        for (i=k;i<end;i++)
        {
            strcpy(auxFin,aux);

            if(numchar[i]==2 || numchar[i]==3)
            {
                longtoa(stack[i],auxCop);
                strcat(auxFin,auxCop);
            }
            if(numchar[i]==1)
            {
                auxCop[0]='"';
                auxCop[1]='\0';
                strcat(auxCop,auxFin);
                strcat(auxCop,stackAux[(int)stack[i]]);
                auxFin[0]='"';
                auxFin[1]='\0';
                strcat(auxCop,auxFin);
                strcpy(auxFin,auxCop);
            }
            
            strcat(auxFin,stackAux[(int)stack[end+2]]);
            calcular(auxFin,nSeguro);
            auxFin[0]='\0';
        }
        top=end+i+i-1;
    }
    else 
    {
        x = pop(&top, stack);
        y = pop(&top, stack);
        push((int)y%(int)x, &top, stack);
    }

    return top;
}




/**
 * \brief Funções do simbolo '%' quando usasse blocos
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 * @param nSeguro Array nSeguro recebido
 *
 * @return top Retorna topo da stack
 */
int simbTilNC8(int top, double stack[], int numchar[], char stackAux[][10240], char nSeguro[])
{
    int xi,j,k,end,i;
    char aux[10240];
    char auxCop[10240];

    k=top;
    while(numchar[k]!=7 && k>=0) k--;
    if (numchar[k-1]==6)
    {
        end= k-1;
        while(numchar[k-1]!=4 && k>0) k--; // k está na pos inicial do array
        push(k-2, &top, stack);
        numchar[top]=-1;
        j=0;
        for (i=k;i<end;i++)
        {
            if(numchar[i]==2 || numchar[i]==3)
            {
                longtoa(stack[i],aux);
            }
            if(numchar[i]==1)
            {
                aux[0]='"';
                aux[1]='\0';
                strcat(aux,stackAux[(int)stack[i]]);
                auxCop[0]='"';
                auxCop[1]='\0';
                strcat(aux,auxCop);
            }
            xi=strlen(aux);
            j = xi + strlen(stackAux[(int)stack[end+2]]);
            strcat(aux,stackAux[(int)stack[end+2]]);
            aux[j]=' ';
            j++;
            aux[j+1]='\0';
            calcular(aux,nSeguro);
            aux[0]='\0';
        }
    }
    else
    {
        push(k-2, &top, stack);
        numchar[top]=-1;
        for(i=0; i<k; i++)
        {
        if(numchar[i]==2 || numchar[i]==3)
        {
            longtoa(stack[i],aux);
        }
        if(numchar[i]==1)
        {
            aux[0]='"';
            aux[1]='\0';
            strcat(stackAux[(int)stack[i]],aux);
            strcat(aux,stackAux[(int)stack[i]]);
        }
        }
        strcat(aux,stackAux[(int)stack[k+1]]);
    }
    calcular(aux,nSeguro);
    return top;
}


/**
 * \brief Funções do simbolo '%' quando usasse blocos
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 * @param nSeguro Array nSeguro recebido
 *
 * @return top Retorna topo da stack
 */
int simbTilBloco(int top, double stack[], int numchar[], char stackAux[][10240], char nSeguro[])
{    
    int xi,j,k,end,i;
    char aux[10240];
    char auxCop[10240];

    k=top;
    while(numchar[k]!=7 && k>=0 &&numchar[k]!=8) k--;
    push(k-1, &top, stack);
    numchar[top]=-1;
    if (numchar[k-1]==6)
    {
        end= k-1;
        while(numchar[k-1]!=4 && k>0) k--;
        j=0;
        for (i=k;i<end;i++)
        {
            if(numchar[i]==2 || numchar[i]==3)
            {
                longtoa(stack[i],aux);
            }
            if(numchar[i]==1)
            {
                j = 1 + strlen(stackAux[(int)stack[i]]);
                strcat(aux,stackAux[(int)stack[i]]);
                aux[j]=' ';
            }
            xi=strlen(aux);
            j = xi + strlen(stackAux[(int)stack[end+2]]);
            strcat(aux,stackAux[(int)stack[end+2]]);
            aux[j]=' ';
            j++;
            aux[j+1]='\0';
            calcular(aux,nSeguro);
            aux[0]='\0';
        }
    }
    else
    {
        i=top-2;
        if(numchar[i]==2 || numchar[i]==3)
        {
            longtoa(stack[i],aux);
        }
        if(numchar[i]==1)
        {
            aux[0]='"';
            aux[1]='\0';
            strcat(stackAux[(int)stack[i]],aux);
            strcat(aux,stackAux[(int)stack[i]]);
        }
        i+=1;
        strcpy(auxCop,stackAux[(int)stack[i]]);
        strcpy(auxCop, auxCop+1);
        xi=strlen(auxCop)-1;
        auxCop[xi]='\0';
        strcat(aux,auxCop);
        calcular(aux,nSeguro);
    }

    return top;
}



/**
 * \brief Funções do simbolo '~'
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 * @param nSeguro Array nSeguro recebido
 *
 * @return top Retorna topo da stack
 */
int simbTil(int top, double stack[], int numchar[], char stackAux[][10240], char nSeguro[])
{
    double x;

    if(numchar[top]==8)
    {
        top=simbTilNC8(top,stack,numchar,stackAux,nSeguro);
    }
    else if(numchar[top]==1 && stackAux[(int)stack[top]][0]=='{')
    {        
        top=simbTilBloco(top,stack,numchar,stackAux,nSeguro);
    }
    else
    {
        x = pop(&top,stack);
        push(~(int)x, &top, stack);
    }

    return top;
}


/**
 * \brief Funções do simbolo '\\' com arrays
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 * @param nSeguro Array nSeguro recebido
 *
 * @return top Retorna topo da stack
 */
int simbDuasBarrasArr(double x,double end,int top, double stack[], int numchar[])
{
    int i,j,xi,acop;
    double auxInt[100];
    double auxInt2[100];
    int auxNInt[100];
    int auxNInt2[100];

    if (numchar[(int)x-2]==6) 
    {
        //erro -> só funciona para certos arrays pequenos
        //os dois elementos são arrays
        end+=1;
        x-=1;
        //copia o segundo array para auxInt
        for(i=x,j=0; i<=end;i++,j++)
        {
            auxInt[j]=stack[i];
            auxNInt[j]=numchar[i];
        }
        acop=x-1;
        xi=acop;
        while(numchar[acop]!=4 && acop>=0) acop--;
        //copia o primeiro array para auxInt2
        for(i=acop,j=0; i<=xi;i++,j++)
        {
            auxInt2[j]=stack[i];
            auxNInt2[j]=numchar[i];
        }
        top=acop-1;
        j=0;
        while(top<end-x)
        {
            push(auxInt[j], &top, stack);
            numchar[top]=auxNInt[j];
            j++;
        }
        j=0;
        while(j<xi-acop+1)
        {
            push(auxInt2[j], &top, stack);
            numchar[top]=auxNInt2[j];
            j++;
        }
    }
    else
    {
        top = trocaElemComArray(x,end,top,stack,numchar);
    }

    return top;
}




/**
 * \brief Funções do simbolo '\\'
 *
 * @param top Top da Stack
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 * @param nSeguro Array nSeguro recebido
 *
 * @return top Retorna topo da stack
 */
int simbDuasBarras(int top, double stack[], int numchar[])
{
    int xi,topx,topy,end;
    double y,x = popR(&top, &end, numchar);
    

    if (numchar[(int)x-1]==4 && x<=end && x>=0 && numchar[end+1]==6) 
    {
        top=simbDuasBarrasArr(x,end,top,stack,numchar);
    }
    else
    {
        top=end+1;
        if(numchar[top-1]==6)
        {
            top=trocaArrayComElem(x,end,top,stack,numchar);
        }
        else
        {
            if(numchar[top-1]==8)
            {
                top=trocaBlocoComElem(top,stack,numchar);                                        
            }
            else
            {
                if(numchar[top]==8)
                {
                    //são dois blocos
                    if (numchar[top-3]==8) swapd(stack, top-1,top-4);
                    else 
                    {
                        // é um elem e depois bloco
                        x=stack[top-3];
                        xi=numchar[top-3];
                        removeElemStack(stack,top,numchar,top-3);
                        pop(&top, stack);
                        pop(&top, stack);
                        push(1,&top,stack);
                        numchar[top]=8;
                        push(x, &top, stack);
                        numchar[top]=xi;
                    }
                }
                else
                {
                    if (numchar[top-1]==8) 
                    {
                        x=pop(&top,stack);
                        xi=numchar[top+1];
                        pop(&top, stack);
                        y=pop(&top, stack);
                        pop(&top,stack);
                        push(x,&top,stack);
                        numchar[top]=x;
                        push(1,&top,stack);
                        numchar[top]=7;
                        push(y,&top,stack);
                        numchar[top]=1;
                        push(1,&top,stack);
                        numchar[top]=8;
                    }
                    topx = top;
                    topy = top-1;
                    swap(numchar,topx, topy);
                    swapd(stack, topx, topy);  
                }                                      
            }
        }
    }
    return top;
}

/**
 * \brief Funções de recursivas e da stack
 *
 * @param *topSDepois Apontador para topS - topo da stackAux
 * @param a Indice do array n
 * @param n Array n recebido
 * @param top Top da Stack
 * @param topS Top da StackAux de strings
 * @param stack[] Stack recebida
 * @param numchar[] Array numchar recebido
 * @param stackAux[][] Stack de strings recebida
 * @param nSeguro String nSeguro recebida
 *
 * @return top Retorna topo da stack
 */
int funcoesrecursivas(int *topSDepois,int a, char n[],int top, int topS, double stack[], int numchar[], char stackAux[][10240], char nSeguro[])
{
    int topx, topy, topz;

    switch (n[a])
    {
        case '*':
            top=simbVezes(&topSDepois,top,topS,stack,numchar,stackAux,nSeguro);
            break;
                            
        case ',':
            top=simbVirgula(top,stack,numchar,stackAux,nSeguro);
            break;
                        
        case '%':
            top=simbPercentagem(top,stack,numchar,stackAux,nSeguro);
            break;

        case ';':

            top=pontoEVirgula(top,stack,numchar);
            break;
    

        case '_':

            top=duplicar(top,stack,numchar);
            break;
    
        case '\\' : 

            top=simbDuasBarras(top,stack,numchar);
            break;
    
        case '@' :

            topx = top;
            topy = topx-1;
            topz = topx-2;
    
            swap(numchar,topz, topy);
            swap(numchar,topy, topx);
    
            swapd(stack, topz, topy);
            swapd(stack, topy, topx);
    
            break;

    }
    return top;
}