#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libs/Tree.h"

NODE build_Tree(FILE* toread, NODE root)
{
    int max_len = 5000, valint = 0;
    char buff[max_len];
    char* buff2 = NULL;
    char* val = NULL;

    fgets(buff, max_len, toread); //delete first line 
    while(fgets(buff, max_len, toread))
    {
        //id is the first section on users and repos files
        buff2 = buff; 
        val = strdup(strsep(&buff2, ";\r\n"));
        valint = atoi(val);
        root = insertTree(root,valint);
        free(val);
    }
    return root;
}


int search_Tree(NODE root, int id, int n)
{
    while(root != NULL)
    {
        if(rootKey(root) == id) 
        {
            if (n==1) incrementCalls(root);
            return 1;
        }
        else if(rootKey(root) > id) root = rootLeft(root);
        else root = rootRight(root);
    }
    return 0;
}

int check_calls (NODE root, int id)
{
    while(root != NULL)
    {   
        if(rootKey(root) == id) 
        {
            if (rootCalls(root)!=0) return 1;
            return 0;
        }
        else if(rootKey(root) > id) root = rootLeft(root);
        else root = rootRight(root);
    }
    return 0;
}

void check_commits(NODE root_users, NODE root_repos, FILE* toread, FILE* towrite)
{
    int max_len = 200000, author_id = 0, commiter_id=0, repo_id=0, faulty=0;
    char buff[max_len];
    char lineok[max_len+1];
    char* buff2 = NULL;
    char* repo = NULL;
    char* author = NULL;
    char* commiter = NULL;

    fgets(buff, max_len, toread);
    fprintf(towrite,"%s",buff);

    while(fgets(buff, max_len, toread))
    {
        strcpy(lineok,buff);
        buff2 = buff;
        repo = strdup(strsep(&buff2, ";\r\n"));
        repo_id = atoi(repo);
        author = strdup(strsep(&buff2, ";\r\n"));
        author_id = atoi(author);
        commiter = strdup(strsep(&buff2, ";\r\n"));
        commiter_id = atoi(commiter);

        if(search_Tree(root_users,author_id,0)==1 && search_Tree(root_users,commiter_id,0)==1 && search_Tree(root_repos,repo_id,1)==1)
                fprintf(towrite,"%s",lineok);
        else faulty++;

        free(repo);
        free(author);
        free(commiter);
    }
    printf("Faulty Commits = %d\n",faulty);
}

void check_repos(NODE root_users, NODE root_repos, FILE* toread, FILE* towrite)
{
    int max_len = 200000, repo_id=0, owner_id=0, faulty=0;
    char buff[max_len];
    char lineok[max_len+1];
    char* buff2 = NULL;
    char* repo = NULL;
    char* owner = NULL;

    fgets(buff, max_len, toread);
    fprintf(towrite,"%s",buff);

    while(fgets(buff, max_len, toread))
    {
        strcpy(lineok,buff);
        buff2 = buff;
        repo = strdup(strsep(&buff2, ";\r\n"));
        repo_id = atoi(repo);
        owner = strdup(strsep(&buff2, ";\r\n")); 
        owner_id = atoi(owner);

        if(search_Tree(root_users,owner_id,0)==1 && check_calls(root_repos,repo_id)==1)
            fprintf(towrite,"%s",lineok);
        else faulty++;

        free(repo);
        free(owner);
    }
    printf("Faulty Repos = %d\n",faulty);
}
    

int exercicio2()
{
    printf("Starting 2nd Verification\n");
    
    NODE root_user = NULL;
    NODE root_repos = NULL;

    FILE *fusersok = fopen("saida/users-ok.csv", "r");

    FILE *fcommitsok = fopen("saida/commits-ok.csv", "r");
    FILE *fcommitsfinal = fopen("saida/commits-final.csv","w");

    FILE *freposok = fopen("saida/repos-ok.csv", "r");
    FILE *freposfinal = fopen("saida/repos-final.csv","w");

    if (fusersok == NULL || fcommitsok == NULL || fcommitsfinal == NULL || freposok == NULL || freposfinal == NULL)
        return -1;
    else printf("All file opened successfully\n");

    root_user=build_Tree(fusersok,root_user);
    root_repos=build_Tree(freposok,root_repos);

    check_commits(root_user,root_repos,fcommitsok,fcommitsfinal);

    fseek(freposok,0,SEEK_SET); // moves pointer to the beginning of the file

    check_repos(root_user,root_repos,freposok,freposfinal);


    fclose(fusersok);
    fclose(fcommitsok);
    fclose(fcommitsfinal);
    fclose(freposok);
    fclose(freposfinal);
    
    freeTree(root_user);
    freeTree(root_repos);

    printf("2nd Verification completed.\n\n");

    return 0;
}