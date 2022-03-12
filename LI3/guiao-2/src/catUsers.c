#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libs/User.h"
#include "../libs/catUser.h"
#include <glib.h>

struct catUser
{
    USER* user;
    GHashTable* users_id;
    int length;
};

CATUSER createCatUser(FILE* toread,char* buff,int max_len)
{
    CATUSER result = malloc(sizeof(struct catUser));
    int length=100;
    result->user=malloc(sizeof(struct catUser)*length);
    result->users_id = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
    int i=0;
    fgets(buff, max_len, toread);
    while(fgets(buff, max_len, toread))
    {
        if(i>=length)
        {
            length*=2;
            result->user = realloc(result->user,sizeof(struct catUser)*length);
        }
        result->user[i] = build_user2(buff);
        g_hash_table_insert(result->users_id,GINT_TO_POINTER(getUserId(result->user[i])),result->user[i]);
        i++;
    }
    result->length=i;
    return result;
}

int getCatUserLength(CATUSER cat){return cat->length;}
GHashTable* getCatUserHash(CATUSER cat){return cat->users_id;}
USER getUserPointer(CATUSER cat, int i){return cat->user[i];} //get specific USER