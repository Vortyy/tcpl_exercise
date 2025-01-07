/************************************************************************************
 * The C Programming Language 7-3:
 * 
 * -> Write a program that will print arbitrary input in a sensible way. As a
 *    minimum, it should print non-graphic characters in octal or hexadecimal according to local
 *    custom, and break long text lines.
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>
#include <stdarg.h>

#define MAXLINESIZE 100
#define HEXSIZE 5

void minprintf(char *fmt, ...);

int main(){
  char *test = "test";
  char t = 't';
  int i = 15;
  printf("%p -- %p\n", &i, (void *) &i); /* with va_arg &i as arg this give me a really weird address and idk why, my pseudo answer that macro is &(&i) like that and make it fuck'd up with addresses */
  minprintf("ceci est un test : %c %x %X %o %p %p", t, i, i, i);
  printf("\n");
}

void minprintf(char *fmt, ...){
  va_list ap; /* points to each unnamed arg in turn */
  char *p, *sval;
  int ival;
  double dval;
  void *pval;

  va_start(ap, fmt); /* make ap point to 1st unnamed arg */
  for(p = fmt; *p; p++){
    if(*p != '%'){
      putchar(*p);
      continue;
    }

    switch(*++p){
      case 'c':
        ival = va_arg(ap, int);
        putchar(ival);
        break;
      case 'd':
        ival = va_arg(ap, int); /* va_arg make ap return the arg and step up to next one */
        printf("%d", ival);
        break;
      case 'f':
        dval = va_arg(ap, double);
        printf("%f", dval);
        break;
      case 'p':
        pval = va_arg(ap, void *);
        printf("%p", pval);
        break;
      case 's':
        for (sval = va_arg(ap, char *); *sval; sval++)
          putchar(*sval);
        break;
      case 'o':
        ival = va_arg(ap, int);
        printf("%o", ival);
        break;
      case 'x':
      case 'X':
        ival = va_arg(ap, int);
        printf("%x", ival);
        break;
      default:
        putchar(*p);
        break;
    }
  }
  va_end(ap); /* clean up when done */ 
}
