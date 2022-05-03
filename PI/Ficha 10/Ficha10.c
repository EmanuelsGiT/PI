#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodo 
{
    int valor;
    struct nodo *esq, *dir;
} *ABin;

ABin newABin (int r, ABin e, ABin d) 
{
   ABin a = malloc (sizeof(struct nodo));
   if (a!=NULL) 
   {
      a->valor = r; a->esq = e; a->dir = d;
   }
   return a;
}

ABin RandArvFromArray (int v[], int N) 
{
   ABin a = NULL;
    int m;
    if (N > 0)
    {
    	m = rand() % N;
    	a = newABin (v[m], RandArvFromArray (v,m), RandArvFromArray (v+m+1,N-m-1));
    }
    return a;	
}


// Questão 1
ABin removeMenor (ABin *a)
{
    return NULL;
}

void removeRaiz (ABin *a)
{
}

int removeElem (ABin *a, int x)
{
    return (-1);
}

// Questão 2
void rodaEsquerda (ABin *a)
{
    ABin b = (*a)->dir;
    (*a)->dir = b->esq;
    b->esq = (*a);
    *a = b;
}
void rodaDireita (ABin *a)
{
    ABin b = (*a)->esq;
    (*a)->esq = b->dir;
    b->dir = *a;
    *a = b;
}
void promoveMenor (ABin *a)
{
}
void promoveMaior (ABin *a)
{
}
ABin removeMenorAlt (ABin *a)
{
    return NULL;
}

// Questão 3
int constroiEspinhaAux (ABin *a, ABin *ult)
{
    return (-1);
}
int constroiEspinha (ABin *a)
{
    ABin ult;
    return (constroiEspinhaAux (a,&ult));
}

ABin equilibraEspinha (ABin *a, int n) 
{
	return NULL;
}

void equilibra (ABin *a) 
{
}


int main ()
{
    int v1[15] = { 1, 3, 5, 7, 9,11,13,15,17,19,21,23,25,27,29},
        N=15, i;
    ABin a1,r;

    srand(time(NULL));

    printf ("_______________ Testes _______________\n\n");
    // N = rand() % 16;
    a1 = RandArvFromArray (v1, N);
    printf ("________________________________________\n");
    printf ("Primeira árvore de teste (%d elementos)\n", N);
    //dumpABin (a1, N);

    /*
    printf ("Espinha\n");
    constroiEspinha_sol (&a1);

    dumpABin (a1, N);

    printf ("Equilibrar espinha\n");
    equilibraEspinha_sol (&a1,N);
    dumpABin (a1, N);
    */

    i = rand() %N;
    printf ("Remoção do elemento %d\n", v1[i]);
    //removeElem_sol (&a1,v1[i]);
    //dumpABin (a1, --N);


    //r = removeMenor_sol (&a1);
    printf ("Remoção do menor %d\n", r->valor);
    //dumpABin (a1, --N);

    printf ("Remoção da raiz %d\n", a1->valor);
    //removeRaiz_sol (&a1);
    //dumpABin (a1, --N);

    //freeABin (a1);

    a1 = newABin(v1[7], RandArvFromArray (v1  ,7), 
                        RandArvFromArray (v1+8,7));
    N = 15;
    printf ("_______________________________________\n");
    printf ("Segunda árvore de teste (%d elementos)\n", N);
    //dumpABin (a1, N);

    printf ("Rotação à direita\n");
    rodaDireita (&a1);
    //dumpABin (a1, N);

    printf ("Rotação à esquerda\n");
    rodaEsquerda (&a1);
    //dumpABin (a1, N);

    printf ("Promoção do maior\n");
    //promoveMaior_sol (&a1);
    //dumpABin (a1, N);

    printf ("Promoção do menor\n");
    //promoveMenor_sol (&a1);
    //dumpABin (a1, N);


    printf ("\n\n___________ Fim dos testes ___________\n\n");
    return 0;
} 