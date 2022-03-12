#include "../libs/catUser.h"
#include "../libs/Commits.h"
#include "../libs/catCommits.h"
#include "../libs/Repos.h"
#include "../libs/catRepos.h"
#include <glib.h>

void query2_2(FILE *catcommits, FILE *catrepos, FILE *output);
void query3_2(CATUSER catuser, FILE *catcommits, FILE *output);
void query5_2(int n_users, char *data_inicio, char *data_fim, CATUSER catuser, FILE *catcommits, FILE *output);
void query6_2(int n_users, char *linguagem, CATUSER catuser, FILE *catcommits, FILE *catrepos, FILE *output,GHashTable* hashIdRepos);
void insereInHashCountDesc(GHashTable* repos_count, int id, char *desc, int c);
void repoWithoutCommit_2(gpointer id, gpointer countDesc, void *output);
void query7_2(char *data_inicio, FILE *catcommits, FILE *catrepos, FILE *output, GHashTable* hashIdRepos);
void query8_2(int n_users, char *data_inicio, FILE *catrepos, FILE *output);
void query9_2(int n_users, CATUSER catuser, FILE *catcommits, FILE *catrepos, FILE *output,GHashTable* hashIdRepos);
void query10_2(int n_users, CATUSER catuser, FILE *catcommits, FILE *catrepos, FILE *output); 