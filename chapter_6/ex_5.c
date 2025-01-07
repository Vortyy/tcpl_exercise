/************************************************************************************
 * The C Programming Language 6-5:
 * WARNING THIS PROGRAM NEED get_word.c TO COMPILE
 *
 * -> Write a function undef that will remove a name and definition from the table
 *    maintained by lookup and install.
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist { /* table entry */
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

struct nlist *lookup(char *);
struct nlist *install(char *, char *);
int undef(char *);

struct testdef{ /* this struct is for testing purpose only */
  char *name;
  char *def;
} t[] = {
  "def", "simple def",
  "testing", "test of def",
  "rand", "923",
  "ascii", "ASCII test"
}; 

int main(int argc, char **argv){
  for(int i = 0; i < sizeof(t)/sizeof(t[0]); i++)
    install(t[i].name, t[i].def);

  //search for "def", and "definition"
  struct nlist *np = lookup("def");
  printf("%s -> %s\n", np->name, np->defn);

  //undef 'def' return 0
  printf("undef of 'def' = %d\n", undef("def"));

  //lookup erased value --> return NULL || nil 
  printf("lookup of 'def' : %p\n", lookup("def"));
 
  np = lookup("ascii");
  printf("%s -> %s\n", np->name, np->defn);

  return 0;
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
