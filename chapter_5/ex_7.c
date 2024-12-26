/************************************************************************************
 * The C Programming Language 5-3:
 * 
 * -> write a function htoi(s) -> take a string of hex decimal value and convert it
 *    to its equivalent in integer value
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAXLINES 500 /* max #lines to be sorted */
#define MAXSTOR 10000 /* max character that can be stored */

char *lineptr[MAXLINES]; /* pointers to text lines */
char linestore[MAXSTOR]; /* character array stored */

int readlines(char *lineptr[], char *linestore, int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right); /* sort input lines */

int main(){
  int nlines;

  if((nlines = readlines(lineptr, linestore, MAXLINES)) >= 0){
    qsort(lineptr, 0, nlines-1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error : input too big to sort\n");
    return 1;
  }
}

#define MAXLEN 1000 /* max length of any input line */
#define MAXSTOR 10000

int get_line(char *, int); /* get_line from ex_6.c to compile add ex_6.c */

int readlines(char *lineptr[], char *linestore, int maxlines){
  int len, nlines;
  char *p = linestore; 
  char line[MAXLEN];

  nlines = 0;
  while((len = get_line(line, MAXLEN)) > 0){
    if(nlines >= maxlines || p + len > (linestore + MAXSTOR))
      return -1;
    else {
      /*line[len-1] = '\0'; /* correct \n already done in implementation of get_line in ex_6.c */
      printf("line copied of %d : %s \n", len, line);
      strcpy(p, line);
      lineptr[nlines++] = p;
      p += len + 1; /* +1 adding ended char len is without */
      /*printf("%c - p\n", *(p - 1));*/
    }
  }

  return nlines;
}

void writelines(char *lineptr[], int nlines){
  while(nlines-- > 0)
    printf("%s\n", *lineptr++);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
  int i, last;
  void swap(char *v[], int i, int j);
  if (left >= right) /* do nothing if array contains */
    return;
  /* fewer than two elements */
  swap(v, left, (left + right)/2);
  last = left;
  
  for (i = left+1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);

  swap(v, left, last);
  qsort(v, left, last-1);
  qsort(v, last + 1, right);
}

void swap(char *v[], int d, int s){
  char *tmp;
  tmp = v[d];
  v[d] = v[s];
  v[s] = tmp;
}
