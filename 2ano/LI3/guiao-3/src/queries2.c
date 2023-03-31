/**
 * @file File with queries functions done with catRepos and catCommits in files (catUser is still in memory).
 * It is used an hash table that has as keys the id of each repo and as a value the position of the repo in the file.
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
 * \brief Estimates the average of collaborators per repository
 */
void query2_2(FILE *catCommits, FILE *catrepos, FILE *output)
{   
    int r = 0, i, length, trepos=0;
    GHashTable* hashRepos = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,freeHashOfGArrays);
    GArray *array = NULL;
    GArray *sum = g_array_new( FALSE, TRUE, sizeof(int));

    int id, repoId, authorId, commiterId;
    char str[550000];
    char buff[100];
    char* buff2 = NULL;
    while(fgets(str, 550000, catrepos))
    {
        buff2 = str;
        id = atoi(strsep(&buff2, ";\n"));
        GArray *arrayx = g_array_new( FALSE, FALSE, sizeof(int));
        g_hash_table_insert(hashRepos,GINT_TO_POINTER(id), arrayx);
        trepos++;
    }

    while(fgets(buff, 100, catCommits))
    {
        buff2 = buff;
        repoId = atoi(strsep(&buff2, ";\n"));
        array = g_hash_table_lookup(hashRepos, GINT_TO_POINTER(repoId));
        if(array!=NULL)
        {
            authorId = atoi(strsep(&buff2, ";\n"));
            g_array_append_val(array, authorId);
            commiterId = atoi(strsep(&buff2, ";\n"));
            g_array_append_val(array, commiterId);
        }
    }
    g_hash_table_foreach(hashRepos, sortArrayQ, sum);
    length = sum->len;

    for(i=0;i<length;i++)
        r+=g_array_index(sum, int, i);
    
    fprintf(output, "%.2f", r / (float)(trepos-1));

    
    g_array_free(sum,TRUE);
    g_hash_table_destroy(hashRepos);

}


/**
 * \brief Number of repositories ‌contendo‌ bots‌‌ ‌como‌ ‌colaboradores
 */
void query3_2(CATUSER catuser,  FILE *catCommits, FILE *output)
{   
    USER user1 = NULL, user2 = NULL;
    GHashTable* repoBot_count = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
    char buff[100];
    char *buff2 = NULL;
    int authorId, commiterId;

    while(fgets(buff, 100, catCommits))
    {
        buff2 = buff;
        strsep(&buff2, ";\n");
        authorId = atoi(strsep(&buff2, ";\n"));
        commiterId = atoi(strsep(&buff2, ";\n"));
        user1 = g_hash_table_lookup(getCatUserHash(catuser),GINT_TO_POINTER(authorId));
        user2 = g_hash_table_lookup(getCatUserHash(catuser),GINT_TO_POINTER(commiterId));
        
        if(user1!=NULL)
        {
            if(getUserTypeEnum(user1)==bot)
                g_hash_table_insert(repoBot_count,GINT_TO_POINTER(authorId),GINT_TO_POINTER(1));
        }
        if(user2!=NULL)
        {
            if(getUserTypeEnum(user2)==bot)
                g_hash_table_insert(repoBot_count,GINT_TO_POINTER(commiterId),GINT_TO_POINTER(1));
        }
    }

    fprintf(output, "%d", g_hash_table_size(repoBot_count));

    g_hash_table_destroy(repoBot_count);
}


/**
 * \brief Top N of users with more commits in a given date range
 */
void query5_2(int n_users, char *data_inicio, char *data_fim, CATUSER catuser, FILE *catcommits, FILE *output)
{
    DATA data_init = build_data(data_inicio);
    DATA data_final = build_data(data_fim);
    USER u = NULL;
    COUNTID cid = NULL;
    int id, i, count=0;
    gpointer search = NULL;
    GArray *array = g_array_new( FALSE, FALSE, sizeof(COUNTID));
    GHashTable* users_count = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
    char* login = NULL;

    char buff[100];

    while(fgets(buff, 100, catcommits))
    {
        COMMITS commits = build_commits2(buff);
        char *aux = getCommitsCommit_at(commits);
        DATA data_commits = build_data(aux);
        id = getCommitsAuthorId(commits);
        search = g_hash_table_lookup(users_count,GINT_TO_POINTER(id));
        count = GPOINTER_TO_INT(search) +1;
        if(compareData(data_init,data_commits)==1 && compareData(data_commits, data_final)==1)
            g_hash_table_insert(users_count,GINT_TO_POINTER(id), GINT_TO_POINTER(count));
        free(aux);
        free(data_commits);
        freeCommits(commits);
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
            printf("%d;%s;%d\n", countIdId(cid), login, countIdCount(cid));
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
void query6_2(int n_users, char *linguagem, CATUSER catuser, FILE *catcommits, FILE *catrepos, FILE *output, GHashTable* hashIdRepos)
{
    USER u = NULL;
    COUNTID cid = NULL;
    int i, count=0;
    gpointer search = NULL;
    gpointer id = NULL;
    GArray *array = g_array_new( FALSE, FALSE, sizeof(COUNTID));
    GHashTable* users_count = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
    char* aux = NULL;
    char* login = NULL;

    char buff[100];
    char* buff2 = NULL;
    int repoId, authorId, pos;
    char str[550000];

    while(fgets(buff, 100, catcommits))
    {
        buff2 = buff;
        repoId = atoi(strsep(&buff2, ";\n"));
        authorId = atoi(strsep(&buff2, ";\n"));
        pos = GPOINTER_TO_INT(g_hash_table_lookup(hashIdRepos,GINT_TO_POINTER(repoId)));
        fseek(catrepos, pos, SEEK_SET);
        fgets(str, 550000, catrepos);
        REPOS repo = build_repos3(str);
        if(repo!=NULL)
        {
            aux = getReposLang(repo);
            id = GINT_TO_POINTER(authorId);
            search = g_hash_table_lookup(users_count,id);
            count = GPOINTER_TO_INT(search) +1;
            if(strcmp(aux, linguagem) == 0)
                g_hash_table_insert(users_count,id, GINT_TO_POINTER(count));
            free(aux);
        }
        freeRepos(repo);
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
    else
    {
        for(i=0;n_users!=0 && i<array->len;n_users--,i++)
        {
            cid = g_array_index(array, COUNTID, i);
            u = g_hash_table_lookup(getCatUserHash(catuser), GINT_TO_POINTER(countIdId(cid)));
            login = getUserLogin(u);
            printf("%d;%s;%d\n", countIdId(cid), login, countIdCount(cid));
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

void insereInHashCountDesc(GHashTable* repos_count, int id, char *desc, int c)
{
  COUNTLANG cid = malloc(sizeof (struct countLang));
  cid->count = c;
  cid->lang = desc;
  g_hash_table_insert(repos_count,GINT_TO_POINTER(id),cid);
}

void repoWithoutCommit_2(gpointer id, gpointer countDesc, void *output)
{
  COUNTLANG cd = countDesc;
  if(cd->count==0)
  {
    if (output!=NULL)
      fprintf((FILE*)output, "%d;%s\n",GPOINTER_TO_INT(id),cd->lang);
    else
      printf("%d;%s\n",GPOINTER_TO_INT(id),cd->lang);
  }
  free(cd->lang);
}

void query7_2(char *data_inicio, FILE *catcommits, FILE *catrepos, FILE *output, GHashTable* hashIdRepos)
{
    // Lista‌ ‌de‌ ‌repositórios‌ ‌sem‌ ‌commits‌ ‌a‌ ‌partir‌ ‌de‌ ‌uma‌ ‌determinada data
    DATA data_init = build_data(data_inicio);
    DATA data_commits = NULL;
    int count=0, id, pos;
    gpointer search = NULL;
    GHashTable* repos_count = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
    char* aux = NULL;
    char str[550000];
    char buff[100];

    while(fgets(buff, 100, catcommits))
    {
        count=0;
        COMMITS commits = build_commits2(buff);
        aux = getCommitsCommit_at(commits);
        data_commits = build_data(aux);
        id = getCommitsRepoId(commits);
        pos = GPOINTER_TO_INT(g_hash_table_lookup(hashIdRepos,GINT_TO_POINTER(id)));
        fseek(catrepos, pos, SEEK_SET);
        fgets(str, 550000, catrepos);
        REPOS repo = build_repos3(str);
        search = g_hash_table_lookup(repos_count,GINT_TO_POINTER(id));
        count = GPOINTER_TO_INT(search) +1;
        char *desc = getReposDescription(repo);

        if(compareData(data_init,data_commits)==1)  
            insereInHashCountDesc(repos_count,id,desc,count);
        else
            insereInHashCountDesc(repos_count,id,desc,0);

        free(aux);
        free(data_commits);
        freeCommits(commits);
        freeRepos(repo);
    }
    g_hash_table_foreach(repos_count, repoWithoutCommit_2, output);
    fprintf(output,"\n");
    free(data_init);
    g_hash_table_destroy(repos_count);
}


/**
 * \brief //Top N of languages most used in a given date range
 */
void query8_2(int n_users, char *data_inicio, FILE *catrepos, FILE *output)
{
    DATA data_init = build_data(data_inicio);
    DATA data_repos = NULL;
    int i, j=0;
    GArray *array = g_array_new( FALSE, FALSE, sizeof(COUNTLANG));
    char* lang = NULL;
    char* aux = NULL;
    
    char buff[550000];

    while(fgets(buff, 550000, catrepos))
    { 
        REPOS repos = build_repos3(buff);
        aux = getReposCreatedAt(repos);
        data_repos = build_data(aux);      
        if(compareData(data_init,data_repos)==1)
        {
            lang = getReposLang(repos);
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
        freeRepos(repos); 
    }
    g_array_sort(array,cmpCommitsLang);

    if (output!=NULL)
    {
        for(i=0;n_users!=0;n_users--,i++)
        {
            lang = countLangLang(g_array_index(array, COUNTLANG, i));
            fprintf(output,"%s\n",lang);
            free(lang);
        }
    }
    else
    {
        for(i=0;n_users!=0 && i<array->len;n_users--,i++)
        {
            lang = countLangLang(g_array_index(array, COUNTLANG, i));
            printf("%s\n",lang);
            free(lang);
        }
    }
    fprintf(output,"\n");
    
    for (i = array->len-1; i >= 0; i--)
        free(g_array_index(array, COUNTLANG, i));
    
    g_array_free(array,TRUE);
    free(data_init);
}


/**
 * \brief Top N of users with more commits in repositories whose owner is a friend
 */
void query9_2(int n_users, CATUSER catuser, FILE *catcommits, FILE *catrepos, FILE *output, GHashTable* hashIdRepos)
{
    USER user = NULL;
    COUNTID cid = NULL;
    int i, count=0, ownerId, arrayLen, pos;
    char buff[9];
    gpointer search = NULL;
    gpointer id = NULL;
    GArray *array = g_array_new( FALSE, FALSE, sizeof(COUNTID));
    GHashTable* hashTop = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
    char* login = NULL;

    char fbuff[100];
    char* buff2 = NULL;
    int authorId, repoId;
    char str[550000];

    while(fgets(fbuff, 100, catcommits))
    {
        buff2 = fbuff;
        repoId = atoi(strsep(&buff2, ";\n"));
        authorId = atoi(strsep(&buff2, ";\n"));
        id = GINT_TO_POINTER(authorId);
        pos = GPOINTER_TO_INT(g_hash_table_lookup(hashIdRepos,GINT_TO_POINTER(repoId)));
        fseek(catrepos, pos, SEEK_SET);
        fgets(str, 550000, catrepos);
        REPOS repos = build_repos3(str);
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
        freeRepos(repos);
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
void query10_2(int n_users, CATUSER catuser, FILE *catcommits, FILE *catrepos, FILE *output)
{
    USER u = NULL;
    GHashTable* hashRepos = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
    GArray *array = NULL;
    
    char str[100];
    char *buff2 = NULL;
    int repoId;

    while(fgets(str, 100, catrepos))
    {
        buff2 = str;
        repoId = atoi(strsep(&buff2, ";\n"));
        GArray *arrayx = g_array_new( FALSE, FALSE, sizeof(COUNTIDLOG));
        g_hash_table_insert(hashRepos,GINT_TO_POINTER(repoId), arrayx);
    }
    
    char buff[100];

    while(fgets(buff, 100, catcommits))
    {
        COMMITS commits = build_commits2(buff);
        array = g_hash_table_lookup(hashRepos, GINT_TO_POINTER(getCommitsRepoId(commits)));
        u = g_hash_table_lookup(getCatUserHash(catuser), GINT_TO_POINTER(getCommitsAuthorId(commits)));
        if(u!=NULL && array!=NULL)
            insert(getCommitsAuthorId(commits), getCommitsLengthMessage(commits), getUserLogin(u), array); 
        freeCommits(commits); 
    }
    
    g_hash_table_foreach(hashRepos, sortArray, GINT_TO_POINTER(n_users));
    g_hash_table_foreach(hashRepos, printArray, output);

    g_hash_table_destroy(hashRepos);
}
    