#include <stdio.h>
#include "../libs/User.h"
#include "../libs/Repos.h"
#include <glib.h>

typedef struct countId *COUNTID;

int cmpCommits(const void* first, const void* second);
void insereInArray(gpointer user_id, gpointer count, void *array);
void repoWithoutCommit(gpointer repos, gpointer count, void *output);
int insideList(USER user, char* ownerId);
int countIdCount(COUNTID c);
int countIdId(COUNTID c);

////////////////////////////////////////////////////////////////////////

typedef struct countLang *COUNTLANG;

void insereInArrayLang(GArray *array, char *language);
int searchLang(GArray *array, char *language);
void addCount(GArray *array, int j);
int countLangCount(COUNTLANG c);
char* countLangLang(COUNTLANG c);

////////////////////////////////////////////////////////////////////////

typedef struct countIdLog *COUNTIDLOG;

void sortArray(gpointer id, gpointer array, void *n_users);
void printArray(gpointer id, gpointer array, void *output);
void insert(int id, int count, char* login, GArray *array);


int cmpCommits2(const void* first, const void* second);
void sortArrayQ(gpointer id, gpointer arrayx, gpointer sum);

int cmpCommitsLang(const void* first, const void* second);