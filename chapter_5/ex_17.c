/************************************************************************************
 * The C Programming Language 5-13:
 * 
 * -> rewrite the tail linux command 
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken(void);
int getch();
void ungetch(int);

int tokentype;            /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char out[1000];

int main(){
  while(gettoken() != EOF){
    strcpy(datatype, token);
    out[0] = '\0';
    dcl();
    if(tokentype != '\n')
      printf("syntax error\n");
    printf("%s: %s %s \n", name, out, datatype);
  }
  return 0;
}

void dcl(){
  int ns;
  for(ns = 0; gettoken() == '*';ns++);
  dirdcl();
  while(ns-- > 0)
    strcat(out, " pointer to");
}

void dirdcl(){
  int type;

  if(tokentype == '('){
    dcl();
    if(tokentype != ')')
      printf("error : missing ) ...\n");
  } else if (tokentype == NAME) 
    strcpy(name, token);
  else
    printf("error: expected name or (dcl)\n");

  while((type=gettoken()) == PARENS || type == BRACKETS)
    if(type == PARENS)
      strcat(out, " function returning");
    else{
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    } 
}

int gettoken(){
  int c;
  char *p = token;

  while((c = getch()) == ' ' || c == '\t');

  if(c == '('){
    if((c = getch()) == ')'){
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c);
      return tokentype = '(';
    }
  } else if (c == '['){
    for(*p++ = c; (*p++ = getch()) != ']';);
    *p = '\0';
    return tokentype = BRACKETS;
  } else if(isalpha(c)) {
    for(*p++ = c; isalnum(c = getch());)
      *p++ = c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  } else 
    return tokentype = c;
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
