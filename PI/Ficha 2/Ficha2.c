#include <stdio.h>

//Ex.1
float multInt1(int n, float m)
{
    int r = 0;

    for (int i = 0; i<n;i++)
        r+=m;

    return r;
}

//Ex.2
float multInt2(int n, float m)
{
    int r = 0;
    while (n!=1)
    {
        n=n/2;
        m=m*2;
        if (n%2!=0)
            r += m;
    }

    return r;
}

//Ex.3
int mdc1 (int a, int b)
{
    int aux;
    if (a<b)
    {
        aux = a;
        a = b;
        b = aux;
    }

    for(int i=1;i<=b;i++)
    {
        if(a%i==0 && b%i==0) aux = i;
    }

    return aux;
}


int main()
{
    multInt1(5, 2.5);
    multInt2(5, 2.5);
    mdc1(3,5);

}