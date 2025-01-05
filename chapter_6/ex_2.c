/************************************************************************************
 * The C Programming Language 6-2:
 *
 * -> Write a program that reads a C program and prints in alphabetical order each
 *    group of variable names that are identical in the first 6 characters, but different 
 *    somewhere thereafter. Don't count words within strings and comments. Make 6 a 
 *    parameter that can be set from the command line.
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MATCH_NUM 6

struct tnode{ /* tree node */
  char *word;
  int match;
  struct tnode *left;  /* left child */
  struct tnode *right; /* right child */
};

void addtree_ite(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
int match(char *, char *, struct tnode *, int *);

void print_info_stack();

int match_num;

int main(int argc, char *argv[]){
  struct tnode *root;
  char word[MAXWORD];
  //print_info_stack();
  
  match_num = (argc > 1 && atoi(argv[1]) != 0) ? atoi(argv[1]) : MATCH_NUM;
  printf("match number selected : %d\n", match_num);

  root = talloc(); /* in the iterative case you're force to allocate the first element mem */
  while(getword(word, MAXWORD) != EOF)
    if(isalpha(word[0]))
      addtree_ite(root, word);
  treeprint(root);
  return 0;
}

/* iterative addtree */
void addtree_ite(struct tnode *root, char *w){
  struct tnode *p = root; /* ptr moving along the tree */ 
  struct tnode *dad;      /* ptr to parent of p */
  int cond;
  int match_found = 0;    /* if a match is found during the parcours */

  if(root->word == NULL){ /* first element */
    root->word = strdup(w);
    root->match = 0;
    root->left = root->right = NULL;
    return;
  } 

  while(p != NULL && cond != 0){ /* whether it have found a match or reach a leaf */
    dad = p;
    if((cond = match(w, p->word, p, &match_found)) < 0)
      p = p->left;
    else if(cond > 0)
      p = p->right;
  }
   
  if(cond != 0) {                                     /* inserting a new element link to the old one */
    p = talloc();
    p->word = strdup(w);
    p->match = match_found;
    p->left = p->right = NULL;
  
    (cond > 0) ? (dad->right = p) : (dad->left = p);  /* link leaf to its dad */
  }
}

/* test if strings match, checks if there are not equal but match the x first char if yes store a match and match_found
 * then return 0 is they are equals or the diff lexico if they are not a perfect match */
int match(char *s1, char *s2, struct tnode *p, int *match_found){
  int i;
  for(i = 0; *s1 == *s2; s1++, s2++, i++)
    if(*s1 == '\0')
      break;

  if(i >= match_num && *s1 != '\0'){ /* case match but after char is diff */
    p->match = 1;
    *match_found = 1;
  }
  
  return (*s1 == '\0') ? 0 : *s1 - *s2;
}

void treeprint(struct tnode *p){
  if(p != NULL){
    treeprint(p->left);
    if(p->match)
      printf("%4d %s\n", p->match, p->word);
    treeprint(p->right);
  }
}

//small stack system with tnode ptr
//could be done with a void * and a casting system but it's simpler to type it
void push(struct tnode *p);
struct tnode *pop();
char isempty();

//TODO tree parcours...
/* is to use a stack to move along the tree */

struct tnode *talloc(){
  return (struct tnode *) malloc(sizeof(struct tnode));
}

/* in my test as expected a list of pointer of struct tnode is lighter 800bytes (8bytes for address bcs im x64 cpt * 100 element) 
 * than stack that contain element tnode directly which is 3200bytes which is bigger by a big margin */
// additional information i used *stack[] format because compiler allocate by itself we can use ** but need to 
// allocate manually
struct tnode *stack[MAXWORD];       /* list of pointer on struct tnode object */
struct tnode **sp = stack;          /* ptr of next free ptr on the list */

void print_info_stack(){
  printf("----STACK INFO----\n\nSize of stack : %lu\nis empty ? %d\nstack addr: %p\n\n-------------------\n", 
    sizeof(stack), isempty(), stack);
}

char isempty(){
  return sp == stack;
}

void push(struct tnode *p){
  if(sp < stack + MAXWORD)
    *sp++ = p;
  else 
    printf("Error : stack is full...");
}

struct tnode *pop(){
  if(sp > stack)
    return *--sp;
  else{
    printf("Error : try to pop on empty stack...");
    return NULL;
  }
}
