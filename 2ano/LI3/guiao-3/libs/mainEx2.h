#include <stdio.h>
#include "../libs/Tree.h"

NODE build_Tree(FILE* toread, NODE root);
int search_Tree(NODE root, int id, int n);
void freeTree(NODE root);
int check_calls (NODE root, int id);
void check_commits(NODE root_users, NODE root_repos, FILE* toread, FILE* towrite);
void check_repos(NODE root_users, NODE root_repos, FILE* toread, FILE* towrite);
int exercicio2();
