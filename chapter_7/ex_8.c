/************************************************************************************
 * The C Programming Language 7-8 :
 * 
 * -> 
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define LINEPERPAGE 50
#define HLINE "--------------------------------------------"

void filecopy(FILE *, FILE *, char *);
void header(int, char *);

/* pratically all the routine is taken from chapter 7 cat v2 */
int main(int argc, char *argv[])
{
  FILE *fp;
  char *prog = argv[0]; /* program name for errors */
  int page = 1;
  
  if (argc == 1) /* no args; copy standard input */
    filecopy(stdin, stdout, "stdin");
  else
    while (--argc > 0)
      if ((fp = fopen(*++argv, "r")) == NULL) {
        fprintf(stderr, "%s: can't open %s\n", prog, *argv);
        exit(1);
      } else {
        filecopy(fp, stdout, *argv);
        fclose(fp);
      }
  
  if (ferror(stdout)) {
    fprintf(stderr, "%s: error writing stdout\n", prog);
    exit(2);
  }

  exit(0);
}

/* print a header with the current page */
void header(int page, char *fname){
  printf("\n%.15s Title : %s ---- page %d %.15s\n", HLINE, fname, page, HLINE);
}

void filecopy(FILE *fpi, FILE *fpo, char * fpiname){ /* near to chapter 7 filecopy just add file input name */
  int nbline = 1, page = 1;
  char line[MAXLINE];
  header(page, fpiname);
  while(fgets(line, MAXLINE, fpi) != NULL){
    fputs(line, fpo);
    if(++nbline > LINEPERPAGE){
      header(++page, fpiname);
      nbline = 1;
    }
  }
}
