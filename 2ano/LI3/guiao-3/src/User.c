#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libs/User.h"
#include <glib.h>


struct user
{
    int id;
    char* login;
    TYPE type;
    //char* created_at;
    //int followers;
    char* follower_list;
    //int following;
    char* following_list;
    //int public_gists;
    //int public_repos;
};

USER build_user2(char* line, int *id)
{
    USER u = malloc(sizeof(struct user));
    char* buff2 = line;
    char* aux = NULL;
    u->id = atoi(strsep(&buff2, ";\n"));
    u->login = strdup (strsep(&buff2, ";\n"));
    aux = strdup (strsep(&buff2, ";\n"));
    if(strcmp(aux, "User") == 0) u->type=userType;
    else if(strcmp(aux, "Organization") == 0) u->type=organization;        
    else u->type=bot;
    strsep(&buff2, ";\n"); //created_at
    strsep(&buff2, ";\n"); //followers
    u->follower_list = strdup (strsep(&buff2, ";\n"));
    strsep(&buff2, ";\n"); //following
    u->following_list = strdup (strsep(&buff2, ";\n"));
    //strsep(&buff2, ";\n"); public_gists
    //strsep(&buff2, ";\n"); public_repos
    *id=u->id;
    free(aux);
    return u;
}

int getUserId(USER u) {return u->id;}
char* getUserLogin(USER u) {return strdup(u->login);}
TYPE getUserTypeEnum(USER u) {return u->type;}
char* getUserFollowersList(USER u) {return strdup(u->follower_list);}
char* getUserFollowingList(USER u) {return strdup(u->following_list);}

char* getUserType(USER u) 
{
    TYPE type = u->type;
    char* rbot = "Bot";
    char* ruser = "User";
    char* rorg = "Organization";
    if(type==bot) return rbot;
    else if(type==userType) return ruser;
    else return rorg;
}

void freeUser (gpointer ux)
{
    USER u = ux;
    free(u->login);
    free(u->follower_list);
    free(u->following_list);
    free(u);
}