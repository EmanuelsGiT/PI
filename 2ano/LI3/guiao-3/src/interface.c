#include <stdio.h>
#include <stdlib.h>
#include "../libs/mainEx1.h"
#include "../libs/guiao2.h"
#include "../libs/query.h"
#include "../libs/catQuery.h"

void menu()
{
    printf(" ------------------------------------------------------------------------------------------- \n");
    printf("| 1 |  Quantidade de bots, organizações e utilizadores.                                     |\n");
    printf(" ------------------------------------------------------------------------------------------- \n");
    printf("| 2 |  Número médio de colaboradores por repositório.                                       |\n");
    printf(" ------------------------------------------------------------------------------------------- \n");
    printf("| 3 |  Quantidade de repositórios de bots.                                                  |\n");
    printf(" ------------------------------------------------------------------------------------------- \n");    
    printf("| 4 |  Quantidade média de commits por utilizador.                                          |\n");
    printf(" ------------------------------------------------------------------------------------------- \n");
    printf("| 5 |  Top N de utilizadores mais ativos num determinado intervalo de datas.                |\n");
    printf(" ------------------------------------------------------------------------------------------- \n");
    printf("| 6 |  Top N de utilizadores com mais commits em repositórios de uma determinada linguagem. |\n");
    printf(" ------------------------------------------------------------------------------------------- \n");
    printf("| 7 |  Lista de repositórios sem commits a partir de uma determinada data.                  |\n");
    printf(" ------------------------------------------------------------------------------------------- \n");
    printf("| 8 |  Top N de linguagens mais utilizadas a partir de uma determinada data.                |\n");
    printf(" ------------------------------------------------------------------------------------------- \n");
    printf("| 9 |  Top N de utilizadores com mais commits em repositórios cujo owner é um amigo seu.    |\n");
    printf(" ------------------------------------------------------------------------------------------- \n");
    printf("| 10 | Top N de utilizadores com as maiores mensagens de commit por repositório.            |\n");
    printf(" ------------------------------------------------------------------------------------------- \n");
}

void submenu(int n,int n_users, QUERY* query)
{
    int i=0, ind=1, j=0, len, pag;
    char opcao[30];
    char* buff2 = NULL;
    len = n_users/10;
    if (len==0) len++;
    
    do {
        printf("-----------------------------------------------------------\n");
        while (i<10 && j<n_users)
        {
            char *login = getQueryLogin(query[j]);
            if (n==5) printf("| %d | %s | %d |\n",getQueryId(query[j]),login,getQueryComSize(query[j]));
            if (n==6) printf("| %d | %s | %d |\n",getQueryId(query[j]),login,getQueryComSize(query[j]));
            if (n==7) printf("| %d | %s |\n",getQueryId(query[j]),login);
            if (n==8) printf("| %s |\n",login);
            if (n==9) printf("| %d | %s |\n",getQueryId(query[j]),login);
            free(login);
            j++;
            i++;
        }
        printf("-----------------------------------------------------------\n\n");
        printf("------- Página %d de %d -------\n",ind,len);
        printf("P      -> Próxima Página\n");
        printf("A      -> Página Anterior\n");
        printf("S <N>  -> Saltar para página N\n\n");
        printf("Insira opção(0 para terminar): \n");
        setbuf(stdin, 0);
        fgets(opcao, 30, stdin);
        system("clear");
        buff2 = opcao;
        char* l = strdup(strsep(&buff2, " \r\n"));
        if (strcmp(l,"P")==0 && j<n_users && ind<len) 
        {
            ind++;
            i=0;
        }
        else if (strcmp(l,"A")==0 && ind-1>0) 
        {   
            ind--;
            i=0;
            j-=20;
        }
        else if (strcmp(l,"S")==0) 
        {
            char* num = strdup(strsep(&buff2, " \r\n"));
            pag = atoi(num);
            if (num!=NULL && pag<=len) 
            {
                ind = pag;
                j=10*(pag-1);
                i=0;
            }
            free(num);
        }
        else
        {
            ind=1;
            i=0;
            j=0;
        }
        free(l);
        
    } while (strcmp(opcao,"0")!=0);
}

int interfaceQ1()
{
    FILE *file = fopen("saida/fquery1.txt", "r");
    if (file == NULL)
    {
        printf("Ficheiro inexistente!\n");
        return -1;
    } 
    char line[20];
    printf("------------------- Query 1 -------------------\n");
    while (!feof(file))
    {
        fgets(line,20,file);
        printf("%s",line);
    }
    printf("\n");
    printf("-----------------------------------------------\n\n");
    
    fclose(file);

    return 0;
}

int interfaceQ2()
{    
    FILE *file = fopen("saida/fquery2.txt", "r");
    if (file == NULL)
    {
        printf("Ficheiro inexistente!\n");
        return -1;
    } 
    char line[20];
    printf("------------------- Query 2 -------------------\n");
    printf("Avg: ");
    fgets(line,20,file);
    printf("%s",line);
    printf("\n");
    printf("-----------------------------------------------\n\n");
    
    fclose(file);

    return 0;
}

int interfaceQ3()
{
    FILE *file = fopen("saida/fquery3.txt", "r");
    if (file == NULL)
    {
        printf("Ficheiro inexistente!\n");
        return -1;
    } 
    char line[20];
    printf("------------------- Query 3 -------------------\n");
    printf("Total: ");
    fgets(line,20,file);
    printf("%s",line);
    printf("\n");
    printf("-----------------------------------------------\n\n");
    
    fclose(file);

    return 0;
}

int interfaceQ4()
{
    FILE *file = fopen("saida/fquery4.txt", "r");
    if (file == NULL)
    {
        printf("Ficheiro inexistente!\n");
        return -1;
    } 
    char line[20];
    printf("------------------- Query 4 -------------------\n");
    printf("Avg: ");
    fgets(line,20,file);
    printf("%s",line);
    printf("\n");
    printf("-----------------------------------------------\n\n");
    
    fclose(file);

    return 0;
}

int interfaceQ5(int n_users, char* data_inicio, char* data_fim, CATUSER catuser, CATCOMMITS catcommits)
{
    char* idata = (char*)malloc(20);
    char* fdata = (char*)malloc(20);
    FILE *output = NULL;
    printf("--------------------------- Query 5 ---------------------------\n");
    printf("Insira o número de utilizadores a apresentar(0 para cancelar): \n");
    scanf("%d",&n_users);
    if (n_users == 0) return 0;
    QUERY* query = malloc(sizeof(QUERY)*n_users);
    int r;
    do
    {
        printf("Insira a data de início a apresentar(aaaa-mm-dd): \n");
        scanf("%s",idata);
        strcat(idata," 00:00:00");
        data_inicio = idata;
        r = check_Time(data_inicio);
        if (r!=1) printf("Data inválida, tente novamente!\n");
    } while (r!=1);
    
    do
    {
        printf("Insira a data de fim a apresentar(aaaa-mm-dd): \n");
        scanf("%s",fdata);
        strcat(fdata," 00:00:00");
        data_fim = fdata;
        r = check_Time(data_fim);
        if (r!=1) printf("Data inválida, tente novamente!\n");
    } while (r!=1);

    query5(n_users, data_inicio, data_fim, catuser, catcommits, output, query);

    submenu(5, n_users, query);

    freeQueries (query, n_users);
    free(query);
    free(idata);
    free(fdata);

    return 0;
}

int interfaceQ6(int n_users, char* linguagem, CATUSER catuser, CATREPOS catrepos, CATCOMMITS catcommits)
{
    char* ling = (char*)malloc(20);
    FILE *output = NULL;
    printf("--------------------------- Query 6 ---------------------------\n");
    printf("Insira o número de utilizadores a apresentar(0 para cancelar): \n");
    scanf("%d",&n_users);
    if (n_users == 0) return 0;
    QUERY* query = malloc(sizeof(QUERY)*n_users);

    printf("Insira a linguagem a apresentar: \n");
    scanf("%s",ling);
    linguagem = ling;
    
    query6(n_users, linguagem, catuser, catcommits, catrepos, output, query);
    
    if(getQueryId(query[0])==0) printf("Linguagem inexistente\n");
    else 
    {
        submenu(6,n_users,query);
        freeQueries (query, n_users);
        free(query);
    }

    free(ling);

    return 0;
}

int interfaceQ7(char* data_inicio, CATREPOS catrepos, CATCOMMITS catcommits)
{
    int i=0, max_len = 500000, len;
    char buff[max_len];
    char* buff2 = NULL;
    char* data = (char*)malloc(20);
    FILE* file = fopen("saida/fquery7.txt", "w+");
    if (file == NULL)
    {
        printf("Ficheiro inexistente!\n");
        return -1;
    }

    printf("----------------------------- Query 7 -----------------------------\n");
    int r;
    do
    {
        printf("Insira a data de início a apresentar(aaaa-mm-dd)(0 para cancelar): \n");
        scanf("%s",data);
        if (strcmp(data,"0") == 0) return 0;
        strcat(data," 00:00:00");
        data_inicio = data;
        r = check_Time(data_inicio);
        if (r!=1) printf("Data inválida, tente novamente!\n");
    } while (r!=1);
    printf("-------------------------------------------------------------------\n");

    query7(data_inicio, catcommits, catrepos, file);

    fseek(file, 0, SEEK_SET);

    for(len=0;fgets(buff, max_len, file);len++);

    QUERY* query = malloc(sizeof(QUERY)*len);

    fseek(file, 0, SEEK_SET);

    while(fgets(buff, max_len, file))
    {
        buff2 = buff;
        query[i] = build_query(&buff2,9,NULL);
        i++;
    }

    submenu(7, len, query);

    freeQueries (query, len);

    free(query);

    free(data);

    fclose(file);

    return 0;
}

int interfaceQ8(int n_users, char* data_inicio, CATREPOS catrepos)
{
    char* data = (char*)malloc(20);
    FILE* output = NULL;
    
    printf("-------------------------- Query 8 -------------------------\n");
    printf("Insira o número de linguagens a apresentar(0 para cancelar): \n");
    scanf("%d",&n_users);
    if (n_users == 0) return 0;
    QUERY* query = malloc(sizeof(QUERY)*n_users);
    int r;
    do
    {
        printf("Insira a data de início a apresentar(aaaa-mm-dd): \n");
        scanf("%s",data);
        strcat(data," 00:00:00");
        data_inicio = data;
        r = check_Time(data_inicio);
        if (r!=1) printf("Data inválida, tente novamente!\n");
    } while (r!=1);

    query8(n_users, data_inicio, catrepos, output, query);

    submenu(8, n_users, query);

    freeQueries (query, n_users);

    free(query);

    free(data);

    return 0;
}

int interfaceQ9(int n_users)
{
    FILE *file = fopen("saida/fquery9.txt", "r");
    if (file == NULL)
    {
        printf("Ficheiro inexistente!\n");
        return -1;
    }

    int i=0, max_len = 500000;
    char buff[max_len];
    char* buff2 = NULL;

    printf("-------------------------- Query 9 ---------------------------\n");
    printf("Insira o número de utilizadores a apresentar(0 para cancelar): \n");
    scanf("%d",&n_users);
    if (n_users == 0) return 0;
    
    QUERY* query = malloc(sizeof(QUERY)*n_users);

    for (i=0;i<n_users;i++)
    {
        fgets(buff, max_len, file);
        buff2 = buff;
        query[i] = build_query(&buff2,9,NULL);
    }
 
    submenu(9, n_users, query);

    freeQueries (query, n_users);

    free(query);

    fclose(file);

    return 0;
}

int interfaceQ10(int n_users)
{   
    FILE *file = fopen("saida/fquery10.txt", "r");
    if (file == NULL)
    {
        printf("Ficheiro inexistente!\n");
        return -1;
    }  

    int pag, ind=0, j, len, max_len = 500000;
    char buff[max_len];
    char opcao[30];
    char* buff2 = NULL;
    QUERY query = NULL;
    CATQUERY catquery = createCatQuery(file,buff,max_len,10);
    len = getCatQueryLength(catquery);
    
    printf("--------------------------- Query 10 --------------------------\n");
    printf("Insira o número de utilizadores a apresentar(0 para cancelar): \n");
    scanf("%d",&n_users);
    if (n_users == 0) return 0;

    do {
        j = 0; 
        query = getQueryPointer(catquery,ind);
        printf("-------------------- Repositório %d --------------------\n",getQueryRepoId(query));
        while (j<n_users && query!=NULL)
        {
            char *login = getQueryLogin(query);
            printf("| %d | %s | %d | %d |\n",getQueryId(query),login,getQueryComSize(query),getQueryRepoId(query));
            query = getQueryNext(query);
            j++;
            free(login);
        }
        
        printf("-----------------------------------------------------------\n\n");
        printf("------- Página %d de %d -------\n",ind+1,len);
        printf("P      -> Próxima Página\n");
        printf("A      -> Página Anterior\n");
        printf("S <N>  -> Saltar para página N\n\n");
        printf("Insira opção(0 para terminar): \n");
        setbuf(stdin, 0);
        fgets(opcao, 30, stdin);
        system("clear");
        buff2 = opcao;
        char* l = strdup(strsep(&buff2, " \r\n"));
        if (strcmp(l,"P")==0 && ind+1 < len) ind++;
        else if (strcmp(l,"A")==0 && ind-1 >= 0) ind--;
        else 
        {
            char* n = strdup(strsep(&buff2, " \r\n"));
            pag = atoi(n);
            if (strcmp(l,"S")==0 && n!=NULL && pag<=len) ind = pag - 1;
            free(n);
        }
        free(l);
    } while (strcmp(opcao,"0")!=0);
    freeCatQuery(catquery);
    fclose(file);
    
    return 0;
}

int interface()
{
    CATUSER catuser = NULL;
    CATREPOS catrepos = NULL;
    CATCOMMITS catcommits = NULL;

    int r = createCats(&catuser,&catrepos,&catcommits);
    if(r == -1) 
    {
        free(catuser);
        free(catrepos);
        free(catcommits); 
        return -1;
    }


    char* linguagem = NULL; 
    char* data_inicio = NULL;
    char* data_fim = NULL;
    int n_users = 0;
    int opcao;

    system("clear");
    
    do
    {   
        menu();
        printf("Insira uma opção(0 para terminar):\n");
        scanf("%d",&opcao);
        system("clear");
        switch (opcao)
        {
            case 1:
                interfaceQ1();
                break;
            case 2:
                interfaceQ2();
                break;
            case 3:
                interfaceQ3();
                break;
            case 4:
                interfaceQ4();
                break;
            case 5:
                interfaceQ5(n_users, data_inicio, data_fim, catuser, catcommits);
                break;
            case 6:
                interfaceQ6(n_users,linguagem, catuser, catrepos, catcommits);
                break;
            case 7:
                interfaceQ7(data_inicio, catrepos, catcommits);
                break;
            case 8:
                interfaceQ8(n_users, linguagem, catrepos);
                break;
            case 9:
                interfaceQ9(n_users);
                break;
            case 10:
                interfaceQ10(n_users);
                break;
            
            default:
                break;
        }
        if((opcao<1 || opcao>10) && opcao !=0) printf("Valor inválido!\n");
   
    } while(opcao != 0);

    system("clear");
    printf("End of Program!\n");

    free(linguagem);
    free(data_inicio);
    free(data_fim);

    freeCatUser(catuser);
    freeCatRepos(catrepos);
    freeCatCommits(catcommits);

    return 0;
}
