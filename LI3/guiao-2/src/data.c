#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libs/data.h"

struct data
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

DATA build_data(char* data)
{
    DATA d = malloc(sizeof(struct data));
    char* buff2 = data;

    d->year = atoi(strsep(&buff2, " -:"));
    d->month = atoi(strsep(&buff2, " -:"));
    d->day = atoi(strsep(&buff2, " -:"));
    if(!buff2) d->hour=d->minute=d->second=0;
    else
    {
        d->hour = atoi(strsep(&buff2, " -:"));
        d->minute = atoi(strsep(&buff2, " -:"));
        d->second = atoi(strsep(&buff2, " -:"));
    }
    return d;
}

int compareData(DATA a, DATA b)  //b>a
{
    if(a->year>b->year) return 0;
    if(a->year<b->year) return 1;
    if(a->month>b->month) return 0;
    if(a->month<b->month) return 1;
    if(a->day>b->day) return 0;
    if(a->day<b->day) return 1;
    if(a->hour>b->hour) return 0;
    if(a->hour<b->hour) return 1;
    if(a->minute>b->minute) return 0;
    if(a->minute<b->minute) return 1;
    if(a->second>b->second) return 0;
    return 1; //(a->second<b->second) 
}