#include <stdio.h>
#include <math.h>
#include <strcmp.h>

typedef struct aluno {
    int numero;
    char nome[100];
    int miniT [6];
    float teste;
} Aluno;

//////////////////////////////////
//Ex.1
int nota (Aluno a) {
    int s = 0, i, reprova=0;
    float m;
    int final;
    for(i=0; i<6;i++) {
        s += a.miniT[i];
    }

    m = ((float) s)*20/12;
    final = round((m*0.3) + (a.teste *0.7));

    if (m<8 || a.teste<8 || final<10) final =0;
    
    return final;
}

int procuraNum (int num, Aluno t[], int N) {
    int i=0, r=N-1, mid;
    while (r>l) {
        mid = (l+r)/2:
        if /t[mid].numero >= num)
            r=mid
        else l = mid+1
    }
    while (i<N && t[i].numero<num) i++;
    if (i==N) t[i]=.numero!=num) i=-1;

    return i;
}

////////////////////////////////////////

int bubble (Aluno t[], int N) {
    int i, r=0;
    for (i=0;i<N-i;i++) {
        if (t[i].nummero>t[i+1].numero) {swap(t,i,i+1); r++};
    }
    return r;
}

void swap(Aluno t[],int i, int j) {
    Aluno aux;
    aux = t[i];
    t[i] = t[j];
    t[j] = aux;
}
////////////////////////////////////////

void ordenaPorNum (Aluno t [], int N) {
    while (bubble(t,N)) N--;
}

int procuraNumInd (int num, int ind[], Aluno t[], int N) {
    int l=0, r=N-1,mid;
    while (r>l) {
        mid = (l+r)/2;
        if(t[ind[mid]].numero >= num)
            r =mid;´´
        elsel= mid + 1;
    }
    if(t[ind[l]].numero==num)
}

void swapI(int a[], int i, int j) {
    int aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}

void criaIndPorNum (Aluno t [], int N, int ind[]) {
    int i, j, min;
    for (i=0; i<N; i++) ind[i] = i;
    for (i=0, i<N; i++) {
        min=i;
        for (j=i+1; j<N; j++) {
            if (t[ind[j]].numero < t[ind[min]].numero) min = j;
        }
        swapI(ind, i, min);
    }
}


void criaIndPorNome (Aluno t [], int N, int ind[]) {
    int i, j, min;
    for (i=0; i<N; i++) ind[i] = i;
    for (i=0, i<N; i++) {
        min=i;
        for (j=i+1; j<N; j++) {
            if (strcmp(t[ind[j]].nome, t[ind[min]].nome)<0) min = j;
        }
        swapI(ind, i, min);
    }
}
}

void imprimeTurmaInd (int ind[], Aluno t[], int N) {
    int i;
    for (i=0; i<N; i++) imprimeAluno(t+ind[i]);
}


/////////////////////////////////

void dumpV (int v[], int N) {
    int i;
    for (i=0; i<N; i++) printf ("%d ", v[i]);
}

void imprimeAluno (Aluno *a) {
    int i;
    printf ("%-5d %s (%d", a->numero, a->nome, a->miniT[0]);
    for(i=1; i<6; i++) printf (", %d", a->miniT[i]);
    printf (") %5.2f %d\n", a->teste, nota(*a));
}

int nota (Aluno a){
    return 0;
}

int procuraNum (int num, Aluno t[], int N){
    return -1;
}

void ordenaPorNum (Aluno t [], int N) {}

int procuraNumInd (int num, int ind[], Aluno t[], int N) {
    return -1;
}

void criaIndPorNum (Aluno t [], int N, int ind[]) {}

void criaIndPorNome (Aluno t [], int N, int ind[]) {}

void imprimeTurmaInd (int ind[], Aluno t[], int N) {}

int main() {
    Aluno Turma1 [7] = {{4444, "André", {2,1,0,2,2,2}, 10.5}
                       ,{6666, "Bruna", {2,2,2,1,0,0}, 12.5}
                       ,{8888, "Carla", {2,1,2,1,0,1}, 14.5}
                       ,{5555, "Diogo", {2,2,1,1,1,0},  8.5}
                       ,{2222, "Joana", {2,0,2,1,0,2},  3.5}
                       ,{7777, "Maria", {2,2,2,2,2,1},  5.5}
                       ,{3333, "Paulo", {0,0,2,2,2,1},  8.7}
                       } ;
    int indNome [7], indNum [7];
    int i;
    
    printf ("\n-------------- Testes --------------\n");
    
    ordenaPorNum (Turma1, 7);
    printf ("procura 5555: %d \n", procuraNum (5555, Turma1, 7));
    printf ("procura 9999:%d \n", procuraNum (9999, Turma1, 7));

    for (i=0; i<7; imprimeAluno (Turma1 + i++));
    
    // criaIndPorNum (Turma1, 7, indNum);
    
    // printf ("procura 5555:%d \n",  procuraNumInd (5555, indNum, Turma1, 7));
    // printf ("procura 9999:%d \n",  procuraNumInd (9999, indNum, Turma1, 7));

    // criaIndPorNome (Turma1, 7, indNome);

    // imprimeTurmaInd (indNum, Turma1, 7);
    // imprimeTurmaInd (indNome, Turma1, 7);

    printf ("\n---------- Fim dos Testes ----------\n");
    
    return 0;
}
