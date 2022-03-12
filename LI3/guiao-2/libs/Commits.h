#include <stdio.h>

typedef struct commits *COMMITS;

COMMITS build_commits2(char* line);
char* getCommitsCommit_at(COMMITS c);
int getCommitsLengthMessage(COMMITS c);
int getCommitsAuthorId(COMMITS c);
int getCommitsRepoId(COMMITS c);
int getCommitsCommitsId(COMMITS c);