/************************************************************************************
 * The C Programming Language 6-6:
 * WARNING THIS PROGRAM NEED get_word.c TO COMPILE
 *
 * -> Implement a simple version of the #define processor (i.e., no arguments)
 *    suitable for use with C programs, based on the routines of this section. 
 *    You may also find getch and ungetch helpful. 
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101
#define MAXWORD 100

struct nlist {        /* table entry */
  struct nlist *next; /* next entry in chain */
  char *name;         /* define name */
  char *defn;         /* replacement text */
};

static struct nlist *hashtab[HASHSIZE]; /* ptr table */

/* hash : form hash from a string s */
unsigned hash(char *s){
  unsigned hashval;

  for(hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;

  return hashval % HASHSIZE;
}

int getword(char *, int); /* ref to get_word.c */
int getch();              /* ref to get_word.c */
void ungetch(int);        /* ref to get_word.c */

void setdef(void);
void setundef(void);

void error(char *s);

struct nlist *lookup(char *);
struct nlist *install(char *, char *);
int undef(char *);

/* this answer i choose to space between each word and jump line as C file parse do to clearly see if define work */
/* for simplicity cause i choose to ignore case where there is space between '#' and 'define' || 'undef' */ 
int main(int argc, char **argv){
  char word[MAXWORD];
  struct nlist *p;
  while(getword(word, MAXWORD) != EOF)
    if(word[0] == '\n') /* line jump */
      printf("\n");
    else if(word[0] == '#') /* begin of definition */
      if(strcmp("#define", word) == 0)
        setdef();
      else if (strcmp("#undef", word) == 0)
        setundef();
      else
        error("unknown processor command");
    else if(!isalpha(word[0]))
      printf("%s ", word);
    else if((p = lookup(word)) == NULL)
      printf("%s ", word);
    else 
      printf("%s ", p->defn);

  return 0;
}

/* error : print error message then clear the line */
void error(char *s){
  int n;
  char trash[MAXWORD];
  printf("error : %s\n", s);
  while((n = getword(trash, MAXWORD)) != '\n');
}

/* setdef : take next word as name and the rest of line as def */
void setdef(){
  int c, i;
  char name[MAXWORD], def[MAXWORD];
  if(getword(name, MAXWORD) != EOF) /* name */ 
    if(!isalpha(name[0])){
      error("define name is not alphabetical...");
      return;
    }

  /* get def */
  while((c = getch()) == ' ' || c == '\t');
  
  ungetch(c);
  for(i = 0; i < MAXWORD - 1; i++)
    if((def[i] = getch()) == EOF || def[i] == '\n')
      break;
  def[i] = '\0';
  if(i <= 0){
    error("no definition given for #define");
  } else 
    install(name, def);
}

/* setundef : take the next word verify it and then try to undef */
void setundef(){
  char name[MAXWORD];
  if(isalpha(getword(name, MAXWORD)))
    undef(name);
  else
    error("name of #undef isn't alphabetical");
}

/* lookup : look for s in hashtab */
struct nlist *lookup(char *s){
  struct nlist *np;

  for(np = hashtab[hash(s)]; np != NULL; np = np->next)
    if(strcmp(s, np->name) == 0)
      return np;

  return NULL;
}

/* install : put(name, defn) in hashtab */
struct nlist *install(char *name, char *defn){
  struct nlist *np;
  unsigned hashval;

  if((np = lookup(name)) == NULL){
    np = (struct nlist *) malloc(sizeof(*np));
    if(np == NULL || (np->name=strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval]; /* first order insertion into the nlist */
    hashtab[hashval] = np;
  } else 
    free((void *) np->defn);
  
  if((np->defn = strdup(defn)) == NULL)
    return NULL;

  return np;
}

/* undef : erase a name and it's definition from hashtab return -1 if none has been erase, 0 if erase an element */
int undef(char *name){
  unsigned hashval = hash(name);
  struct nlist *np = hashtab[hashval];

  // 1st element need to be undef 
  if(np != NULL && strcmp(name, np->name) == 0){
    hashtab[hashval] = np->next;
    free(np);
    return 0;
  }
  // in list || last
  int cond;
  while(np->next != NULL && (cond = strcmp(name, np->next->name)) != 0) /* looping until the list is empty or he found the parent of element that need to be undef */
    np = np->next;

  if(cond == 0){ /* found */
    struct nlist *del = np->next; /* just for reading purpose np = parent of deleted element */
    np->next = del->next;
    free(del);
    return 0;
  }

  return -1;
}
