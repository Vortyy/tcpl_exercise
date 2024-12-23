/************************************************************************************
 * The C Programming Language 5-10:
 * 
 * -> write a program 'expr', which evaluates a reverse Polish expression from the 
 *    command line, where each operator and operand is a separate arg.
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ***********************************************************************************/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
//inspired but rewrited to play more with argv and argc, obviously we could use ex_3
#define MAXOP 100
#define NUMBER '0'

int getop(char *s);
void push(double f);
double pop();

int main(int argc, char *argv[])
{
  int opt = 0;
  double op2;
  while(argc-- > 1){ /* argc == 1 if there is no arg at all that why > 1*/ 
    switch (opt = getop(*++argv)) {
      case NUMBER:
        push(atof(*argv));
        break;
      case '+':
        push(pop() + pop());
        break;
      case '*':
        push(pop() * pop());
        break;
      case '-':
        op2 = pop();
        push(pop() - op2);
        break;
    }
  }

  printf("result : %f \n", pop());
  return EXIT_SUCCESS;
}

#define MAXVAL 1000

/* rewrite pop and push with a ptr index */
double stack[MAXVAL];
double *sp = stack; 

//https://stackoverflow.com/questions/21152289/redefinition-of-a-pointer-in-global-scope
//that why we get an warning when 'sp = stack' in global context
void push(double f){
  if(sp < stack + MAXVAL)
    *sp++ = f;
  else
    fprintf(stderr, "error : stack full\n");
}

double pop(){
  if(sp > stack)
    return *--sp;
  else{
    fprintf(stderr, "error : pop() on empty stack\n");
    return 0.0;
  }
}

/* check first char if it's a digit or no */
int getop(char *s){
  if(!isdigit(*s) && *s != '.' && *s != '-')
    return *s; /* it's an operation */

  if(*s == '-'){ /* minus case it can be a number or operation */
    if(isdigit(*(s + 1)) || *(s + 1) == '.')
      ;
    else {
      return '-'; 
    }
  }

  return NUMBER;
}
