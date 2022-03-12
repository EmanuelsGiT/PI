#include <stdio.h>
#include <stdlib.h>
#include "../libs/guiao2.h"

void menu();
void submenu(int n,int n_users, QUERY* query);
int interfaceQ1();
int interfaceQ2();
int interfaceQ3();
int interfaceQ4();
int interfaceQ5(int n_users, char* data_inicio, char* data_fim, CATUSER catuser, CATCOMMITS catcommits);
int interfaceQ6(int n_users, char* linguagem, CATUSER catuser, CATREPOS catrepos, CATCOMMITS catcommits);
int interfaceQ7(char* data_inicio, CATREPOS catrepos, CATCOMMITS catcommits);
int interfaceQ8(int n_users, char* data_inicio, CATREPOS catrepos);
int interfaceQ9(int n_users);
int interfaceQ10(int n_users);

int interface();