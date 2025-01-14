/************************************************************************************
 * The C Programming Language 8-6, 8-7 and 8-8 :
 * 
 * 8-6 -> The standard library function calloc(n,size) returns a pointer to n objects of
 *        size size, with the storage initialized to zero. Write calloc, by calling 
 *        malloc or by modifying it.
 *
 * 8-7 -> malloc accepts a size request without checking its plausibility; free believes
 *        that the block it is asked to free contains a valid size field. Improve these 
 *        routines so they make more pains with error checking.
 *
 * 8-8 -> Write a routine bfree(p,n) that will free any arbitrary block p of n characters
 *        into the free list maintained by malloc and free. By using bfree, a user can add
 *        a static or external array to the free list at any time.
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MALLOCMAX 10000
#define max(a, b) ((a > b) ? (a) : (b)) 

typedef long Align; /* define the instance of the most restrictive alignment on the local
                     * local machine (in the exercise they choose long arbitrarily)*/

/* the trick is to use union to force the alignment an union is a qualifier that allow 
 * to the struct to take the maximum value of every type inside it, by taking a most 
 * restrictive alignment inside we force each header to be align on Align size */
union header {
  struct {
    union header *ptr; /* next block if on free list */
    unsigned size;     /* size of this block */
  } s;
  Align x;             /* force the alignment of blocks (never used) */ 
};

typedef union header Header;

/* one thing important to note hear is that the freep list is ordered by
 * their storage addresse that allow to search and place efficiently 
 * freeblock inside */
static Header base;           /* empty list to get started */
static Header *freep = NULL;  /* start of free list */
static unsigned maxalloc = 0;

void *malloc(unsigned);
void *calloc(unsigned, unsigned);
void free(void *);
unsigned bfree(char *, unsigned);
Header *moreroce(unsigned);

/* note to free */

void *malloc(unsigned nbytes){
  Header *p, *prevp;
  Header *moreroce(unsigned);
  unsigned nunits;

  if(nbytes > MALLOCMAX){
    fprintf(stderr, "trying to allocate too much memory (MAX IS %d)\n", MALLOCMAX);
    return NULL;
  }

  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
  if((prevp = freep) == NULL) {
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0; 
  }

  for(p = prevp->s.ptr; ; prevp = p, p=p->s.ptr){
    if(p->s.size >= nunits){
      if(p->s.size == nunits)
        prevp->s.ptr = p->s.ptr;
      else {
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;
      return (void *) (p + 1);
    }
    if(p == prevp)
      if((p = moreroce(nunits)) == NULL)
        return NULL;
  }
}

#define NALLOC 1024 

/* set program break defines the end of the process's data segment (i.e., the pbrk is the 1st location after the end
 * of uninitialized data segment --> that why sbrk given always address in that are ordered because it's just increase
 * a data segment) cf. man sbrk*/
Header *moreroce(unsigned nu){
  char *cp;
  Header *up;

  if(nu < NALLOC)
    nu = NALLOC;
  cp = sbrk(nu * sizeof(Header)); /* basicalle sbrk = set program break */
  if(cp == (char *) -1)
    return NULL;
  up = (Header *) cp;
  up->s.size = nu;
  maxalloc = max(up->s.size, maxalloc);
  free((void *) (up + 1)); /* + 1 because free(void *) realign -1 */
  return freep;
}

void free(void *ap){
  Header *bp, *p;
  bp = (Header *) ap - 1; /* set ptr to block header */
  if(bp->s.size == 0 || bp->s.size > maxalloc){
    fprintf(stderr, "free : can't free this amounts of units %u\n", bp->s.size);
    return;
  }

  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break;

  if(bp + bp->s.size == p->s.ptr){ /* join upper boundaries */
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else 
    bp->s.ptr = p->s.ptr;

  if(p + p->s.size == bp){ /* join lower boundaries */
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else 
    p->s.ptr = bp;

  freep = p;
}

/* calloc : set all the reserved memory to 0 */
void *calloc(unsigned n, unsigned size){
  char *p, *mp;
  unsigned tbytes = n * size;
  p = (char *) malloc(tbytes);
  if(p != NULL){
    for(mp = p; mp < p + tbytes; mp++)
      *mp = 0;
  }
  return p;
}

/* forced char ptr to ensure they are only 1bytes */
unsigned bfree(char *p, unsigned n){
  Header *hp;
  if(n < sizeof(Header))
    return 0; /* no freeing too small */
  hp = (Header *) p;
  hp->s.size = n/sizeof(Header);
  free((void *)(hp + 1));
  return hp->s.size;
}

/* printFreep : utility function to prints the linked list of free mem */
void printFreep(){
  printf("\nsee the free block list :\n");
  Header *vp;
  printf("(freep) %p : %u ", freep, freep->s.size);
  for(vp = freep->s.ptr; vp != freep; vp = vp->s.ptr)
    printf(" -> %p : %u ", vp, vp->s.size);
  printf(" -> (freep)\n");
}

int main(){
  /* printf took my malloc and allocated 1024 for the stdout buffer -> 
   * thing funny his that not using BUFSIZE but 1024 (like MYSTDIO.h)  */
  printf("allocated buf of stdout\n\n");      /* reserved unit when (sizeof(Header) == 16) : 65 */ 

  int *man, *man1, *man2, *p;
  man = (int *) calloc(10,sizeof(int));       /* reserved unit when (sizeof(Header) == 16) : 4 */
  man1 = (int *) malloc(50 * sizeof(int));    /* reserved unit when (sizeof(Header) == 16) : 14 */
  man2 = (int *) malloc(sizeof(int));         /* reserved unit when (sizeof(Header) == 16) : 2 */

  printf("Size alignment %lu\n\n", sizeof(Header));
  /* now or oun first block should be shrinked by 85 and his size to be 939 = 1024 - 85*/
  printf("%-20s -> %p\n%-20s -> %p\n%-20s -> %p\n\n", "man allocated", man, "man1 allocated", man1, "man2 allocated", man2);

  printf("checking calloc on man :\n");
  p = man;
  while(p < man + 10){
    printf("%d at %p\n", *p, p); /* allow to vizualize data and related mem address (can't do *p++ UB) */
    p++;
  }

  printFreep();  

  bfree((char *)man, 40); /* if you use static or external var that are on stack mem, you will be rejectet by SIGSEGV */
  free(man1);

  printFreep();
  return 0;
}
