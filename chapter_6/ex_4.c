/************************************************************************************
 * The C Programming Language 6-4:
 * WARNING THIS PROGRAM NEED get_word.c TO COMPILE
 *
 * -> Write a program that prints the distinct words in its input sorted into decreasing
 *    order of frequency of occurrence. Precede each word by its count.
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
  int count;
  struct tnode *left;  /* left child */
  struct tnode *right; /* right child */
};

void addtree_ite(struct tnode *, char *);
void sorted_print(struct tnode *);
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
    

  sorted_print(root);
  return 0;
}

/* iterative addtree */
void addtree_ite(struct tnode *root, char *w){
  if(root->word == NULL){ /* first element */
    root->word = strdup(w);
    root->count = 1;
    root->left = root->right = NULL;
    return;
  }

  struct tnode *p = root; /* ptr moving along the tree */ 
  struct tnode *dad;      /* ptr to parent of p */

  int cond = -1;

  while(p != NULL && cond != 0){ /* whether it have found a match or reach a leaf */
    dad = p;
    if((cond = strcmp(w, p->word)) < 0)
      p = p->left;
    else if(cond > 0)
      p = p->right;
  }
  
  if(cond == 0){
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

struct tnode *list[MAXWORD]; /* list of ptr on tnode struct */
int lp = 0;                  /* idx of next free element on the list */

void storelist(struct tnode *p){
  if(p != NULL){
    storelist(p->left);
    if(lp < MAXWORD)
      list[lp++] = p;
    storelist(p->right);
  }
}

/* storing, then shellsorting (bcs it's a small list) list on count finally print the list */
void sorted_print(struct tnode *p){
  storelist(p);

  /* shellsort ptr tnode based on count */
  int gap, i, j;
  struct tnode *temp;
  for(gap = lp/2; gap > 0; gap/=2)
    for(i = gap; i < lp; i++)
      for(j = i - gap; j >= 0; j -= gap){
        if((list[j]->count) >= (list[j+gap]->count)) /* need to add parentheses because order of evaluation cf.ch2 */
          break;

        temp = list[j];
        list[j] = list[j+gap];
        list[j+gap] = temp;
      }

  for(i = 0; i < lp; i++)
    printf("%4d : %s\n", list[i]->count, list[i]->word); 
}

struct tnode *talloc(){
  return (struct tnode *) malloc(sizeof(struct tnode));
}
