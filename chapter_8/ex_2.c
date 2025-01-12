/************************************************************************************
 * The C Programming Language 8-2, 8-3 and 8-4 :
 * 
 * -> Write a program to print a set of files, starting each new one on a new page,
 *    with a title and a running page count for each file.
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/
// ----------------------------------- MYSTDIO.H ---------------------------------- //

#define NULL 0
#define EOF (-1)
#define BUFSIZ 8192  /* based on previous ex where on my local BUFSIZE is set to 8192 */
#define OPEN_MAX 20   /* max #files open at once */

/* when you need to be really carefull to memory usage you can choose to use bit manipulation
 * or field. Fields work as struct inside were can split a 'word' in bit following the use 
 * of :nb_bit needed 
 * in this example there is 5 bits that correspond to 5 attribute (padded to the
 * the first type casted here int then 32bits (with still 27 available))
 * unsigned is just to protection but not really need */
struct flag_field { /* we could cast them as char to make it small since we need only 5bits */
  unsigned is_read : 1;   /* file open for reading */
  unsigned is_write : 1;  /* file open for writing */ 
  unsigned is_unbuf : 1;  /* file is unbuffered */
  unsigned is_eof : 1;    /* EOF has occured on this file */
  unsigned is_err : 1;    /* error occured on this file */
};

#define _setflags(r,w,u) {.is_read = (r), .is_write = (w), .is_unbuf = (u), .is_eof = 0, .is_err = 0}

/* Typedef work a new type definition make good type definition helps on 2 points :
* 1st --> better portability because you need to only change primary data inside typedef 
*         not the all definition
* 2nd --> better readability and documentation */
typedef struct _iobuf{
  int cnt;                  /* char left */
  char *ptr;                /* next char pos */
  char *base;               /* location of the buffer */
  struct flag_field flags;  /* mode of file access, here it is the same size of int 4bytes */
  int fd;                   /* file descriptor */
} FILE;

extern FILE _iob[OPEN_MAX]; /* here it's a declaration (no memory set aside) not a definition 
                            + they must be only one definition for  all prog using this vars !!! */

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) ((p)->flags.is_err == 1)
#define ferror(p) ((p)->flags.is_err == 1)
#define fileno(p) ((p)->fd)

/* here the precedence of -> is higher than -- then the ptr is first dereferenced then apply -- on value cnt */
#define getc(p) (--(p)->cnt >= 0 \
              ? *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 \
              ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin) /* insane wrapper tricks with macro this blow my mind */
#define putchar(x) putc((x), stdout) /* same here */

// ----------------------------------- MYSTDIO.H ---------------------------------- //

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define PERMS 0666 /* RW for all groups */

struct flag_field const _read = _setflags(1, 0, 0);
struct flag_field const _write = _setflags(0, 1, 0);
struct flag_field const _wu = _setflags(0, 1, 1);

FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr */ 
  {0, (char *) 0, (char *) 0, _read, 0},
  {0, (char *) 0, (char *) 0, _write, 0},
  {0, (char *) 0, (char *) 0, _wu, 0},
};

/* while stdio.h is not included the warning is not a big deal just telling me that will be a conflic */
FILE *fopen(char *name, char *mode){
  int fd;
  FILE *fp;

  if(*mode != 'r' && *mode != 'w' && *mode != 'a') /* unknows mode error */
    return NULL;

  for(fp = _iob; fp < _iob + OPEN_MAX; fp++)
    if(fp->flags.is_read == 0 && fp->flags.is_write == 0)
      break; /* free slot found */

  if(fp >= _iob + OPEN_MAX)
    return NULL;

  if(*mode == 'w')
    fd = creat(name, PERMS);
  else if (*mode == 'a'){
    if ((fd = open(name, O_WRONLY, 0)) == -1)
      fd = creat(name, PERMS);
    lseek(fd, 0L, 2); /* go to end of file */
  } else
    fd = open(name, O_RDONLY, 0);

  if(fd == -1) /* couldn't access to the name */
    return NULL;

  /* set attribute */
  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL;
  fp->flags.is_read = (*mode == 'r') ? 1 : 0;
  fp->flags.is_write = (*mode == 'w') ? 1 : 0;
  fp->flags.is_unbuf = 0;
  fp->flags.is_eof = 0;
  fp->flags.is_err = 0;

  return fp;
}

int _fillbuf(FILE *fp){
  int bufsize;
  if(fp->flags.is_read == 0 || fp->flags.is_err == 1 || fp->flags.is_eof == 1)
    return EOF;

  bufsize = (fp->flags.is_unbuf == 1) ? 1 : BUFSIZ;
  if(fp->base == NULL) /* no buffer yet */
    if((fp->base = (char *) malloc(bufsize)) == NULL) /* error while allocating mem */
      return EOF;

  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if(--fp->cnt < 0){
    if(fp->cnt == -1)
      fp->flags.is_eof = 1;
    else
      fp->flags.is_err = 1;
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char) *fp->ptr++; /* in this case ++ apply to ptr bcs -> is higher prio then it dereferenced the ptr 
                                        associativity right to left but in this case postfixe operator is apply to ptr after 
                                        it be used to be dereferenced nice trick */
}

int fclose(FILE *fp){
  return 0;
}

int _flushbuf(int c, FILE *fp){
  unsigned nc;
  int bufsize;

  if(fp < _iob || fp >= _iob + OPEN_MAX)
    return EOF; /* pointer invalid */

  if(fp->flags.is_write == 0 || fp->flags.is_err == 1)
    return EOF; /* invalid action */

  bufsize = (fp->flags.is_unbuf == 1) ? 1 : BUFSIZ;
  if(fp->base == NULL){ /* no buffer yet */
    if((fp->base = (char *) malloc(bufsize)) == NULL){ /* error while allocating mem */
      fp->flags.is_err = 1;
      return EOF;
    }
  }
  return 0;
}

int fflush(){
  return 0;
}

int main(){
  return 0;
}
