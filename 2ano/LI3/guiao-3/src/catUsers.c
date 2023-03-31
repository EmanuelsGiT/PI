#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libs/User.h"
#include "../libs/catUser.h"
#include <glib.h>

struct catUser
{
    GHashTable* users_id;
    int length;
};

CATUSER createCatUser(FILE* toread,char* buff,int max_len)
{
    CATUSER result = malloc(sizeof(struct catUser));
    result->users_id = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,freeUser);
    int i=0;
    USER u = NULL;
    int id;
    fgets(buff, max_len, toread);
    while(fgets(buff, max_len, toread))
    {
        u = build_user2(buff,&id);
        g_hash_table_insert(result->users_id,GINT_TO_POINTER(id),u);
        i++;
    }
    result->length=i;

    return result;
}

int getCatUserLength(CATUSER cat){return cat->length;}
GHashTable* getCatUserHash(CATUSER cat){return cat->users_id;}


void freeCatUser(CATUSER catuser)
{
    g_hash_table_destroy (catuser->users_id);
    free(catuser);
}

void saveCatUserInFileAux(gpointer idx, gpointer userx, gpointer out)
{
    USER u = userx;
    FILE *output = out;
    fprintf(output, "%d;%s;%s;%s;%s", getUserId(u), getUserLogin(u), getUserType(u), getUserFollowersList(u), getUserFollowingList(u));
}

int saveCatUserInFile(CATUSER cat)
{
    FILE *fcatUser = fopen("saida/catUser.txt", "w");
    if(fcatUser==NULL) return -1;
    g_hash_table_foreach(cat->users_id, saveCatUserInFileAux, fcatUser);
    return 0;
} 