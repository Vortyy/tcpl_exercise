/************************************************************************************
 * The C Programming Language 7-3:
 * 
 * -> Write a private version of scanf analogous to minprintf from the previous
 *    section.
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

int myscanf(char *fmt, ...);
void get_word(char *);
int float_error(char *);

char word[MAXWORD];

/* this my minscanf version that use 2 routines to work and handle float, double and int */
int main(){
  int i, j, k;
  double d;
  int n = myscanf("%f", &d);
  /*int n = scanf("%lf", &d);*/
  /*printf("i : %d, j: %d, k: %d, number found : %d\n", i, j, k, n);*/
  printf("d : %lf, scanf=%d\n", d, n);
  return 0;
}

int myscanf(char *fmt, ...){
  va_list ap;
  char *p;
  int *ip;
  double *dp;
  int stored = 0;
  int error = 0;

  va_start(ap, fmt);
  for(p = fmt; *p; p++){
    if(*p == '%'){
      switch (*++p) {
        case 'd': /* int */
          ip = va_arg(ap, int *);
          /*printf("%p\n", ip);*/
          get_word(word);
          *ip = atoi(word);
          if(*ip == 0 || (strlen(word) == 1 && word[0] != '0')) /* because atoi give 0 in error case verify a true 0 */
            error = 1;
          else 
            stored++;
          break;
        case 'f': /* float */
          dp = va_arg(ap, double *);
          get_word(word);
          if(!float_error(word))
            error = 1;
          else {
            *dp = atof(word);
            stored++;
          } 
          break;
        default: 
          printf("Format unknown...\n");
          return stored;
      } 

      if(error == 1)
        break;
    }
  }

  return stored;
}

int float_error(char *word){ /* check if there another thing than a number or '.' in the word */
  char *s = word;
  while(isdigit(*s) || *s == '.')
    s++;
  return *s == '\0'; 
}

void get_word(char *word){ /* just get char until the next non-alpha num char */
  char c;
  char *w = word;
  while(!isspace(c = getchar()) || c == '.') /* for float conversion */ 
    *w++ = c;
  *w = '\0';
}
