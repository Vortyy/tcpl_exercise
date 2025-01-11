/************************************************************************************
 * The C Programming Language 7-7 :
 * 
 * -> 
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#define MAXPATTERN 20
#define MAXLINE 100

void find(FILE *fp, char *fname, char *pattern, int expect, int number);

/* pretty straight forward, near to copy from chapter 5... and concate file v2 from chapter 7 for file looping */
int main(int argc, char *argv[]){
  char pattern[MAXPATTERN];
  int c, except = 0, number = 0, found = 0;
  FILE *fp;

  /* extract from the book */
  while (--argc > 0 && (*++argv)[0] == '-')
    while (c = *++argv[0])
      switch (c) {
        case 'x':
          except = 1;
          break;
        case 'n':
          number = 1;
          break;
        default:
          printf("find: illegal option %c\n", c);
          argc = 0;
          found = -1;
          break;
      }
  
  if (argc >= 1)
    strcpy(pattern, *argv);
  else 
    printf("Usage : find [-x] [-n] pattern [File ...]\n");

  if(argc == 1)
    find(stdin, "", pattern, except, number);
  else 
    while(--argc > 0)
      if((fp = fopen(*++argv, "r")) == NULL){
        fprintf(stderr, "find: can't open file %s", *argv);
        exit(1);
      } else {
        find(fp, *argv, pattern, except, number);
        fclose(fp);
      }
  return 0;
}

void find(FILE *fp, char *fname, char *pattern, int expect, int number){
  char line[MAXLINE];
  int nbline = 0;

  while(fgets(line, MAXLINE, fp) != NULL){
    ++nbline;
    if((strstr(line, pattern) != NULL) != expect){
      if(*fname)
        printf("%s - ", fname);
      if(number)
        printf("%d : ", nbline);
      printf("%s", line);
    }
  }
}
