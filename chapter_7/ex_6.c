/************************************************************************************
 * The C Programming Language 7-6 :
 * 
 * -> Write a program to compare two files, printing the first line where they differ.
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

/* interesting point when including stdio.h --> it creates 3 files (stdin, stdout, stderr) that 
* are used to get writting, print output et error */
#include <stdio.h> 
#include <string.h>

/* fopen with w mode with a already existing file will replace it, you need to use a append */
/* mode are a, w, r : append, write, read */

/* a lot of OS have a limit in nb file that can be opened by a program that why fclose is usefull
 * and it flush the putc() buffer */

/* and is automatically called when a prog ends */

#define MAXLINE 150

void compare(FILE *, FILE *);

int main(int argc, char *argv[]){
  if(argc > 2){
    char *pname = argv[0]; /* usefull when you looking where come from an error */

    FILE *f = fopen(argv[1], "r");
    FILE *fc = fopen(argv[2], "r");

    if(f == NULL || fc == NULL){
      fprintf(stderr, "%s : error while trying to open files\n", pname);
      return 1;
    }

    compare(f, fc);
    return 0;
  } 
  printf("not enough args ! need to specify to 2 files in current directory\n");
  return 1;
}

void compare(FILE *f, FILE *fc){
  int nbline = 0;
  int diff = 0, end = 0; /* marker end of a file and diff */
  char linef[MAXLINE], linefc[MAXLINE];
  char  *r1, *r2;

  while(!diff && !end){
    r1 = fgets(linef, MAXLINE, f);
    r2 = fgets(linefc, MAXLINE, fc);

    if(r1 == NULL && r2 != NULL){ /* f is ended but not fc */
      end = 1;
      printf("end of the first file at line : %d\n", nbline); 
    }
    else if (r2 == NULL && r1 != NULL){ /* fc is ended but not f */
      end = 1;
      printf("end of the second file at line : %d\n", nbline);
    }
    else if(strcmp(linefc, linef) != 0){
      printf("line %d : %s", nbline, linef);
      diff = 1; 
    } else
      if(r1 == NULL && r2 == NULL) /* both ended at same and equal until the end */
        end = 1;
      else
        nbline++;
  }
}
