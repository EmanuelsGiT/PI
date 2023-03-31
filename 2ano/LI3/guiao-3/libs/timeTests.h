#include <stdio.h>
#include <stdio.h>
#include "../libs/queries_estatistic.h"
#include "../libs/User.h"
#include "../libs/catUser.h"
#include "../libs/Commits.h"
#include "../libs/catCommits.h"
#include "../libs/Repos.h"
#include "../libs/catRepos.h"
#include "../libs/queriesAux.h"
#include <glib.h>
#include <time.h>

double testQ1 (CATUSER catuser);
double testQ2 (CATCOMMITS catcommits, CATREPOS catrepos);
double testQ3 (CATUSER catuser, CATCOMMITS catcommits);
double testQ4 ();
double testQ5 (int n_users, char *data_inicio, char *data_fim, CATUSER catuser, CATCOMMITS catcommits);
double testQ6 (int n_users, char *linguagem, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos);
double testQ7 (char *data_inicio, CATCOMMITS catcommits, CATREPOS catrepos);
double testQ8 (int n_users, char *data_inicio, CATREPOS catrepos);
double testQ9 (int n_users, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos);
double testQ10 (int n_users, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos);

void testAll (CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, int test[]);
void testAllNTimes (CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos);

int testQuery (CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, int QueryID, int target);

int time_UI(CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos);
int compareFiles(FILE *f1, FILE *f2);
int tester_UI(CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos);
int testMain();
