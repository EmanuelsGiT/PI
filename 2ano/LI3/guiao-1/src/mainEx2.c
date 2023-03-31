#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tree.c"

struct Node* build_Tree(FILE* toread, struct Node* root)
{
    int max_len = 5000, valint = 0;
    char buff[max_len];
    char *buff2=NULL;

    fgets(buff, max_len, toread); //delete first line 
    while(fgets(buff, max_len, toread))
    {
        buff2=buff; //id is the first section on users and repos files
        valint = atoi(strdup(strsep(&buff2, ";\r\n")));
        root=insert(root,valint);
    }
    return root;
}

int search_Tree(struct Node* root, int id, int n)
{
    while(root != NULL)
    {
        if(root->key == id) 
        {
            if (n==1) root->calls++;
            return 1;
        }
        else if(root->key > id) root = root->left;
        else root = root->right;
    }
    return 0;
}

int check_calls (struct Node *root, int id)
{
    while(root != NULL)
    {   
        if(root->key == id) 
        {
            if (root->calls!=0) return 1;
            return 0;
        }
        else if(root->key > id) root = root->left;
        else root = root->right;
    }
    return 0;
}

void check_commits(struct Node* root_users, struct Node* root_repos, FILE* toread, FILE* towrite)
{
    int max_len = 200000, author_id = 0, commiter_id=0, repo_id=0, faulty=0;
    char buff[max_len];
    char *buff2=NULL;
    char lineok[max_len+1];

    fgets(buff, max_len, toread);
    fprintf(towrite,"%s",buff);

    while(fgets(buff, max_len, toread))
    {
        strcpy(lineok,buff);
        buff2=buff;
        repo_id = atoi(strdup(strsep(&buff2, ";\r\n")));
        author_id = atoi(strdup(strsep(&buff2, ";\r\n")));
        commiter_id = atoi(strdup(strsep(&buff2, ";\r\n")));

        if(search_Tree(root_users,author_id,0)==1 && search_Tree(root_users,commiter_id,0)==1 && search_Tree(root_repos,repo_id,1)==1)
                fprintf(towrite,"%s",lineok);
        else faulty++;
    }
    printf("Faulty Commits = %d\n",faulty);
}

void check_repos(struct Node* root_users, struct Node* root_repos, FILE* toread, FILE* towrite)
{
    int max_len = 200000, repo_id=0, owner_id=0, faulty=0;
    char buff[max_len];
    char *buff2=NULL;
    char lineok[max_len+1];

    fgets(buff, max_len, toread);
    fprintf(towrite,"%s",buff);

    while(fgets(buff, max_len, toread))
    {
        strcpy(lineok,buff);
        buff2=buff;
        repo_id = atoi(strdup(strsep(&buff2, ";\r\n")));
        owner_id = atoi(strdup(strsep(&buff2, ";\r\n")));

        if(search_Tree(root_users,owner_id,0)==1 && check_calls(root_repos,repo_id)==1)
            fprintf(towrite,"%s",lineok);
        else faulty++;
    }
    printf("Faulty Repos = %d\n",faulty);
}
    

int exercicio2()
{
    struct Node *root_user = NULL;
    struct Node *root_repos = NULL;

    printf("starting...\n");
    FILE *fusersok = fopen("saida/users-ok.csv", "r");
    FILE *fusersfinal = fopen("saida/users-final.csv","w");

    FILE *fcommitsok = fopen("saida/commits-ok.csv", "r");
    FILE *fcommitsfinal = fopen("saida/commits-final.csv","w");

    FILE *freposok = fopen("saida/repos-ok.csv", "r");
    FILE *freposfinal = fopen("saida/repos-final.csv","w");

    if (fusersok == NULL || fusersfinal == NULL ||  fcommitsok == NULL || fcommitsfinal == NULL || freposok == NULL || freposfinal == NULL)
        return -1;
    else printf("All file opened successfully\n");

    root_user=build_Tree(fusersok,root_user);
    root_repos=build_Tree(freposok,root_repos);

    check_commits(root_user,root_repos,fcommitsok,fcommitsfinal);

    fseek(freposok,0,SEEK_SET); // moves pointer to the beginning of the file

    check_repos(root_user,root_repos,freposok,freposfinal);

    printf("Everything tested, mission completed.\n");

    fclose(fusersok);
    fclose(fusersfinal);
    fclose(fcommitsok);
    fclose(fcommitsfinal);
    fclose(freposok);
    fclose(freposfinal);

    return 0;
}