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
    result->repos=malloc(sizeof(REPOS)*length);
    result->repos_id = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
    fgets(buff, max_len, toread);

    while(fgets(buff, max_len, toread))
    {
                if(i>=length)
        {
            length*=2;
            result->repos = realloc(result->repos,sizeof(REPOS)*length);
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

void freeCatRepos(CATREPOS catrepos)
{
    int i;
    for(i=catrepos->length-1;i>=0;i--)
        freeRepos (catrepos->repos[i]);
    g_hash_table_destroy (catrepos->repos_id);
    free(catrepos->repos);
    free(catrepos);
}

void swapRepos(int* a, int* b, REPOS *x, REPOS *y) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
    REPOS z = *x;
    *x = *y;
    *y = z;
} 

int partitionRepos (int arr[], int low, int high, REPOS *repos) 
{ 
    int pivot = arr[high];
    int i = (low - 1);
  
    for (int j = low; j <= high - 1; j++) 
    { 
        if (arr[j] < pivot) 
        { 
            i++;
            swapRepos(&arr[i], &arr[j], &repos[i], &repos[j]); 
        } 
    } 
    swapRepos(&arr[i + 1], &arr[high], &repos[i+1], &repos[high]); 
    return (i + 1); 
} 

void quickSortRepos(int arr[], int low, int high, REPOS *repos) 
{ 
    if (low < high) 
    { 
        int pi = partitionRepos(arr, low, high, repos); 
        quickSortRepos(arr, low, pi - 1, repos); 
        quickSortRepos(arr, pi + 1, high, repos); 
    } 
}


void saveCatReposInFile(FILE* toread, char* buff, int max_len, FILE* fcatRepos, GHashTable* hashIdRepos)
{
    fgets(buff, max_len, toread);

    while(fgets(buff, max_len, toread))
    {
        REPOS r = build_repos2(buff);
        char *desc = getReposDescription(r);
        char *lang = getReposLang(r);
        char *data = getReposCreatedAt(r);
        g_hash_table_insert(hashIdRepos,GINT_TO_POINTER(getReposId(r)),GINT_TO_POINTER(ftell(fcatRepos)));
        fprintf(fcatRepos, "%d;%d;%s;%s;%s\n", getReposId(r), getReposOwnerId(r), desc, lang, data);
        free(desc);
        free(lang);
        free(data);
        freeRepos(r);
    }

    fclose(fcatRepos);
} 

int createArrayIdRepos(int* idRepos)
{
    FILE *index = fopen("saida/indexCatRepos.txt", "w");
    if(index==NULL) return -1;
    int i;
    char buff[20];
    char* buff2 = NULL;
    for(i=0;fgets(buff, 20, index);i++)
    {
        buff2 = buff;
        idRepos[i] = atoi(strsep(&buff2, ";\n"));
    }

    fclose(index);
    return 0;
}


int binarySearch(int *idRepos, int len, int item)
{
    int begin = 0;
    int end = len - 1;
    int i;

    while (begin <= end) 
    {
        i = (begin + end) / 2;

        if (idRepos[i] == item) return i;
        if (idRepos[i] < item) begin = i + 1;
        else end = i;
    }
    return -1;
}



void findRepo(GHashTable* hashIdRepos, int id, REPOS r, FILE *fcatRepos, char* str)
{
    int pos = GPOINTER_TO_INT(g_hash_table_lookup(hashIdRepos,GINT_TO_POINTER(id)));
    fseek(fcatRepos, pos, SEEK_SET);
    fgets(str, 550000, fcatRepos);
}