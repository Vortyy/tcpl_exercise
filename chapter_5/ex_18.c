/************************************************************************************
 * The C Programming Language 5-18:
 * 
 * -> Make dcl recover from input errors.
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

enum { ERROR, NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken(void);

int getch();
void ungetch(int);

void dcl_error(char *);   /* set error flag to 1 and print a message */
void clear();             /* clear arrays and buffer */

int tokentype;            /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char out[1000];

char error;               /* error marker */

/* in this answer i choose to skip the line when it got an unexpected input (cf. error marker)*/
int main(){
  error = 0;
  while(gettoken() != EOF){
    strcpy(datatype, token);
    out[0] = '\0';
    dcl();
    if(tokentype != '\n')
      dcl_error("syntax error");

    if(error) /* if an error append during dcl execution */
      clear();
    else
      printf("%s: %s %s \n", name, out, datatype);
  }
  return 0;
}

void dcl(){
  int ns;
  for(ns = 0; gettoken() == '*';ns++)
    ;
  dirdcl();
  while(ns-- > 0)
    strcat(out, " pointer to");
}

void dirdcl(){
  int type;

  if(tokentype == '('){
    dcl();
    if(tokentype != ')')
      dcl_error("missing ) ...");
  } else if (tokentype == NAME) 
    strcpy(name, token);
  else
    dcl_error("expected name or (dcl)");

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

  if(error)
    return tokentype = ERROR;

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

void dcl_error(char *msg){
  printf("err_msg : %s\n", msg);
  error = 1;
}

#define BUFSIZE 100

int buf[BUFSIZE];     /* buffer for ungetch */
int bufp = 0;         /* next free position in buf */

void clear(){ /* reset buffer reader */
  printf("There was at least 1 error in your previous input please retype it :\n");
  bufp = 0; /* resest getch */
  error = 0;
}

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
