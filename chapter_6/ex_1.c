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
#include <string.h>

// give us the size of the array (becarefull this can only be set in prepro. #define, not #if)
// #define NKEYS (sizeof keytab / sizeof(struct key))
#define NKEYS (sizeof keytab / sizeof(keytab[0])) /* TRICKS : this one is independant of the struct which a lot better */
#define MAXWORD 100

/* here the declaration and the definition is done here, plus the size of the array
 * will be computed by the compiler */
struct key { 
  char *word;
  int count;
} keytab[] = { 
  "auto", 0,
  "break", 0,
  "case", 0,
  "char", 0,
  "const", 0,
  "for", 0,
  "int", 0,
  "return", 0,
  "unsigned", 0,
  "while", 0
}; /* not written all the keyword don't hit me */

int getword(char *, int);

/* insight here that every parameter is a local variable inside the function, then it copy the variable inside
 * that why with classic type there no probleme because they are lightweight but when it comes to big structures
 * that could be clearly another story */
int binsearch(char *, struct key *, int); /* using pointer inside function as param is a lot more memory efficient */ 

int main(){
  int n;
  char word[MAXWORD];
  while(getword(word, MAXWORD) != EOF) /* tip on Linux it's CTRL+D to send EOF signal */
    if(isalpha(word[0]))
      if((n = binsearch(word, keytab, NKEYS)) >= 0)
        keytab[n].count++;
  for(n = 0; n < NKEYS; n++)
    if(keytab[n].count > 0)
      printf("s : %4d %s\n", keytab[n].count, keytab[n].word);
  return 0;
}

/* binary search in a sorted list */
int binsearch(char *word, struct key *tab, int n){
  int cond;
  int low, high, mid;
  low = 0;
  high = n-1;
  while(low <= high){
    mid = (low + high) /2;
    if((cond = strcmp(word, tab[mid].word)) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

int getword(char *word, int lim){
  int c, d, comment(), getch(void);
  void ungetch(int);
  char *w = word;

  while (isspace(c = getch()))
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
  else if (isalpha(c) || c == '_' || c == '#'){ /* C keyword */
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
  int c, getch(void);
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
