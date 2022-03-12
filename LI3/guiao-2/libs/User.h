#include <stdio.h>

typedef struct user *USER;

USER build_user2(char* line);
int getUserId(USER u);
char* getUserType(USER u);
char* getUserLogin(USER u);
char* getUserFollowersList(USER u);
char* getUserFollowingList(USER u);