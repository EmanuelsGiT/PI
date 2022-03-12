#include <stdio.h>
#include "../libs/queries_estatistic.h"
#include "../libs/queries_parameterizable.h"
#include "../libs/catUser.h"
#include "../libs/catCommits.h"
#include "../libs/catRepos.h"
#include "../libs/queriesAux.h"
#include "../libs/guiao2.h"
#include <glib.h>
#include <time.h>
#include "../libs/mainEx1.h"
#include "../libs/mainEx2.h"

double testQ1 (CATUSER catuser)
{

  time_t start_time, end_time;
  double delta;
  double r;
  FILE *fquery = fopen("saida/test1.txt", "w");
  if(fquery==NULL) return -1;

  time(&start_time);
  query1(catuser, fquery);
  time(&end_time);
  delta = difftime(end_time, start_time);
  r = delta;

  fclose(fquery);
  return r;
}

double testQ2 (CATCOMMITS catcommits, CATREPOS catrepos)
{
  time_t start_time, end_time;
  double delta;
  double r;

  FILE *fquery = fopen("saida/test2.txt", "w");
  if(fquery==NULL) return -1;

  time(&start_time);
  query2(catcommits, catrepos, fquery);
  time(&end_time);
  delta = difftime(end_time, start_time);
  r = delta;

  fclose(fquery);
  return r;
}

double testQ3 (CATUSER catuser, CATCOMMITS catcommits)
{
  time_t start_time, end_time;
  double delta;
  double r;

  FILE *fquery = fopen("saida/test3.txt", "w");
  if(fquery==NULL) return -1;

  time(&start_time);
  query3(catuser, catcommits, fquery);
  time(&end_time);
  delta = difftime(end_time, start_time);
  r = delta;

  fclose(fquery);
  return r;
}

double testQ4 ()
{
  time_t start_time, end_time;
  double delta;
  double r;

  FILE *fquery = fopen("saida/test4.txt", "w");
  if(fquery==NULL) return -1;

  time(&start_time);
  query4(fquery);
  time(&end_time);
  delta = difftime(end_time, start_time);
  r = delta;

  fclose(fquery);
  return r;
}

double testQ5 (int n_users, char* data_inicio, char* data_fim, CATUSER catuser, CATCOMMITS catcommits)
{
  time_t start_time, end_time;
  double delta;
  double r;

  FILE *fquery = fopen("saida/test5.txt", "w");
  if(fquery==NULL) return -1;

  time(&start_time);
  query5(n_users, data_inicio, data_fim, catuser, catcommits, fquery, NULL);
  time(&end_time);
  delta = difftime(end_time, start_time);
  r = delta;

  fclose(fquery);
  return r;
}

double testQ6 (int n_users, char* lang, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos)
{
  time_t start_time, end_time;
  double delta;
  double r;

  FILE *fquery = fopen("saida/test6.txt", "w");
  if(fquery==NULL) return -1;

  time(&start_time);
  query6(n_users, lang, catuser, catcommits, catrepos, fquery, NULL);
  time(&end_time);
  delta = difftime(end_time, start_time);
  r = delta;

  fclose(fquery);
  return r;
}

double testQ7 (char *data_inicio, CATCOMMITS catcommits, CATREPOS catrepos)
{
  time_t start_time, end_time;
  double delta;
  double r;

  FILE *fquery = fopen("saida/test7.txt", "w");
  if(fquery==NULL) return -1;

  time(&start_time);
  query7(data_inicio, catcommits, catrepos, fquery);
  time(&end_time);
  delta = difftime(end_time, start_time);
  r = delta;

  fclose(fquery);
  return r;
}

double testQ8 (int n_users, char *data_inicio, CATREPOS catrepos)
{
  time_t start_time, end_time;
  double delta;
  double r;

  FILE *fquery = fopen("saida/test8.txt", "w");
  if(fquery==NULL) return -1;

  time(&start_time);
  query8(n_users, data_inicio, catrepos, fquery, NULL);
  time(&end_time);
  delta = difftime(end_time, start_time);
  r = delta;

  fclose(fquery);
  return r;
}

double testQ9 (int n_users, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos)
{
  time_t start_time, end_time;
  double delta;
  double r;

  FILE *fquery = fopen("saida/test9.txt", "w");
  if(fquery==NULL) return -1;

  time(&start_time);
  query9 (n_users, catuser, catcommits, catrepos, fquery);
  time(&end_time);
  delta = difftime(end_time, start_time);
  r = delta;

  fclose(fquery);
  return r;
}

double testQ10 (int n_users, CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos)
{
  time_t start_time, end_time;
  double delta;
  double r;

  FILE *fquery = fopen("saida/test10.txt", "w");
  if(fquery==NULL) return -1;

  time(&start_time);
  query10(n_users, catuser, catcommits, catrepos, fquery);
  time(&end_time);
  delta = difftime(end_time, start_time);
  r = delta;

  fclose(fquery);
  return r;
}

void testAll (CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, double *test)
{
  char* dataInit = NULL;
  char* dataEnd = NULL;

  test[0] = testQ1(catuser);

  test[1] = testQ2(catcommits, catrepos);

  test[2] = testQ3(catuser, catcommits);

  test[3] = testQ4();

  dataInit = strdup("2010-01-01");
  dataEnd = strdup("2015-01-01");
  test[4] = testQ5(100, dataInit, dataEnd, catuser, catcommits);
  free(dataInit);
  free(dataEnd);

  test[5] = testQ6(5, "Python", catuser, catcommits, catrepos);

  dataInit = strdup("2014-04-25");
  test[6] = testQ7(dataInit, catcommits, catrepos);
  free(dataInit);

  dataInit = strdup("2016-10-05");
  test[7] = testQ8(3, dataInit, catrepos);
  free(dataInit);

  test[8] = testQ9(4, catuser, catcommits, catrepos);

  test[9] = testQ10(50, catuser, catcommits, catrepos);

}

void testAllNTimes (CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos)
{
  int i, j, n;
  printf("How many times?\n");
  scanf("%d", &n);
  double test[n][10];
  int max, min;
  double sum;

  for(i=0; i<n; i++)
    for(j=0; j<10; j++)
      test[i][j] = 0;

  for(i=0; i<n; i++)
  {
    testAll(catuser,catcommits,catrepos,test[i]);
    printf("%dº test done\n", i+1);
  }
  
  printf("All tests done\n");

  for(i=0; i<10; i++)
  {
    max = 0;
    min = 0;
    sum = 0;

    for(j=0; j<n; j++)
    {
      if( test[max][i] <= test[j][i]) max = j;
      if( test[min][i] >  test[j][i]) min = j;
    }
    
    for(j=0; j<n; j++)
    {
      if(j!=max && j!=min) 
      {
        sum+=test[j][i];
      }
    }
    printf("Query %d: %.3f\n", i+1, sum/(n-2));
  }

}

int testQuery (CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos, int queryID, int target)
{
  int r = -1;
  int time = 0;
  char* dataInit = NULL;
  char* dataEnd = NULL;

  switch (queryID)
  {
    case -1:
      break;
    case 1:
      time = testQ1 (catuser);
      break;

    case 2:
      time = testQ2 (catcommits, catrepos);
      break;

    case 3:
      time = testQ3 (catuser, catcommits);
      break;

    case 4:
      time = testQ4 ();
      break;

    case 5:
      dataInit = strdup("2010-01-01");
      dataEnd = strdup("2015-01-01");
      time = testQ5 (100, dataInit, dataEnd, catuser, catcommits);
      free(dataInit);
      free(dataEnd);
      break;

    case 6:
      time = testQ6 (5, "Python", catuser, catcommits, catrepos);
      break;

    case 7:
      dataInit = strdup("2014-04-25");
      time = testQ7 (dataInit, catcommits, catrepos);
      free(dataInit);
      break;

    case 8:
      dataInit = strdup("2016-10-05");
      time = testQ8 (3, dataInit, catrepos);
      free(dataInit);
      break;

    case 9:
      time = testQ9 (4, catuser, catcommits, catrepos);
      break;

    case 10:
      time = testQ10 (50, catuser, catcommits, catrepos);
      break;

    default:
      printf("INVALID QUERY, PLEASE INPUT A QUERY ID BETWEEN 1 AND 10\n");
      time = target + 1;
      break;
  }
    
  if(target == 0) r = time;
  else if(time <= target) r = 0;

  return r;
}

int time_UI (CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos)
{
  int target;
  double r;
  int query = 0;  
  printf("Enter query -1 to exit, enter target as 0 to show raw time\n"); 
  while(query != -1)
  {
    query = 0;
    printf("Please enter query ID:\n");
    scanf("%d", &query);
    if(query > 0 && query <= 10)
    {
      printf("Please enter target time (seconds):\n");
      scanf("%d", &target);
      r = testQuery(catuser, catcommits, catrepos, query, target);
      if(r == -1)
          printf("Query %d takes longer than %d seconds\n", query, target); 
      else if(target == 0) 
          printf("Query %d took %.3f seconds\n", query, r);
      else 
          printf("Query %d passed the test\n", query);
    }
  }

  printf("Exiting\n\n");

  return 0;
}

int compareFiles(FILE *file1, FILE *file2)
{
  int error = 0;
  char buff[550000];
  char buff2[550000];

  while(fgets(buff,550000,file1) && fgets(buff2,550000,file2))
    if(strcmp(buff,buff2)!=0) 
      error++;

  return error;
}

int tester_UI(CATUSER catuser, CATCOMMITS catcommits, CATREPOS catrepos)
{
  int q = 0, r;
  FILE *f = NULL;
  FILE *test = NULL;
  char *dataInit = NULL;
  char *dataEnd = NULL;

  while(q != -1)
  {
    q = 0;
    printf("Write the query you want to test, -1 to go back\n");
    scanf("%d", &q);

    test = fopen("saida/test.txt", "w+");
    switch (q)
    {
      case -1: 
        break;

      case 1:
        query1(catuser, test);
        f = fopen("entrada/expectedOutput1.txt", "r");
        break;

      case 2:
        query2(catcommits, catrepos, test);
        f = fopen("entrada/expectedOutput2.txt", "r");
        break;

      case 3:
        query3(catuser, catcommits, test);
        f = fopen("entrada/expectedOutput3.txt", "r");
        break;

      case 4:
        query4(test);
        f = fopen("entrada/expectedOutput4.txt", "r");
        break;

      case 5:
        dataInit = strdup("2010-01-01");
        dataEnd = strdup("2015-01-01");
        query5(100, dataInit, dataEnd, catuser, catcommits, test, NULL);
        f = fopen("entrada/expectedOutput5.txt", "r");
        free(dataInit);
        free(dataEnd);
        break;

      case 6:
        query6(5, "Python", catuser, catcommits, catrepos, test, NULL);
        f = fopen("entrada/expectedOutput6.txt", "r");
        break;

      case 7:
        dataInit = strdup("2014-04-25");
        query7( dataInit, catcommits, catrepos, test);
        f = fopen("entrada/expectedOutput7.txt", "r");
        free(dataInit);
        break;

      case 8:
        dataInit = strdup("2016-10-05");
        query8(3,  dataInit, catrepos, test, NULL);
        f = fopen("entrada/expectedOutput8.txt", "r");
        break;

      case 9:
        query9(4, catuser, catcommits, catrepos, test);
        f = fopen("entrada/expectedOutput9.txt", "r");
        break;

      case 10:
        query10(50, catuser, catcommits, catrepos, test);
        f = fopen("entrada/expectedOutput10.txt", "r");
        break;

      default:
        printf("Invalid Query\n");
        break;
    }
    if(q!=-1)
    {
      fseek(test, 0, SEEK_SET);
      
      r = compareFiles(test, f);

      if(r == 0) printf("Query is working as intended\n");
      else printf("Query has failed\n");

      fclose(f);
    }
    fclose(test);
  }
  
  printf("Exiting...\n\n");

  return 0;
}

int main()
{
  exercicio1();
  exercicio2();

  CATUSER catuser = NULL;
  CATREPOS catrepos = NULL;
  CATCOMMITS catcommits = NULL;
  int r = createCats(&catuser,&catrepos,&catcommits);
  if(r == -1)  return r;
  char c;
  system("clear");
  while(c != 'E' && c != 'e')
  {
    printf("T - Time Tests\nF - Functionality Tests\nA - All Time Tests\n\nE - Exit program\n");
    setbuf(stdin, 0);
    scanf("%c", &c);
    system("clear");
    if(c == 'T' || c == 't') time_UI(catuser, catcommits, catrepos);
    else if(c == 'F' || c == 'f') tester_UI(catuser, catcommits, catrepos);
    else if(c == 'A' || c == 'a') testAllNTimes(catuser,catcommits,catrepos);
  }

  printf("Closing\n");
  freeCatUser (catuser);
  freeCatCommits (catcommits);
  freeCatRepos (catrepos);

  return 0;
}
