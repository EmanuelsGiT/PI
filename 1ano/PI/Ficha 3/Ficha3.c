#include <stdio.h>


//Ex.1
/*
a)

1 1 4
2 2 6
3 3 8
4 4 10
5 5 12

b)
13
*/

//Ex.2
void swapM(int *x, int *y)
{
    int aux;
    aux = *x;
    x = y;
    y = &aux; 
}

//Ex.3
void swap(int v[], int i, int j)
{
    int aux;
    aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

//Ex.4
int soma(int v[], int N)
{
    int soma;

    for (int i = 0; i < N; i++)
    {
        soma += v[i];
    }
    
    return soma;
}

//Ex.5
void inverteArray (int v[], int N)
{
    for(int i=0;i<N;i++)
        swap(v,i,N-i-1);
}

//Ex.6
int maximum(int v[], int N, int *m)
{
    if (N<0) return -1;
    int aux=0;

    for (int i = 1; i < N; i++)
    {
        if (v[aux]<v[i]) aux = i;
    }

    m = &v[aux];
    
    return 0;
}

//Ex.7
void quadrados(int q[], int N)
{
    for (int i = 0; i < N; i++)
    {
        q[i] = i*i;
    }
}

int main()
{
    int x=3, y=5;
    swapM(&x,&y);
    printf("%d %d\n", x,y);

    return 0;
}