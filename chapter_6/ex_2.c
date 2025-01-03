/************************************************************************************
 * The C Programming Language 6-2:
 * 
 * -> Improve getword() presented in ch6.3 by taking into account comment, underscore
 *    preprocessor control and string constant
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode{ /* tree node */
  char *word;         
  int count;
  struct tnode *left;  /* left child */
  struct tnode *right; /* right child */
};

struct tnode *addtree(struct tnode *, char *);
void addtree_ite(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);

int main(int argc, char *argv[]){
  struct tnode *root;
  char word[MAXWORD];

  root = talloc(); /* in the iterative case you're force to allocate the first element mem */
  while(getword(word, MAXWORD) != EOF)
    if(isalpha(word[0]))
      addtree_ite(root, word);
  treeprint(root);
  return 0;
}

struct tnode *addtree(struct tnode *p, char *w){
  int cond;

  if(p == NULL){
    p = talloc();
    p->word = strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0)
    p->count++;
  else if (cond < 0)
    p->left = addtree(p->left, w);
  else 
    p->right = addtree(p->right, w);
  return p;
}

/* iterative addtree */
void addtree_ite(struct tnode *root, char *w){
  struct tnode *p = root; /* ptr moving along the tree */ 
  struct tnode *dad;      /* ptr to parent of p */
  int cond;

  if(root->word == NULL){ /* first element */
    root->word = strdup(w);
    root->count = 1;
    root->left = root->right = NULL;
    return;
  } 

  while(p != NULL && cond != 0){ /* whether it have found a match or reach a leaf */
    dad = p;
    if((cond = strcmp(w, p->word)) < 0)
      p = p->left;
    else if(cond > 0)
      p = p->right;
  }

  if(cond == 0){                                      /* count increase */
    p->count++; 
  } else {                                            /* inserting a new element link to the old one */
    p = talloc();
    p->word = strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  
    (cond > 0) ? (dad->right = p) : (dad->left = p);  /* link leaf to its dad */
  }
}

void treeprint(struct tnode *p){
  if(p != NULL){
    treeprint(p->left);
    printf("%4d %s\n", p->count, p->word);
    treeprint(p->right);
  }
}

/* is to use a stack to move along the tree */
void treeprint_it(struct tnode *root){
  if(root != NULL){
    //TODO 
  }
}

struct tnode *talloc(){
  return (struct tnode *) malloc(sizeof(struct tnode));
}
