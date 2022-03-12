#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libs/Commits.h"

struct commits
{
    int repo_id;
    int author_id;
    int committer_id;
    char* commit_at;
    int lenMessage;
};

COMMITS build_commits2(char* line)
{
    COMMITS u = malloc(sizeof(struct commits));
    char* buff2 = line;
    u->repo_id = atoi(strsep(&buff2, ";\n"));
    u->author_id = atoi(strsep(&buff2, ";\n"));
    u->committer_id = atoi(strsep(&buff2, ";\n"));
    u->commit_at = strdup (strsep(&buff2, ";\n"));
    u->lenMessage = strlen(strsep(&buff2, ";\n"));
    
    return u;
}

int getCommitsRepoId(COMMITS c) {return c->repo_id;}
int getCommitsAuthorId(COMMITS c) {return c->author_id;}
int getCommitsCommitsId(COMMITS c) {return c->committer_id;}
char* getCommitsCommit_at(COMMITS c) {return strdup(c->commit_at);}
int getCommitsLengthMessage(COMMITS c) {return c->lenMessage;}

void freeCommits (COMMITS u)
{
    free(u->commit_at);
    free(u);
}