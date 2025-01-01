/************************************************************************************
 * The C Programming Language 5-1:
 * 
 * -> Fix getint to treats + or - not followed by a digit not as a zero, and push
 *    back the sign
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int getint(int *pn){
  int c, d, sign;

  while(isspace(c =getch()))
    ;

  if(!isdigit(c) && c != EOF && c != '+' && c != '-'){
    ungetch(c);
    return 0;
  }

  sign = (c == '-') ? -1 : 1;
  if(c == '+' || c == '-'){
    d = c;
    if(!isdigit(c = getch())){
      if(c != EOF)
        ungetch(c);
      ungetch(d);
      return d;
    }
  }

  for(*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;
  if(c != EOF)
    ungetch(c);
  return c;
}

#define BUFSIZE 100

int buf[BUFSIZE];     /* buffer for ungetch */
int bufp = 0;         /* next free position in buf */

int getch(){    /* get characters maybe a pushed-back one */
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){    /* push back char on input */
  if(bufp >= BUFSIZE){
    fprintf(stderr, "ungetch : too many characters \n");
  } else {
    buf[bufp++] = c;
  }
}
