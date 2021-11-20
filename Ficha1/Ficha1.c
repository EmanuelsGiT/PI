/*
    1.1
    x=3
    y=x+1 => y=4
    x=x*y => x=12
    y=x+y => y=16

    1.2
    x=0
    y=0

    1.3
    A 65
    B 66 2 50
    b 98

    1.4
    x=100 
    y=200


    2.1
    x=3
    y=5

    2.2
    x=11
    y=66

    2.3
    _#_#_#_#_#_#_#_#_#_#

    2.4
    1
    01
    11
    001
    101
    011
    111
    0001
    1001
    0101
    1101
    0011
    1011
    0111
    1111
*/

#include <stdio.h>

int ex1(int n)
{
    for (int i = 0; i<n; i++)
    {
        for (int j = 0; j<n; j++)
            printf("#"); 
        printf("\n");
    }

    return 0; 
}

int ex2(int n)
{
    for (int i=0; i<n; i++)
    {
        if (i%2==0)
        {
            for(int j=0; j<n; j++) 
            {
                if (j%2==0) printf("#");
                else printf("_");
                
            }
        }
        else
        {
            for(int k=0; k<n; k++) 
            {
                if (k%2==0) printf("_");
                else printf("#");
            }
        }
        printf("\n");
    }
    return 0;
}

int ex3(int n)
{
    int i=0, j=1, k=0;
    while (k<n)
    {
        for (i=0; i<j; i++) printf("#");
        printf("\n");
        j++;
        k++;
    }
    k--;
    j = k;
    while (k)
    {
        for (i=0; i<j; i++) printf("#");
        printf("\n");
        j--;
        k--;
    }
    
    return 0;
}


int main()
{
    ex1(5);
    ex2(5);
    ex3(5);

    return 0;
}

