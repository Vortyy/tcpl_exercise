/************************************************************************************
 * The C Programming Language 5-6:
 * 
 * -> Rewrite appropriate programs from earlier chapters and exercises with pointers 
 *    instead of array indexing. (i choose get_line and itoa)
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <ctype.h>
#include <stdio.h>

#define MAXLINE 100

int get_line(char *s, int lim){
  int c;
  char *t = s; /* starting point length */
  while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
    *s++ = c;
  *s = '\0';

  //printf("size %ld \n", (s - t));
  return (s - t); /*ending char add*/
}

int atoi_(char *s){
  int n = 0;
  int sign = 1;
  
  if(*s == '-'){
    sign = -1;
    s++;
  }

  for(; isdigit(*s); s++)
    n = 10 * n + (*s - '0');

  return n * sign;
}

/*int main(){*/
/*  char line[MAXLINE];*/
/*  while(get_line(line, MAXLINE) > 0){*/
/*    printf("%d\n", atoi_(line));*/
/*  } */
/*  return 0;*/
/*}*/
