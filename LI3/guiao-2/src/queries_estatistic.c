#include <stdio.h>
#include "../libs/queries_estatistic.h"
#include "../libs/User.h"
#include "../libs/catUser.h"
#include "../libs/Commits.h"
#include "../libs/catCommits.h"
#include "../libs/Repos.h"
#include "../libs/catRepos.h"
#include "../libs/queriesAux.h"
#include <glib.h>

//Number of bots‌,‌ ‌organizations ‌and user of specific user
void query1(CATUSER catuser, FILE *output)
{   
    int user_count = 0, bot_count = 0, org_count = 0, i;
    int length = getCatUserLength(catuser);

    for(i = 0; i < length; i++)
    {
        if(strcmp(getUserType(getUserPointer(catuser,i)), "User") == 0) user_count++;
        else if(strcmp(getUserType(getUserPointer(catuser,i)), "Organization") == 0) org_count++;        
        else bot_count++;
    }

    fprintf(output, "Bot: %d\nOrganization: %d\nUser: %d", bot_count, org_count, user_count);
}

//Estimates the average of collaborators per repository
void query2(CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output)
{   
    int a, b, r = 0, id, lenRepos = getCatReposLength(catrepos), length = getCatCommitsLength(catcommits), i;
    float trepos = getCatReposLength(catrepos);
    COMMITS commits;
    GHashTable* hashRepos = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
    GArray *array = NULL;
    GArray *sum = g_array_new( FALSE, TRUE, sizeof(int));

    for(i=0;i<lenRepos;i++)
    {
        GArray *arrayx = g_array_new( FALSE, FALSE, sizeof(int));
        id = getReposId(getReposPointer(catrepos,i));
        g_hash_table_insert(hashRepos,GINT_TO_POINTER(id), arrayx);
    }

    for(i=0;i<length;i++)
    {
        commits = getCommitsPointer(catcommits,i);

        array = g_hash_table_lookup(hashRepos, GINT_TO_POINTER(getCommitsRepoId(commits)));
        a = getCommitsAuthorId(commits);
        g_array_append_val(array, a);
        b = getCommitsCommitsId(commits);
        g_array_append_val(array, b);
    }
    g_hash_table_foreach(hashRepos, sortArrayQ, sum);
    length = sum->len;
    for(i=0;i<length;i++)
        r+=g_array_index(sum, int, i);
    fprintf(output, "%.2f", r / trepos);

    g_array_free(array,TRUE);
    g_array_free(sum,TRUE);
    g_hash_table_destroy(hashRepos);
}

//Number of repositories ‌contendo‌ bots‌‌ ‌como‌ ‌colaboradores
void query3(CATUSER catuser,  CATCOMMITS catcommits, FILE *output)
{   
    int i, length = getCatCommitsLength(catcommits);
    USER user1, user2;
    COMMITS commits;
    GHashTable* repoBot_count = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);

    for(i=0;i<length;i++)
    {
        commits = getCommitsPointer(catcommits,i);
        user1 = g_hash_table_lookup(getCatUserHash(catuser),GINT_TO_POINTER(getCommitsAuthorId(commits)));
        user2 = g_hash_table_lookup(getCatUserHash(catuser),GINT_TO_POINTER(getCommitsCommitsId(commits)));
        
        if((user1!=NULL && strcmp(getUserType(user1),"Bot")==0))
            g_hash_table_insert(repoBot_count,GINT_TO_POINTER(getCommitsAuthorId(commits)),GINT_TO_POINTER(1));

        if((user2!=NULL && strcmp(getUserType(user2),"Bot")==0))
            g_hash_table_insert(repoBot_count,GINT_TO_POINTER(getCommitsCommitsId(commits)),GINT_TO_POINTER(1));
    }

    fprintf(output, "%d", g_hash_table_size(repoBot_count));

    g_hash_table_destroy(repoBot_count);
}

void query4(CATUSER catuser, CATCOMMITS catcommits, FILE *output)
{
    float r = (float)getCatCommitsLength(catcommits) / getCatUserLength(catuser);
    fprintf(output, "%.2f", r);
}
