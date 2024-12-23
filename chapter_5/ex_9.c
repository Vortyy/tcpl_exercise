/************************************************************************************
 * The C Programming Language 5-3:
 * 
 * -> write a function htoi(s) -> take a string of hex decimal value and convert it
 *    to its equivalent in integer value
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

/* small notice hint there is 366 day in leap year and 365 in non-leap year */
#include <stdio.h>

#define isLeap(x) (x%4 == 0 && x%100 != 0 || year%400 == 0) /* a leap year is every 4 year except every 100 year and 400 */

static char *name[] = {"Illegal test", "jan", "feb", "mar"};

static char *daytab[2] = {
  (char []){0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  (char []){0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
  int i, leap;
  leap = isLeap(year);
  char *p = daytab[leap];

  if(month < 1 || month > 12 || day < 1 || day > *(p + month))
    return -1;
  for (i = 1; i < month; i++)
    day += *(p + i); /* bcs for loop start at one */
  return day;
}
/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;
  leap = isLeap(year);
  char *p = daytab[leap];

  for (i = 1; i <= 12 && yearday > *(p + i); i++)
    yearday -= *(p + i);

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
  int yearday = 354;

  month_day(year, yearday, &pmonth, &pday);
  printf("day %d of year %d is %d/%d/%d\n", yearday, year, pday, pmonth, year);
  printf(" --> %d <--\n", day_of_year(year, 7, 19));
}
