/************************************************************************************
 * The C Programming Language 5-2:
 * 
 * -> write getfloat (cf ch.4 ex_2) which transform a string into a float and return
 *    int of the last char
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int getfloat(float *pn){
  int c, d, sign;
  float power;

  while(isspace(c =getch()))
    ;

  if(!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.'){
    ungetch(c);
    return 0;
  }

  sign = (c == '-') ? -1 : 1;
  if(c == '+' || c == '-')
    c = getch();

  for(*pn = 0.0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  if(c == '.')
    c = getch();
  for(power = 1.0; isdigit(c); c=getch()){
    *pn = 10 * *pn + (c - '0');
    power *= 10.0;
  }

  *pn *= sign / power;

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
