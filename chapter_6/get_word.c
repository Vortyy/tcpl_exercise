#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

/* this function get word in C program, avoids comment section and handle _ */ 
int getword(char *word, int lim){
  int c, d, comment();
  char *w = word;

  while (isspace(c = getch()) && c!='\n')
    ;
  if(c != EOF)
    *w++ = c;
  if(c == '\'' || c == '"'){ /* string or char */
    for(; --lim > 0; w++){
      if((*w = getch()) == '\\')
        *w++ = getch();
      else if(*w == c){
        w++;
        break;
      } else if(*w == EOF){
        break;
      }
    } 
  }
  else if (isalnum(c) || c == '_' || c == '#'){ /* C keyword */
    for(; --lim > 0 ; w++) /* word */
      if(!isalnum(*w = getch()) && *w != '_'){
        ungetch(*w);
        break;
      }
  } else if (c == '/'){ /* a comment */
    if((d = getch()) == '*')
      c = comment();
    else
      ungetch(d);
  }
  
  *w = '\0';
  return c;
}

/* comment skip until the comment end */ 
int comment(){
  int c;
  while((c=getch()) != EOF)
    if(c == '*')
      if((c = getch()) == '/')
        break;
      else
        ungetch(c);

  return c;
}

/* getch and ungetch part, pointer version */

#define BUFSIZE 100

int buf[BUFSIZE];     /* buffer for ungetch */
int *bufp = buf;         /* next free position in buf */

int getch(){    /* get characters maybe a pushed-back one */
  return (bufp > buf) ? *--bufp : getchar();
}

void ungetch(int c){    /* push back char on input */
  if(bufp >= buf + BUFSIZE){
    fprintf(stderr, "ungetch : too many characters \n");
  } else {
    *bufp++ = c;
  }
}
