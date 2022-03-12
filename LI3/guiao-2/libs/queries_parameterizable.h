#include <glib.h>
#include "../libs/User.h"
#include "../libs/catUser.h"
#include "../libs/Commits.h"
#include "../libs/catCommits.h"
#include "../libs/Repos.h"
#include "../libs/catRepos.h"

void query5(int n_users, char *data_inicio, char *data_fim, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output);
void query6(int n_users, char *linguagem, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output);
void query7(char *data_inicio, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output);
void query8(int n_users, char *data_inicio, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output);
void query9(int n_users, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output);
void query10(int n_users, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output); 