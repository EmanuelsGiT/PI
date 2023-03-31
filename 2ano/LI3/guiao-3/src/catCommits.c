#include "../libs/Commits.h"
#include "../libs/catCommits.h"
#include <glib.h>

struct catCommits
{
    COMMITS* commits;
    int length;
};

CATCOMMITS createCatCommits(FILE* toread,char* buff,int max_len)
{
    int i=0, length=100;
    CATCOMMITS result = malloc(sizeof(struct catCommits));
    result->commits=malloc(sizeof(COMMITS)*length);
    fgets(buff, max_len, toread);
    
    while(fgets(buff, max_len, toread))
    {
        if(i>=length)
        {
            length*=2;
            result->commits = realloc(result->commits,sizeof(COMMITS)*length);
        }
        result->commits[i] = build_commits2(buff);

        i++;
    }

    result->length = i;
    return result;
}

int getCatCommitsLength(CATCOMMITS cat){return cat->length;}
COMMITS getCommitsPointer(CATCOMMITS cat, int i){return cat->commits[i];} //get specific Commit

void freeCatCommits(CATCOMMITS catcommits)
{
    int i;

    for(i=catcommits->length-1;i>=0;i--)
        freeCommits(catcommits->commits[i]);
    free(catcommits->commits);
    free(catcommits);
}

// File criado a partir de cat
int saveCatCommmitsInFile(CATCOMMITS cat)
{
    FILE *fcatCommits = fopen("saida/catCommits.txt", "w");
    if(fcatCommits==NULL) return -1;
    int i, len = cat->length;
    COMMITS c;
    for(i=0;i<len;i++)
    {
        c = cat->commits[i];
        fprintf(fcatCommits, "%d;%d;%d;%s;%d\n", getCommitsRepoId(c), getCommitsAuthorId(c), getCommitsCommitsId(c), getCommitsCommit_at(c), getCommitsLengthMessage(c));
    }
    return 0;
} 

// retorna tamanho da catCommits se não houver problemas ao abrir o ficheiro (sem criação da catCommits)
int saveCatCommmitsInFile2(FILE* toread,char* buff,int max_len)
{
    FILE *fcatCommits = fopen("saida/catCommits.txt", "w");
    if(fcatCommits==NULL) return -1;

    int i = 0;
    fgets(buff, max_len, toread);

    while(fgets(buff, max_len, toread))
    {
        COMMITS c = build_commits2(buff);
        char *aux = getCommitsCommit_at(c);
        fprintf(fcatCommits, "%d;%d;%d;%s;%d\n", getCommitsRepoId(c), getCommitsAuthorId(c), getCommitsCommitsId(c), aux, getCommitsLengthMessage(c));
        i++;
        freeCommits(c);
        free(aux);
    }

    fclose(fcatCommits);

    return i;
} 