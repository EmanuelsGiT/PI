#include <stdio.h>
#include <glib.h>

typedef struct catRepos *CATREPOS;

CATREPOS createCatRepos(FILE* toread,char* buff,int max_len);
int getCatReposLength(CATREPOS cat);
GHashTable* getCatReposHash(CATREPOS cat);
REPOS getReposPointer(CATREPOS cat, int i);
void freeCatRepos(CATREPOS catrepos);

void swapRepos(int* a, int* b, REPOS *x, REPOS *y);
int partitionRepos (int arr[], int low, int high, REPOS *repos);
void quickSortRepos(int arr[], int low, int high, REPOS *repos);
void saveCatReposInFile(FILE* toread, char* buff, int max_len, FILE* fcatRepos, GHashTable* hashIdRepos);

int createArrayIdRepos(int* idRepos);
int binarySearch(int *idRepos, int len, int item);
void findRepo(GHashTable* hashIdRepos, int repo, REPOS r, FILE *catrepos, char* str);