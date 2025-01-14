/************************************************************************************
 * The C Programming Language 8-1 :
 * 
 * -> Rewrite (chapter_7/ex_8.c) using read, write, open and close using their <unistd.h>
 *    equivalent, and determine the relative speeds of the two version 
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

/*As i said in ch7 ex5 there is 3 file opened when a program start to run in UNIX
* stdin, stdout, stderr when a program is launch 'prog <infile >outfile' this overwrite
* the stdin and stdout file descriptor to select infile and outfile their filedescriptor
* id correspond to 0 -> in, 1 -> out, 2 -> err*/

#include <fcntl.h> /* works for open and creates */
#include <unistd.h> /* unistd useful for close, read and write */
#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>
/*#include <sys/file.h> or fcntl.h on V UNIX systems */

/* the fun part is that read, write routine any number can be used commons value are 
* 1 bytes, 1024, 4096 but more can be used and will be more efficient du to fact that
* less syscall are required */

/* BUFSIZE is an optimal value for the local system */  

/* limit of open were often 20 */

#define MAXLINE 100
#define LINEPERPAGE 50
#define HLINE "--------------------------------------------"

struct field {
  unsigned is_test : 1;
  unsigned is_testing : 1;
};

void filecopy(int, int, char *);

/* this routine goes a lot faster than fopen one's */
int main(int argc, char *argv[]){
  printf("BUFSIZ - %d bytes\n", BUFSIZ);
  printf("field size --> %lu\n", sizeof(struct field));

  int fd;
  char *prog = argv[0]; /* program name for errors */
  int page = 1;
  
  if (argc == 1) /* no args; copy standard input */
    filecopy(0, 1, "stdin");
  else
    while (--argc > 0)
      if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
        fprintf(stderr, "%s: can't open %s\n", prog, *argv);
        exit(1);
      } else {
        filecopy(fd, 1, *argv);
        close(fd);
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

void filecopy(int fdi, int fdo, char * fpiname){ /* near to chapter 7 filecopy just add file input name */
  int nbline = 1, page = 1;
  char buf[BUFSIZ];
  int n = 0;
  header(page, fpiname);
  while((n = read(fdi, buf, BUFSIZ)) > 0){
    if(write(fdo, buf, n) != n) // meaning that there is an error if n bytes are not written 
      printf("error while writing...\n");
  }
}
