/************************************************************************************
 * The C Programming Language 8-2, 8-3 and 8-4 :
 * 
 * 8-2 -> Rewrite fopen and _fillbuf with fields instead of explicit bit operations. 
 *        Compare code size and execution speed 
 *
 * 8-3 -> Design and write _flushbuf, fflush and fclose
 *
 * 8-4 -> int fseek(FILE *fp, long offset, int origin) is identical to lseek except 
 *        that fp is a file pointer instead of a file descriptor and return value is 
 *        an int status, not a position. Write fseek. Make sure that your fseek 
 *        coordinates properly with the buffering done for the other functions of 
 *        the library.
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
  {0, (char *) 0, (char *) 0, _write, 1},
  {0, (char *) 0, (char *) 0, _wu, 2},
};

/* while stdio.h is not included the warning is not a big deal just telling me that will be a conflic */
/* fopen : set a member of _iob array and create a link with its file descriptor */
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

/* _fillbuf : fill the buffer of a file pointer to be read */
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

/* _flushbuf : flush the buffer of file pointer and write at 1st the c char to it, return c */
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
  } else { /* there is a buffer write it's content */
    nc = fp->ptr - fp->base;
    if(write(fp->fd, fp->base, nc) != nc){
      fp->flags.is_err = 1;
      return EOF;
    }
  }

  fp->ptr = fp->base;     /* reset ptr of the next free space char */
  *fp->ptr++ = (char) c;  /* store c inside buffer */
  fp->cnt = bufsize - 1;  /* reset char left */

  return c;
}

/* fflush : flush/reset the file pointer */
int fflush(FILE *fp){
  int rc;
  if(fp->flags.is_write == 1)
    rc = _flushbuf(0, fp);
  fp->ptr = fp->base;
  fp->cnt = (fp->flags.is_unbuf == 1) ? 1 : BUFSIZ;
  return rc;
}

/* fclose : flush file buffer and release ressources */
int fclose(FILE *fp){
  int rc; /* return code */
  if((rc = fflush(fp)) != EOF){
    free(fp->base);
    fp->ptr = NULL;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flags = (struct flag_field) _setflags(0,0,0); /* reset flags */
    fp->fd = 0; /* reset fd even if it will be remap at each fopen */
  }
  return rc;
}

int fseek(FILE *fp, long offset, int origin){
  long rc = 0;
  unsigned nc;
  if(fp->flags.is_read == 1){
    if(origin == 1)
      offset -= fp->cnt;
    rc = lseek(fp->fd, offset, origin);
    fp->cnt = 0;
  } else {
    if((nc = fp->ptr - fp->base) > 0)
      if(write(fp->fd, fp->base, nc) != nc)
        rc = -1;
    if(rc != -1)
      rc = lseek(fp->fd, offset, origin);
    
  }
  return (rc == -1) ? -1 : 0;
}

/* simple getchar() -> putchar() until EOF with MYSTDIO.h */
/* how this works is simple first getchar() call _fillbuf --> that reads stdin file (fd = 0) then all getchar() call
* will correspond to an element of the buffered array char, then when all the char of the arr will be consumed 
* getchar() recall _fillbuf() to queries the new input inside stdin all the input are reported thx to the read() fct */ 
int main(){
  int c;

  FILE *fp = fopen("ex_1.c", "r");
  fseek(fp, 300, 0); 

  while((c = getc(fp)) != EOF){
    putchar(c);
  }

  fclose(fp);
  fclose(stdout); //this line force to _flushbuf stdout to print even if the buffer size limit is not reach 
  return 0;
}
