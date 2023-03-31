#include <stdio.h>
#include <stdlib.h>

#define Max 100

typedef struct staticStack
{
    int sp;
    int values [Max];
} STACK, *SStack;

typedef struct staticQueue
{
    int front;
    int length;
    int values[Max];
} QUEUE, *SQueue;

typedef struct dinStack 
{
    int size; // guarda o tamanho do array values
    int sp;
    int *values;
} *DStack;

typedef struct dinQueue
 {
    int size; // guarda o tamanho do array values
    int front;
    int length;
    int *values;
} *DQueue;

// Static stacks 
void SinitStack (SStack s)
{

	// ...
}

int  SisEmpty (SStack s)
{
	return 1;
}

int  Spush (SStack s, int x)
{
	int r = 0;
	
	return r;
}

int  Spop (SStack s, int *x) 
{
	int r=0;
	
	return r;
}

int  Stop (SStack s, int *x) 
{
	int r=0;
	
	return r;
}

void ShowSStack (SStack s)
{
    int i;
    printf ("%d Items: ", s->sp);
    for (i=s->sp-1; i>=0; i--) 
        printf ("%d ", s->values[i]);
    putchar ('\n');
}

// Stacks with dynamic arrays
int dupStack (DStack s) 
{
	int r = 0, i;
	int *t = malloc (2*s->size*sizeof(int));

	if (t == NULL) r = 1;
	else 
    {
		for (i=0; i<s->size; i++) 
			t[i] = s->values[i];
		free (s->values);
		s->values = t;
		s->size*=2;
	}
	return r;
}

void DinitStack (DStack s) 
{
	
}

int  DisEmpty (DStack s)
{
	return 1;
}

int  Dpush (DStack s, int x)
{
	int r=0;
	
	return r;
}

int  Dpop (DStack s, int *x)
{
	int r=0;
	
	return r;
}

int  Dtop (DStack s, int *x)
{
	int r=0;
	
	return r;
}

void ShowDStack (DStack s)
{
    int i;
    printf ("%d Items: ", s->sp);
    for (i=s->sp-1; i>=0; i--) 
        printf ("%d ", s->values[i]);
    putchar ('\n');
}


// Static queues 
void SinitQueue (SQueue q)
{
	// ...
}

int  SisEmptyQ (SQueue q)
{
    // ...
	return (-1);
}

int  Senqueue (SQueue q, int x)
{
	// ...
	return (-1);
}

int  Sdequeue (SQueue q, int *x) 
{
	// ...
	return (-1);
}

int  Sfront (SQueue q, int *x) 
{
	// ...
	
	return (-1);
}

void ShowSQueue (SQueue q)
{
    int i, p;
    printf ("%d Items: ", q->length);
    for (i=0, p=q->front; i<q->length; i++) 
    {
        printf ("%d ", q->values[p]);
        p = (p+1)%Max;
    }
    putchar ('\n');
}

// Queues with dynamic arrays

int dupQueue (DQueue q) 
{
	// ...
	return (-1);
}

void DinitQueue (DQueue q) 
{
	// ...
}

int  DisEmptyQ (DQueue s) 
{
	return (-1);
}

int  Denqueue (DQueue q, int x)
{
	// ...
	return (-1);
}

int  Ddequeue (DQueue q, int *x)
{
	// ...
	return (-1);
}

int  Dfront (DQueue q, int *x)
{
	// ...
	return (-1);
}

void ShowDQueue (DQueue q)
{
    int i, p;
    printf ("%d Items: ", q->length);
    for (i=0, p=q->front; i<q->length; i++) 
    {
        printf ("%d ", q->values[p]);
        p = (p+1)%q->size;
    }
    putchar ('\n');
}


int main() 
{
    int i ; 
    struct staticStack s1;
    SStack S1 = &s1;
    struct dinStack d1;
    DStack D1 = &d1;    

    struct staticQueue q1;
    SQueue Q1 = &q1;
    struct dinQueue r1;
    DQueue R1 = &r1;

    printf ("Testing Stacks .... \n");
    SinitStack (S1);
    DinitStack (D1);
    for (i=0; i<15; i++) 
    {
        if (Spush (S1,i) != 0) printf ("ERROR pushing %d\n", i);
        if (Dpush (D1,i) != 0) printf ("ERROR pushing %d\n", i);
    }
    ShowSStack (S1);
    ShowDStack (D1);

    printf ("Testing Queues .... \n");
    SinitQueue (Q1);
    DinitQueue (R1);
    for (i=0; i<15; i++) 
    {
        if (Senqueue (Q1,i) != 0) printf ("ERROR enqueueing %d\n", i);
        if (Denqueue (R1,i) != 0) printf ("ERROR enqueueing %d\n", i);
    }
    ShowSQueue (Q1);
    ShowDQueue (R1);  
      
    return 0;
} 