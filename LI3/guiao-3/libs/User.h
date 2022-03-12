#include <stdio.h>
#include <glib.h>


typedef enum type
{
    userType,
    organization,
    bot,
}TYPE;

typedef struct user *USER;

USER build_user2(char* line, int *id);
int getUserId(USER u);
TYPE getUserTypeEnum(USER u);
char* getUserLogin(USER u);
char* getUserFollowersList(USER u);
char* getUserFollowingList(USER u);
char* getUserType(USER u);

void freeUser (gpointer ux);