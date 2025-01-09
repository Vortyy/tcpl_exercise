/************************************************************************************
 * The C Programming Language 7-5 :
 * 
 * -> 
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>

#define MAXOP 100
#define NUMBER '0'

void clear(void);
int getop(double *);
void push(double f);
double pop(void);

/* reverse Polish calculator --> polish calculation ex : (4 + 9) - (4 - 1) => 4 9 + 4 1 - - tree representation */
/* in this exercise i choose to handle by using scanf in a efficient way but, major downside it's that need to change + and - by 
 * p and m because + and - are taken into account by scanf("%lf") but does nothing beside that using scanf make getop way easier
 * to read than this one from ex_3 chapter 4*/
int main(){
  int type;
  double op1, op2; /* this operation allow to guarantee order while doing non commutative operation bcs (pop() - pop()) --> not evaluated)*/
  double v;

  while((type = getop(&v)) != EOF){
    switch (type) {
     case NUMBER:
        push(v);
        break;
     case 'p':
        push(pop() + pop());
        break;
      case '*':
        push(pop() * pop());
        break;
      case 'm':
        op2 = pop();
        push(pop() - op2);
        break;
      case '/':
        op2 = pop();
        if(op2 != 0.0){
          push(pop() / op2);
        }else{
          fprintf(stderr, "error : zero divisor...3\n");
        }
        break;
     case '?': /* print the top element */
        op2 = pop();
        printf("\t%.8g\n", op2);
        push(op2);
        break;
      case 'c': /* clear stack */
        clear();
        break;
      case 'd': /* duplicate top element */
        op2 = pop();
        push(op2);
        push(op2);
        break;
      case 's': /* swap top 2 elements */
        op1 = pop();
        op2 = pop();
        push(op1);
        push(op2);
        break;
     case '\n':
        printf("\t%.8g\n", pop());
        break;
      default :
        fprintf(stderr, "error : unknown command... \n");
        break;
    }
  }
  return 0;
}

#define MAX_VAL 100

int sp = 0; /* next free position in stack */
double val[MAX_VAL]; /* stack values */

void clear(){
  sp = 0; //equivalent to clear stack
}

void push(double f){
  if(sp < MAX_VAL)
    val[sp++] = f;
  else
    fprintf(stderr, "error : stack full...1\n");
}

double pop(void){
  if(sp > 0)
    return val[--sp];
  else {
    fprintf(stderr, "error : stack empty...2\n");
    return 0.0;
  }
}

/* getop : return char op or store a number inside v */
int getop(double *v){ /* get next char or numeric operand */
  static char nc; /* next char */
  char c; /* current char */

  if(nc == '\n'){
    nc = ' '; /* reset nc */
    return '\n';
  }

  *v = 0.0; /* flush v */
  int r = scanf("%lf", v); /* try to get a number */
  /*printf("v : %lf", *v);*/
  if(r > 0)
    return NUMBER;
  
  if(r == 0){ /* not a number then get the char operation */
    scanf("%c", &c);
    scanf("%c", &nc);
    /*printf("%c and %c", c, nc);*/
    return c;
  }

  return EOF;
}
