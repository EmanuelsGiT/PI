#include <stdio.h>


//Ex.1.1
int contaVogais (char *s)
{
    int cont=0;

    while(s)
    {
        cont++;
    }

    return cont;
}

//Ex.1.2
int retiraVogaisRep (char *s)
{
    char aux[100];
    int cont = 0, j = 0;
    for (int i = 0; s[i]; i++)
    {
        if (s[i] != s[i+1])
        {
            aux[j] = s[i];
            j++;
            printf("aqui\n");
        }
        else
        {
            cont++;
        }
    }

    s = aux;
    return cont;
}

//Ex.1.3
int duplicaVogais (char *s)
{
    return 0;
}


//Ex.2
void dumpV (int v[], int N)
{
    int i;
    putchar ('{');
    for (i=0; i<N; i++) printf ("%2d ", v[i]);
    putchar ('}');
}

void simNao (int x)
{
    if (!x) printf (" não ");
}

//Ex.2.1
int ordenado (int a[], int N)
{
    return 0;
}

//Ex.2.2
void merge (int a[], int na, int b[], int nb, int r[])
{
    //...
}

//Ex.2.3
int partition (int v[], int N, int x)
{
    
    return 0;
}

int main() 
{  
    //Ex.1
    char s1 [100] = "Estaa e umaa string coom duuuplicadoos";
    int x;
    
    printf ("Testes\n");
    printf ("A string \"%s\" tem %d vogais\n", s1, contaVogais (s1));
    
    x = retiraVogaisRep (s1);
    printf ("Foram retiradas %d vogais, resultando em \"%s\"\n", x, s1);
    
    x = duplicaVogais (s1);
    printf ("Foram acrescentadas %d vogais, resultando em \"%s\"\n", x, s1);
    
    printf ("\nFim dos testes\n");
    
    
    //Ex.2
    int a [15] = {10, 3,45,56, 8,23,13,42,77,31,18,88,24,45, 1},
        b [10] = { 4,12,34,45,48,52,61,73,84,87}, 
        c [10] = { 1, 3, 8,22,33,35,38,41,44,49}, 
        d [50];
    int x;
    
    printf ("Testes\n\n");

    printf ("O array "); dumpV(a,15);
    simNao (ordenado (a,15)); printf (" está ordenado\n");
    printf ("O array "); dumpV(b,10);
    simNao (ordenado (b,10)); printf (" está ordenado\n");
    
    printf ("\n\nMerge dos arrays "); dumpV (b,10);
    printf ("\ne                "); dumpV (c,10); 
    merge (b, 10, c, 10, d);
    printf ("\nresulta em       "); dumpV (d,20);

    printf ("\n\n\nA partição do array  "); dumpV (a,15);
    printf ("\nusando 30 resulta em "); 
    x = partition (a,15,30); 
    dumpV (a,15); printf (" e retorna %d \n", x);

    printf ("\nFim dos testes\n");
    return 0;
}
