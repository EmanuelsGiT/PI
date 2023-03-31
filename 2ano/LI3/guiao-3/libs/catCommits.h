#include <stdio.h>

typedef struct catCommits *CATCOMMITS;

CATCOMMITS createCatCommits(FILE* toread,char* buff,int max_len);
int getCatCommitsLength(CATCOMMITS cat);
COMMITS getCommitsPointer(CATCOMMITS cat, int i);

void freeCatCommits(CATCOMMITS catcommits);

int saveCatCommmitsInFile(CATCOMMITS cat);
int saveCatCommmitsInFile2(FILE* toread,char* buff,int max_len);