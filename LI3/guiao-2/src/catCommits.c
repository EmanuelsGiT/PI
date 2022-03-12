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
    result->commits=malloc(sizeof(struct catCommits)*length);
    fgets(buff, max_len, toread);
    
    while(fgets(buff, max_len, toread))
    {
        if(i>=length)
        {
            length*=2;
            result->commits = realloc(result->commits,sizeof(struct catCommits)*length);
        }
        result->commits[i] = build_commits2(buff);

        i++;
    }

    result->length = i;
    return result;
}

int getCatCommitsLength(CATCOMMITS cat){return cat->length;}
COMMITS getCommitsPointer(CATCOMMITS cat, int i){return cat->commits[i];} //get specific Commit