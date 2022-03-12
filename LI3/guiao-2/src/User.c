#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libs/User.h"

struct user
{
    int id;
    char* login;
    char* type;
    //char* created_at;
    //int followers;
    char* follower_list;
    //int following;
    char* following_list;
    //int public_gists;
    //int public_repos;
};

USER build_user2(char* line)
{
    USER u = malloc(sizeof(struct user));
    char* buff2 = line;
    u->id = atoi(strsep(&buff2, ";\n"));
    u->login = strdup (strsep(&buff2, ";\n"));
    u->type = strdup (strsep(&buff2, ";\n"));
    strsep(&buff2, ";\n"); //created_at
    strsep(&buff2, ";\n"); //followers
    u->follower_list = strdup (strsep(&buff2, ";\n"));
    strsep(&buff2, ";\n"); //following
    u->following_list = strdup (strsep(&buff2, ";\n"));
    //strsep(&buff2, ";\n"); public_gists
    //strsep(&buff2, ";\n"); public_repos
    return u;
}

int getUserId(USER u) {return u->id;}
char* getUserLogin(USER u) {return strdup(u->login);}
char* getUserType(USER u) {return strdup(u->type);}
char* getUserFollowersList(USER u) {return strdup(u->follower_list);}
char* getUserFollowingList(USER u) {return strdup(u->following_list);}