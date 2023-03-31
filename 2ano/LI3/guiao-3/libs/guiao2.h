#include <stdio.h>
#include "../libs/Commits.h"
#include "../libs/Repos.h"
#include "../libs/catUser.h"
#include "../libs/catCommits.h"
#include "../libs/catRepos.h"
#include "../libs/queries_estatistic.h"
#include "../libs/queries_parameterizable.h"

int createCats(CATUSER *catuser, CATREPOS *catrepos, CATCOMMITS *catcommits);
void execute(char* line, CATUSER catuser, CATREPOS catrepos, CATCOMMITS catcommits);
int q1To4Plus9And10(int query_id, char *buff, char *buff2, FILE *file);
int createOut(CATUSER catuser, CATREPOS catrepos, CATCOMMITS catcommits, FILE *fcommands);
int guiao2();