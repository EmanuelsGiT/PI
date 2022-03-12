#include <stdio.h>

typedef struct catquery* CATQUERY;

CATQUERY createCatQuery(FILE* toread,char* buff,int max_len, int n);
QUERY getQueryPointer(CATQUERY cat, int i);
int getCatQueryLength(CATQUERY cat);
void freeCatQuery(CATQUERY catquery);