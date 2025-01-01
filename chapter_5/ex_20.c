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

enum { ERROR, QUALIFIER, TYPE, NAME, PARENS, BRACKETS };

void extdcl(void);   
void paramdcl(void);
void dcl(int);
void dirdcl(int);
int gettoken(void);

int getch();
void ungetch(int);

void dcl_error(char *);   /* set error flag to 1 and print a message */
void clear();             /* clear arrays and buffer */

int tokentype;            /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char qualifier[MAXTOKEN]; /* qualifier = const, register */
char out[1000];

char error;               /* error marker */

/* we choose to modify */
int main(){
  error = 0;
  while(gettoken() != EOF){
    out[0] = '\0';
     
    extdcl();

    if(error) /* if an error append during dcl execution */
      clear();
    else {
      printf("%s :%s ", name, out);
      if(qualifier[0] != '\0')
        printf("%s ", qualifier);
      printf("%s\n", datatype);
    }
  }
  return 0;
}

void extdcl(){
  //case QUALIFIE
  if(tokentype == QUALIFIER){
    strcpy(qualifier, token);
    gettoken();
  }

  if(tokentype != TYPE)
    dcl_error("no data type");
  else{
    int type;
    strcpy(datatype, token);
    dcl(0); /* not a param */
  }
}

void paramdcl(){
  int type;
  char temp[MAXTOKEN];
  temp[0] = '\0';

  gettoken(); 
  if(tokentype == QUALIFIER){
    strcat(temp, token);
    gettoken();
  }
    
  if(tokentype != TYPE){
    dcl_error("param got no type");
  } else {
    strcat(temp, " ");
    strcat(temp, token);
    dcl(1); /* param */
  }

  if(!error)
    strcat(out, temp);
}

void dcl(int isparam){
  int ns;
  for(ns = 0; gettoken() == '*';ns++)
    ;
  dirdcl(isparam);
  while(ns-- > 0)
    strcat(out, " pointer to");
}

void dirdcl(int isparam){
  int type;

  if(tokentype == '('){
    dcl(isparam);
    if(tokentype != ')')
      dcl_error("missing ) ...");
  } else if (tokentype == NAME){
    if(name[0] == '\0')
      strcpy(name, token);
  } else if (isparam && (tokentype == ')' || tokentype == ','))
    return;
  else
    if(!isparam)
      dcl_error("expected name or (dcl)");

  while((type=gettoken()) == PARENS || type == BRACKETS || type == '(')
    if(type == PARENS)
      strcat(out, " function returning");
    else if(type == '('){
      strcat(out, " function expecting");
      while(tokentype != ')' && tokentype != ERROR){
        paramdcl();
        strcat(out, " and");
      }
      strcat(out, " returning");
    }
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

    if(!strcmp(token, "const") || !strcmp(token, "register"))
      return tokentype = QUALIFIER;

    if(!strcmp(token, "int") || !strcmp(token, "char")) /* now we support only 2 types but can be improve by setting a list of type and apply a bsearch inside that list */
      return tokentype = TYPE;

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
  error = 0;
  while(gettoken() != '\n');
  bufp = 0; /* resest getch */
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
