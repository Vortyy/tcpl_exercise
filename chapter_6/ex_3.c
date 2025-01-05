/************************************************************************************
 * The C Programming Language 6-3:
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

struct ll {   /* linked list because we don't know in how much line will be the word */
  int line_num;
  struct ll *next;
};

struct tnode{ /* tree node */
  char *word;
  struct ll *lines_num;   /* linked list of lines numbers */
  struct tnode *left;     /* left child */
  struct tnode *right;    /* right child */
};

void addtree_ite(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
void addlinenum(struct ll *); /* check if it's a new line in line linked list of a specific word */
int noiseword(char *);        /* check if the word is inside noise word list */

struct tnode *talloc(void);
struct ll *lalloc(void);

int line_num = 1;

int main(int argc, char *argv[]){
  struct tnode *root;
  char word[MAXWORD];

  root = talloc(); /* in the iterative case you're force to allocate the first element mem */
  while((getword(word, MAXWORD)) != EOF)
    if(isalpha(word[0]) && noiseword(word) == -1)
      addtree_ite(root, word);
    else if(word[0] == '\n')
      line_num++;
  
  treeprint(root);
  return 0;
}

/* iterative addtree */
void addtree_ite(struct tnode *root, char *w){
  struct tnode *p = root; /* ptr moving along the tree */ 
  struct tnode *dad;      /* ptr to parent of p */
  int cond = -1;

  if(root->word == NULL){ /* first element */
    root->lines_num = lalloc();
    root->lines_num->line_num = line_num;
    root->lines_num->next = NULL;
    root->word = strdup(w);
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
  
  if(cond == 0){ /* found a same */
    addlinenum(p->lines_num); 
  } else { /* inserting a new element link to the old one */
    p = talloc();                       /* mem init becarfull it's important to allocate tree node first because it's inside tree node that live lines_num */
    p->lines_num = lalloc();
    
    p->lines_num->line_num = line_num;  /* linked list initializer */
    p->lines_num->next = NULL;

    p->word = strdup(w);                /* tree node initializer */
    p->left = p->right = NULL;
  
    (cond > 0) ? (dad->right = p) : (dad->left = p);  /* link leaf to its dad */
  }
}

void addlinenum(struct ll *ln){
  struct ll *temp = ln;
  while(temp->next != NULL && temp->line_num != line_num) /* go until the end of linked list or stop if found same line_num */
    temp = temp->next;
  if(temp->line_num != line_num){ /* new line number detected */
    temp->next = lalloc();
    temp->next->line_num = line_num;
    temp->next->next = NULL;
  }
}

void treeprint(struct tnode *p){
  if(p != NULL){
    struct ll *ln = p->lines_num;
    treeprint(p->left);
    printf("%s : ", p->word);
    for(; ln != NULL; ln = ln->next)
      printf("%4d ", ln->line_num);
    printf("\n");
    treeprint(p->right);
  }
}

/* bsearch inside a static list of noise word, return -1 if it's not a noisy word */
int noiseword(char *w){
  static char *nw[] = {"a", "an", "and", "are", "in", "is", "of", "or", "the", "than", "this", "to", "with"}; /* this list need to be ordered */
  int cond;
  int low, high, mid;
  low = 0;
  high = sizeof(nw)/sizeof(nw[0]) - 1;
  while(low <= high){
    mid = (low + high) /2;
    if((cond = strcmp(w, nw[mid])) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

/* ---- mem allocator ---- */

struct tnode *talloc(){
  return (struct tnode *) malloc(sizeof(struct tnode));
}

struct ll *lalloc(){
  return (struct ll *) malloc(sizeof(struct ll));
}
