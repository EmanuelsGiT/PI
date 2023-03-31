#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/queries_parameterizable.h"
#include "../libs/User.h"
#include "../libs/catUser.h"
#include "../libs/Commits.h"
#include "../libs/catCommits.h"
#include "../libs/Repos.h"
#include "../libs/catRepos.h"
#include "../libs/data.h"
#include "../libs/queriesAux.h"
#include <glib.h>


//Top N of users with more commits in a given date range
void query5(int n_users, char *data_inicio, char *data_fim, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output)
{
    DATA data_init = build_data(data_inicio);
    DATA data_final = build_data(data_fim);
    DATA data_commits;
    USER u;
    COUNTID cid;
    COMMITS commits;
    int id, i, length=getCatCommitsLength(catcommits), count=0;
    char aux[11];
    gpointer search = NULL;
    GArray *array = g_array_new( FALSE, FALSE, sizeof(COUNTID));
    GHashTable* users_count = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);

    for(i=0;i<length;i++)
    {
        commits=getCommitsPointer(catcommits,i);
        strcpy(aux,getCommitsCommit_at(commits));
        data_commits = build_data(aux);
        id = getCommitsAuthorId(commits);
        search = g_hash_table_lookup(users_count,GINT_TO_POINTER(id));
        count = GPOINTER_TO_INT(search) +1;
        if(compareData(data_init,data_commits)==1 && compareData(data_commits, data_final)==1)
            g_hash_table_insert(users_count,GINT_TO_POINTER(id), GINT_TO_POINTER(count));
    }

    g_hash_table_foreach(users_count, insereInArray, array);
    g_array_sort(array,cmpCommits);

    for(i=0;n_users!=0;n_users--,i++)
    {
        cid = g_array_index(array, COUNTID, i);
        u = g_hash_table_lookup(getCatUserHash(catuser), GINT_TO_POINTER(countIdId(cid)));
        fprintf(output,"%d;%s;%d\n", countIdId(cid), getUserLogin(u), countIdCount(cid));
    }

    free(data_init);
    free(data_final);
    g_array_free(array,TRUE);
    g_hash_table_destroy(users_count);
}

//Top‌ ‌N‌ of users with more commits in specific language's repositories 
void query6(int n_users, char *linguagem, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output)
{
    USER u;
    REPOS repo;
    COMMITS commits;
    COUNTID cid;
    int i, len, length = getCatCommitsLength(catcommits), count=0;
    char aux[21];             //Maior nome de linguagem minimamente popular que encontrei é classic visual basic
    gpointer search = NULL;
    gpointer id = NULL;
    GArray *array = g_array_new( FALSE, FALSE, sizeof(COUNTID));
    GHashTable* users_count = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);

    for(i=0;i<length;i++)
    {
        commits = getCommitsPointer(catcommits,i);
        repo = g_hash_table_lookup(getCatReposHash(catrepos), GINT_TO_POINTER(getCommitsRepoId(commits)));
        if(repo!=NULL)
        {
            strcpy(aux,getReposLang(repo));
            id = GINT_TO_POINTER(getCommitsAuthorId(commits));
            search = g_hash_table_lookup(users_count,id);
            count = GPOINTER_TO_INT(search) +1;
            if(strcmp(aux, linguagem) == 0)
                g_hash_table_insert(users_count,id, GINT_TO_POINTER(count));
        }
    }

    g_hash_table_foreach(users_count, insereInArray, array);
    g_array_sort(array,cmpCommits);
    len = g_hash_table_size(users_count);

    for(i=0;n_users!=0 && len!=0;n_users--,i++)
    {
        cid = g_array_index(array, COUNTID, i);
        u = g_hash_table_lookup(getCatUserHash(catuser), GINT_TO_POINTER(countIdId(cid)));
        fprintf(output, "%d;%s;%d\n", countIdId(cid), getUserLogin(u), countIdCount(cid));
    }

    g_array_free(array,TRUE);
    g_hash_table_destroy(users_count);
}

//Repositories's list without commits from a given date
void query7(char *data_inicio, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output)
{
    // Lista‌ ‌de‌ ‌repositórios‌ ‌sem‌ ‌commits‌ ‌a‌ ‌partir‌ ‌de‌ ‌uma‌ ‌determinada data
    DATA data_init = build_data(data_inicio);
    DATA data_commits;
    COMMITS commits;
    REPOS repos;
    char aux[11];
    int length = getCatCommitsLength(catcommits), count=0, id, i;
    gpointer search = NULL;
    GHashTable* repos_count = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);

    for(i=0;i<length;i++)
    {
        commits = getCommitsPointer(catcommits,i);
        strcpy(aux,getCommitsCommit_at(commits));
        data_commits = build_data(aux);
        id = getCommitsRepoId(commits);
        repos =  g_hash_table_lookup(getCatReposHash(catrepos),GINT_TO_POINTER(id));
        search = g_hash_table_lookup(repos_count,GINT_TO_POINTER(id));
        count = GPOINTER_TO_INT(search) +1;

        if(compareData(data_init,data_commits)==1)
            g_hash_table_insert(repos_count,repos, GINT_TO_POINTER(count));
        else
            g_hash_table_insert(repos_count,repos, GINT_TO_POINTER(0));
    }
    g_hash_table_foreach(repos_count, repoWithoutCommit, output);

    g_hash_table_destroy(repos_count);
}


//Top N of languages most used in a given date range
void query8(int n_users, char *data_inicio, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output)
{
    DATA data_init = build_data(data_inicio);
    DATA data_repos;
    REPOS repos;
    char lang[21];
    char aux[11];
    int i, length = getCatReposLength(catrepos), j=0;
    GArray *array = g_array_new( FALSE, FALSE, sizeof(COUNTLANG));

    for(i = 0; i < length; i++)
    {
        repos = getReposPointer(catrepos, i);
        strcpy(aux,getReposCreatedAt(repos));
        data_repos = build_data(aux);      
        if(compareData(data_init,data_repos)==1)
        {
            strcpy(lang, getReposLang(repos));
            j = searchLang(array,lang); // pos of lang -> -1 if doens't exists
            if(strcmp(lang,"None")!=0)
            {
                if(j==-1)
                    insereInArrayLang(array,lang);
                else 
                    addCount(array, j);
            }
        }        
    }
    g_array_sort(array,cmpCommitsLang);

    for(i=0;n_users!=0;n_users--,i++)
    {
        strcpy(lang,countLangLang(g_array_index(array, COUNTLANG, i)));
        fprintf(output,"%s\n",lang);
    }

    g_array_free(array,TRUE);
    free(data_init);
}


// Top N of users with more commits in repositories whose owner is a friend
void query9(int n_users, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output)
{
    USER user;
    COUNTID cid;
    COMMITS commits;
    REPOS repos;
    int i, count=0, ownerId, length = getCatCommitsLength(catcommits);
    char buff[9];
    gpointer search = NULL;
    gpointer id = NULL;
    GArray *array = g_array_new( FALSE, FALSE, sizeof(COUNTID));
    GHashTable* hashTop = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);

    for(i=0;i<length;i++)
    {
        commits = getCommitsPointer(catcommits,i);
        id = GINT_TO_POINTER(getCommitsAuthorId(commits));

        repos = g_hash_table_lookup(getCatReposHash(catrepos),GINT_TO_POINTER(getCommitsRepoId(commits)));
        if (repos != NULL)
        {
            ownerId = getReposOwnerId(repos);
            user = g_hash_table_lookup(getCatUserHash(catuser),id);
            sprintf(buff,"%d",ownerId);

            if (insideList(user,buff) == 1)
            {
                search = g_hash_table_lookup(hashTop,id);
                count = GPOINTER_TO_INT(search) + 1;
                g_hash_table_insert(hashTop,id, GINT_TO_POINTER(count));
            }
        }
    }

    g_hash_table_foreach(hashTop, insereInArray, array);
    g_array_sort(array,cmpCommits);

    for(i=0;n_users!=0;n_users--,i++)
    {
        cid = g_array_index(array, COUNTID, i);
        user = g_hash_table_lookup(getCatUserHash(catuser), GINT_TO_POINTER(countIdId(cid)));
        fprintf(output,"%d;%s\n", countIdId(cid), getUserLogin(user));
    }

    g_array_free(array,TRUE);
    g_hash_table_destroy(hashTop);
}

// Top N of users, sorted by size message‌ from‌ commit‌,‌ ‌in‌ ‌each‌ ‌repository
void query10(int n_users, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output)
{
    USER u;
    COMMITS commits;
    GHashTable* hashRepos = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
    GArray *array = NULL;
    int i, id, lenRepos = getCatReposLength(catrepos), lenCommits = getCatCommitsLength(catcommits);
    
    for(i=0;i<lenRepos;i++)
    {
        GArray *arrayx = g_array_new( FALSE, FALSE, sizeof(COUNTIDLOG));
        id = getReposId(getReposPointer(catrepos,i));
        g_hash_table_insert(hashRepos,GINT_TO_POINTER(id), arrayx);
    }

    for(i=0;i<lenCommits;i++)
    {
        commits = getCommitsPointer(catcommits,i);
        array = g_hash_table_lookup(hashRepos, GINT_TO_POINTER(getCommitsRepoId(commits)));
        u = g_hash_table_lookup(getCatUserHash(catuser), GINT_TO_POINTER(getCommitsAuthorId(commits)));
        insert(getCommitsAuthorId(commits), getCommitsLengthMessage(commits), getUserLogin(u), array);  
    }
    
    g_hash_table_foreach(hashRepos, sortArray, GINT_TO_POINTER(n_users));
    g_hash_table_foreach(hashRepos, printArray, output);

    g_array_free(array,TRUE);
    g_hash_table_destroy(hashRepos);
}
    