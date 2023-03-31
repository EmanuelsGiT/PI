#include "../libs/Repos.h"
#include "../libs/catRepos.h"
#include <stdio.h>
#include <glib.h>

struct catRepos
{
    REPOS* repos;
    GHashTable* repos_id;
    int length;
};

CATREPOS createCatRepos(FILE* toread,char* buff,int max_len)
{
    int i=0, length=100;
    CATREPOS result = malloc(sizeof(struct catRepos));
    result->repos=malloc(sizeof(struct catRepos)*length);
    result->repos_id = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
    fgets(buff, max_len, toread);
    while(fgets(buff, max_len, toread))
    {
        if(i>=length)
        {
            length*=2;
            result->repos = realloc(result->repos,sizeof(struct catRepos)*length);
        }
        result->repos[i] = build_repos2(buff);
        g_hash_table_insert(result->repos_id,GINT_TO_POINTER(getReposId(result->repos[i])),result->repos[i]);
        i++;
    }
    result->length = i;
    return result;
}

int getCatReposLength(CATREPOS cat){return cat->length;}
GHashTable* getCatReposHash(CATREPOS cat){return cat->repos_id;}
REPOS getReposPointer(CATREPOS cat, int i){return cat->repos[i];} //get specific REPOS