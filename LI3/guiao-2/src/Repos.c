#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libs/Repos.h"

struct repos
{
    int id;
    int owner_id;
    //char* full_name;
    //char* license;
    //char* has_wiki;
    char* description;
    char* language;
    //char* default_branch;
    char* created_at;
    //char* updated_at;
    //int forks_count;
    //int open_issues;
    //int stargazers_count;
    //int size;
};


REPOS build_repos2(char* line)
{
    REPOS u = malloc(sizeof(struct repos));
    char* buff2 = line;
    u->id = atoi(strsep(&buff2, ";\n"));
    u->owner_id = atoi(strsep(&buff2, ";\n"));
    strsep(&buff2, ";\n"); //full_name
    strsep(&buff2, ";\n"); //license
    strsep(&buff2, ";\n"); //has_wiki
    u->description = strdup (strsep(&buff2, ";\n"));
    u->language = strdup (strsep(&buff2, ";\n"));
    strsep(&buff2, ";\n"); //default_branch
    u->created_at = strdup (strsep(&buff2, ";\n"));
    //strsep(&buff2, ";\n"); updated_at
    //strsep(&buff2, ";\n"); forks_count
    //strsep(&buff2, ";\n"); open_issues
    //strsep(&buff2, ";\n"); stargazers_count
    //strsep(&buff2, ";\n"); size

    return u;
}

int getReposId(REPOS r) { return r->id;}
int getReposOwnerId(REPOS r) { return r->owner_id;}
char* getReposDescription(REPOS r) { return strdup(r->description);}
char* getReposLang(REPOS r) { return strdup(r->language);}
char* getReposCreatedAt(REPOS r) { return strdup(r->created_at);}