/************************************************************************************
 * The C Programming Language 5-8:
 * 
 * -> There is no error checking in day_of_year or month_day. Remedy this defect.
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>
#include <sys/types.h>

/* small notice hint there is 366 day in leap year and 365 in non-leap year */
#define isLeap(x) (x%4 == 0 && x%100 != 0 || year%400 == 0) /* a leap year is every 4 years except every 100 years unless it's a 400 years multiple */

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
  int i, leap;
  leap = isLeap(year); 
  if(month < 1 || month > 12 || day < 1 || day > daytab[leap][month])
    return -1;
  for (i = 1; i < month; i++)
    day += daytab[leap][i];
  return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;
  leap = isLeap(year);
  for (i = 1; i <= 12 && yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];

  if(i > 12){
    *pday = -1;
    *pmonth = -1;
  }else{
    *pmonth = i;
    *pday = yearday;
  }
}

int main(){
  int pday, pmonth;
  int year = 1999;
  int yearday = 365;

  month_day(year, yearday, &pmonth, &pday);
  printf("day %d of year %d is %d/%d/%d\n", yearday, year, pday, pmonth, year);
  printf(" --> %d <--\n", day_of_year(year, 7, 19));
}
