#include <stdio.h>
#include "../libs/User.h"
#include "../libs/Repos.h"
#include "../libs/data.h"
#include <glib.h>

typedef struct countId *COUNTID;
typedef struct countLang *COUNTLANG;
typedef struct countIdLog *COUNTIDLOG;


void getType(gpointer idx, gpointer userx, gpointer sumx);

int cmpCommits2(const void* first, const void* second);
void sortArrayQ(gpointer id, gpointer arrayx, gpointer sum);
void freeHashOfGArrays(gpointer arrayx);

int cmpCommits(const void* first, const void* second);
void insereInArray(gpointer user_id, gpointer count, void *array);
int countIdCount(COUNTID c);
int countIdId(COUNTID c);

void repoWithoutCommit(gpointer repos, gpointer count, void *output);

void insereInArrayLang(GArray *array, char *language);
int searchLang(GArray *array, char *language);
void addCount(GArray *array, int j);
int cmpCommitsLang(const void* first, const void* second);
int countLangCount(COUNTLANG c);
char* countLangLang(COUNTLANG c);

int insideList(USER user, char* ownerId);

void insert(int id, int count, char* login, GArray *array);
void sortArray(gpointer id, gpointer array, void *n_users);
void printArray(gpointer id, gpointer array, void *output);
void freeCountIdLog (COUNTIDLOG cid);