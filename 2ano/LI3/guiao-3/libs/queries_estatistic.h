#include "../libs/catUser.h"
#include "../libs/Commits.h"
#include "../libs/catCommits.h"
#include "../libs/Repos.h"
#include "../libs/catRepos.h"
#include <glib.h>

void query1(CATUSER catuser, FILE *output);
void query2(CATCOMMITS catcommits, CATREPOS catrepos, FILE *output);
void query3(CATUSER catuser, CATCOMMITS catcommits, FILE *output);
void query4(FILE *output);