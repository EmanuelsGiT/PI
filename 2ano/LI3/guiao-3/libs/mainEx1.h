#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getIntLen (int x);
int check(char *validated);
int find_errors(char *buff, int n);
int inArray(int elem, int array[], int tam);
int check_Time(char* time);
int check_list(int follow, char *validated);
int build_user(char* line,FILE* out);
int build_commits(char* line,FILE* out);
int build_repos(char* line,FILE* out);
int build_main(FILE* toread, FILE* towrite, int n);
int exercicio1();
