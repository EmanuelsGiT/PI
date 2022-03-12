/**
 * @file Parameterizable queries' functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/queries_parameterizable.h"
#include "../libs/catUser.h"
#include "../libs/Commits.h"
#include "../libs/catCommits.h"
#include "../libs/Repos.h"
#include "../libs/catRepos.h"
#include "../libs/data.h"
#include "../libs/queriesAux.h"
#include <glib.h>


/**
 * \brief Top N of users with more commits in a given date range
 */
void query5(int n_users, char *data_inicio, char *data_fim, CATUSER catuser, CATCOMMITS catcommits, FILE *output, QUERY* query)
{
    DATA data_init = build_data(data_inicio);
    DATA data_final = build_data(data_fim);
    USER u = NULL;
    COUNTID cid = NULL;
    COMMITS commits = NULL;
    int id, i, length=getCatCommitsLength(catcommits), count=0;
    gpointer search = NULL;
    GArray *array = g_array_new( FALSE, FALSE, sizeof(COUNTID));
    GHashTable* users_count = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
    char* login = NULL;
    char* buff2 = NULL;
    char buff[100];

    for(i=0;i<length;i++)
    {
        commits=getCommitsPointer(catcommits,i);
        char *aux = getCommitsCommit_at(commits);
        DATA data_commits = build_data(aux);
        id = getCommitsAuthorId(commits);
        search = g_hash_table_lookup(users_count,GINT_TO_POINTER(id));
        count = GPOINTER_TO_INT(search) +1;
        if(compareData(data_init,data_commits)==1 && compareData(data_commits, data_final)==1)
            g_hash_table_insert(users_count,GINT_TO_POINTER(id), GINT_TO_POINTER(count));
        free(aux);
        free(data_commits);
    }

    g_hash_table_foreach(users_count, insereInArray, array);
    g_array_sort(array,cmpCommits);
    
    for(i=0;n_users!=0 && i<array->len;n_users--,i++)
    {
        if (output!=NULL)
        {
            cid = g_array_index(array, COUNTID, i);
            u = g_hash_table_lookup(getCatUserHash(catuser), GINT_TO_POINTER(countIdId(cid)));
            login = getUserLogin(u);
            fprintf(output,"%d;%s;%d\n", countIdId(cid), login, countIdCount(cid));
            free(login);
        }
        else
        {
            cid = g_array_index(array, COUNTID, i);
            u = g_hash_table_lookup(getCatUserHash(catuser), GINT_TO_POINTER(countIdId(cid)));
            login = getUserLogin(u);
            sprintf(buff,"%d;%s;%d\n", countIdId(cid), login, countIdCount(cid));
            buff2 = buff;
            query[i] = build_query(&buff2,5,NULL);
            free(login);
        }
    }
    
    free(data_init);
    free(data_final);
    for (i = array->len-1; i >= 0; i--) 
        free(g_array_index(array, COUNTID, i));
    g_array_free(array,TRUE); 
    g_hash_table_destroy(users_count);
}


/**
 * \brief Top‌ ‌N‌ of users with more commits in specific language's repositories 
 */
void query6(int n_users, char *linguagem, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output, QUERY* query)
{
    USER u = NULL;
    REPOS repo = NULL;
    COMMITS commits = NULL;
    COUNTID cid = NULL;
    int i, j=0, length = getCatCommitsLength(catcommits), count=0;
    gpointer search = NULL;
    gpointer id = NULL;
    GArray *array = g_array_new( FALSE, FALSE, sizeof(COUNTID));
    GHashTable* users_count = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
    char* aux = NULL;
    char* login = NULL;
    char buff[100]; 
    char* buff2 = NULL;

    for(i=0;i<length;i++)
    {
        commits = getCommitsPointer(catcommits,i);
        repo = g_hash_table_lookup(getCatReposHash(catrepos), GINT_TO_POINTER(getCommitsRepoId(commits)));
        if(repo!=NULL)
        {
            aux = getReposLang(repo);
            id = GINT_TO_POINTER(getCommitsAuthorId(commits));
            search = g_hash_table_lookup(users_count,id);
            count = GPOINTER_TO_INT(search) +1;
            if(strcmp(aux, linguagem) == 0)
            {
                g_hash_table_insert(users_count,id, GINT_TO_POINTER(count));
                j++;
            }
            free(aux);
        }
    }

    g_hash_table_foreach(users_count, insereInArray, array);
    g_array_sort(array,cmpCommits);
    if (output!=NULL)
    {
        for(i=0;n_users!=0 && i<array->len;n_users--,i++)
        {
            cid = g_array_index(array, COUNTID, i);
            u = g_hash_table_lookup(getCatUserHash(catuser), GINT_TO_POINTER(countIdId(cid)));
            login = getUserLogin(u);
            fprintf(output, "%d;%s;%d\n", countIdId(cid), login, countIdCount(cid));
            free(login);
        }
    }
    else if (j==0)
    {
        sprintf(buff,"%d;%s;%d\n", 0, "login", 0);
        buff2 = buff;
        query[0] = build_query(&buff2,6,NULL);
    }
    else
    {
        for(i=0;n_users!=0 && i<array->len;n_users--,i++)
        {
            cid = g_array_index(array, COUNTID, i);
            u = g_hash_table_lookup(getCatUserHash(catuser), GINT_TO_POINTER(countIdId(cid)));
            login = getUserLogin(u);
            sprintf(buff,"%d;%s;%d\n", countIdId(cid), login, countIdCount(cid));
            buff2 = buff;
            query[i] = build_query(&buff2,6,NULL);
            free(login);
        }
    }
    for (i = array->len-1; i >= 0; i--) 
        free(g_array_index(array, COUNTID, i));
    g_array_free(array,TRUE);
    g_hash_table_destroy(users_count);
}

/**
 * \brief Repositories's list without commits from a given date
 */
void query7(char *data_inicio, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output)
{
    // Lista‌ ‌de‌ ‌repositórios‌ ‌sem‌ ‌commits‌ ‌a‌ ‌partir‌ ‌de‌ ‌uma‌ ‌determinada data
    DATA data_init = build_data(data_inicio);
    COMMITS commits = NULL;
    REPOS repos = NULL;
    DATA data_commits = NULL;
    int length = getCatCommitsLength(catcommits), count=0, id, i;
    gpointer search = NULL;
    GHashTable* repos_count = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
    char* aux = NULL;

    for(i=0;i<length;i++)
    {
        count=0;
        commits = getCommitsPointer(catcommits,i);
        aux = getCommitsCommit_at(commits);
        data_commits = build_data(aux);
        id = getCommitsRepoId(commits);
        repos =  g_hash_table_lookup(getCatReposHash(catrepos),GINT_TO_POINTER(id));
        search = g_hash_table_lookup(repos_count,GINT_TO_POINTER(id));
        count = GPOINTER_TO_INT(search) +1;
        
        if(compareData(data_init,data_commits)==1)
            g_hash_table_insert(repos_count,repos, GINT_TO_POINTER(count));
        else
            g_hash_table_insert(repos_count,repos, GINT_TO_POINTER(0));

        free(aux);
        free(data_commits);
    }
    g_hash_table_foreach(repos_count, repoWithoutCommit, output);

    free(data_init);
    g_hash_table_destroy(repos_count);
}


/**
 * \brief //Top N of languages most used in a given date range
 */
void query8(int n_users, char *data_inicio, CATREPOS catrepos, FILE *output, QUERY* query)
{
    DATA data_init = build_data(data_inicio);
    REPOS repos = NULL;
    DATA data_repos = NULL;
    int i, length = getCatReposLength(catrepos), j=0;
    GArray *array = g_array_new( FALSE, FALSE, sizeof(COUNTLANG));
    char* buff2 = NULL;
    
    for(i = 0; i < length; i++)
    {   
        repos = getReposPointer(catrepos, i);
        char* aux = getReposCreatedAt(repos);
        data_repos = build_data(aux);      
        if(compareData(data_init,data_repos)==1)
        {
            char* lang = getReposLang(repos);
            j = searchLang(array,lang); // pos of lang -> -1 if doens't exists
            if(strcmp(lang,"None")!=0)
            {
                if(j==-1)
                    insereInArrayLang(array,lang);
                else 
                {
                    addCount(array, j);
                    free(lang);
                }
            }
            else free(lang);
        }  
        free(aux);   
        free(data_repos); 
    }
    g_array_sort(array,cmpCommitsLang);

    if (output!=NULL)
    {
        for(i=0;n_users!=0;n_users--,i++)
        {
            char* lang = countLangLang(g_array_index(array, COUNTLANG, i));
            fprintf(output,"%s\n",lang);
            free(lang);
        }
        fprintf(output,"\n");
    }
    else
    {
        for(i=0;n_users!=0 && i<array->len;n_users--,i++)
        {
            char* lang = countLangLang(g_array_index(array, COUNTLANG, i));
            buff2 = lang;
            query[i] = build_query(&buff2,8,NULL);
            free(lang);
        }
    }
    
    for (i = array->len-1; i >= 0; i--)
        free(g_array_index(array, COUNTLANG, i));
    
    g_array_free(array,TRUE);
    free(data_init);
}


/**
 * \brief Top N of users with more commits in repositories whose owner is a friend
 */
void query9(int n_users, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output)
{
    USER user = NULL;
    COUNTID cid = NULL;
    COMMITS commits = NULL;
    REPOS repos = NULL;
    int i, count=0, ownerId, length = getCatCommitsLength(catcommits), arrayLen;
    char buff[9];
    gpointer search = NULL;
    gpointer id = NULL;
    GArray *array = g_array_new( FALSE, FALSE, sizeof(COUNTID));
    GHashTable* hashTop = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
    char* login = NULL;

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
    arrayLen = array->len;
    
    for(i=0;n_users!=0 && i<arrayLen;n_users--,i++)
    {
        cid = g_array_index(array, COUNTID, i);
        user = g_hash_table_lookup(getCatUserHash(catuser), GINT_TO_POINTER(countIdId(cid)));
        login = getUserLogin(user);
        fprintf(output,"%d;%s\n", countIdId(cid), login);
        free(login);
    }
    fprintf(output,"\n");

    for (i = array->len-1; i >= 0; i--) 
        free(g_array_index(array, COUNTID, i));
    g_array_free(array,TRUE);
    g_hash_table_destroy(hashTop);
}


/**
 * \brief Top N of users, sorted by size message‌ from‌ commit‌,‌ ‌in‌ ‌each‌ ‌repository
 */
void query10(int n_users, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, FILE *output)
{
    USER u = NULL;
    COMMITS commits = NULL;
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
        if(u!=NULL && array!=NULL)
            insert(getCommitsAuthorId(commits), getCommitsLengthMessage(commits), getUserLogin(u), array);  
    }
    
    g_hash_table_foreach(hashRepos, sortArray, GINT_TO_POINTER(n_users));
    g_hash_table_foreach(hashRepos, printArray, output);

    g_hash_table_destroy(hashRepos);
}