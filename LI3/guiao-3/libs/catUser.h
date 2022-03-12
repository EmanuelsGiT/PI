#include <stdio.h>
#include <glib.h>

typedef struct catUser *CATUSER;

CATUSER createCatUser(FILE* toread,char* buff,int max_len);
int getCatUserLength(CATUSER cat);
GHashTable* getCatUserHash(CATUSER cat);

void freeCatUser(CATUSER catuser);

void saveCatUserInFileAux(gpointer idx, gpointer userx, gpointer out);
int saveCatUserInFile(CATUSER cat);