/************************************************************************************
 * The C Programming Language 7-2:
 * 
 * -> Write a program that will print arbitrary input in a sensible way. As a
 *    minimum, it should print non-graphic characters in octal or hexadecimal according to local
 *    custom, and break long text lines.
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <ctype.h>
#include <stdio.h>

#define MAXLINESIZE 100
#define HEXSIZE 5

/* to be honest i really don't understand this question ??? */
/* i choose to represent char by 4 hex which correspond to single byte 4 * bits each bytes and size of char*/ 
int main(){
  int c, linesize = 0;

  while((c = getchar()) != EOF){
    if(iscntrl(c) || c == ' '){ /* non-graphical char */
      if((linesize += HEXSIZE) > MAXLINESIZE){
        putchar('\n');
        linesize = HEXSIZE;
      }
      printf("\\0x%-2x", c);
    } else { /* graphical char */
      putchar(c);
      linesize++;
    }

    if(linesize >= MAXLINESIZE)
      putchar('\n');
  }
}
