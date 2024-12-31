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

int gettoken();
int getnexttoken();

int getch();
void ungetch(int);

int tokentype;            /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char out[1000];

int prevtoken;

int main(){
  int type, prevtoken =0;
  char temp[MAXTOKEN];

  while(gettoken() != EOF){
    strcpy(out,token);
    while((type = gettoken()) != '\n'){
      if(type == PARENS || type == BRACKETS)
        strcat(out, token);
      else if(type == '*'){
        if((type = getnexttoken()) == PARENS || type == BRACKETS) /* if [] or () --> need parens else no */
          sprintf(temp, "(*%s)", out);
        else 
          sprintf(temp, "*%s", out);
        strcpy(out, temp);
      } else if (type == NAME){
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      } else 
        printf("invalide input at %s\n", token);
    }
    printf("out : %s\n", out);
  }
  return 0;
}

int getnexttoken(){
  int type = gettoken();
  prevtoken = 1;
  return type;
}

int gettoken(){
  int c;
  char *p = token;

  if(prevtoken == 1){
    prevtoken = 0;
    return tokentype;
  }

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
