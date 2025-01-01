/************************************************************************************
 * The C Programming Language 5-14, 5-15, 5-16 and 5-17 :
 * WARNING THIS EXERCISE NEED TO BE COMPILED WITH ex_6.c TO GET get_line() 
 * 
 * 5-14 -> Modify the sort program to handle a -r flag, which indicates sorting in 
 *         reverse (decreasing) order. Be sure that -r works with -n.
 *
 * 5-15 -> Add the option -f to fold upper and lower case together, so that case 
 *         distinctions are not made during sorting; for example, a and A compare 
 *         equal.
 *
 * 5-16 -> Add the -d (``directory order'') option, which makes comparisons only on 
 *         letters, numbers and blanks. Make sure it works in conjunction with -f.
 *
 * 5-17 -> Add a field-searching capability, so sorting may bee done on fields within 
 *         lines, each field sorted according to an independent set of options.
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#define ARG_MACRO(name) {cmp_fct_name=#name;cmp_fct=name;cmp_lock++;}

#define MAXLINES 500  /* max #lines to be sorted */
#define MAXSTOR 10000 /* max character that can be stored */

char *lineptr[MAXLINES]; /* pointers to text lines */
char linestore[MAXSTOR]; /* character array stored */

int readlines(char *lineptr[], char *linestore, int nlines);
void writelines(char *lineptr[], int nlines);

void q_sort(void *arr[], int left, int right, int (*comp) (void *, void *), int reverse); /* sort input lines */
int num_cmp(char *, char *);                                                              /* compare numericaly to string */
int dir_cmp(char *, char *);                                                              /* compare only alphanumeric and blanck char */

void substring(char *);

int start_pos = -1;
int end_pos = 1;

int main(int argc, char *argv[]){
  int nlines;
  int reverse = 0;

  void *cmp_fct = strcmp;
  char *cmp_fct_name = "strcmp";
  int cmp_lock = 0;

   while(argc-- > 1){ /* reads arguments */
    if(*argv[argc] == '-')
      while(*++argv[argc]){
        if(*argv[argc] == 'n' && cmp_lock == 0)
          ARG_MACRO(num_cmp)
        if(*argv[argc] == 'f' && cmp_lock == 0)
          ARG_MACRO(strcasecmp)
        if(*argv[argc] == 'd' && cmp_lock == 0)
          ARG_MACRO(dir_cmp)
        if(*argv[argc] == 'r')
          reverse = 1;
        if(*argv[argc] == isalnum(*argv[argc])){
          start_pos = atoi(argv[argc]);
          *argv[argc] += strlen(argv[argc]);
        }
      }
    if(*argv[argc] == '+'){
      end_pos = atoi(++argv[argc]);
    }
  }

  printf("cmp_fct: %s, reverse : %d\n\n", cmp_fct_name, reverse);

  if((nlines = readlines(lineptr, linestore, MAXLINES)) >= 0){
    q_sort((void **) lineptr, 0, nlines-1, (int (*) (void *, void *)) cmp_fct, reverse);
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
      /*printf("line copied of %d : %s \n", len, line);*/
      if(start_pos != -1 && end_pos != -1)
        substring(line);

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

/* q_sort: sort v[left]...v[right] into increasing order */
void q_sort(void *v[], int left, int right, int (*comp) (void *, void *), int reverse)
{
  int i, last;
  void swap(void *v[], int i, int j);
  if (left >= right) /* do nothing if array contains */
    return;
  /* fewer than two elements */
  swap(v, left, (left + right)/2);
  last = left;
  
  for (i = left+1; i <= right; i++)
    if(reverse == 1){
      if ((*comp)(v[i], v[left]) > 0)
        swap(v, ++last, i);
    }else
      if ((*comp)(v[i], v[left]) < 0)
        swap(v, ++last, i);

  swap(v, left, last);
  q_sort(v, left, last-1, comp, reverse);
  q_sort(v, last + 1, right, comp, reverse);
}

int num_cmp(char *s1, char *s2){
  double v1, v2;
  v1 = atof(s1);
  v2 = atof(s2);
  if(v1 == v2)
    return 0;
  else
    return (v1 < v2) ? -1 : 1;
}

int dir_cmp(char *s1, char *s2){
  while(!isalnum(*s1) && *s1 != ' ' && *s1 != '\0')
    s1++;
  while(!isalnum(*s2) && *s2 != ' ' && *s2 != '\0')
    s2++;

  for(; *s1 == *s2; s1++, s2++){
    while(!isalnum(*s1) && *s1 != ' ' && *s1 != '\0')
      s1++;
    while(!isalnum(*s2) && *s2 != ' ' && *s2 != '\0')
      s2++;
    if(*s1 == *s2 && *s1 == '\0')
      return 0;
  }
  
  return *s1 - *s2;
}

void substring(char *str){
  char *p_str = str;
  int len = strlen(str);
  if(end_pos < len)
    for(int i = start_pos; i < end_pos; i++)
      *p_str++ = *(str + i);
  else 
    printf("error : range is too big for input...");
  *p_str = '\0'; 
}

void swap(void *v[], int d, int s){
  void *tmp;
  tmp = v[d];
  v[d] = v[s];
  v[s] = tmp;
}
