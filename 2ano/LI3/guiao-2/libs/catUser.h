#include <stdio.h>
#include <glib.h>

typedef struct catUser *CATUSER;

CATUSER createCatUser(FILE* toread,char* buff,int max_len);
int getCatUserLength(CATUSER cat);
GHashTable* getCatUserHash(CATUSER cat);
USER getUserPointer(CATUSER cat, int i);