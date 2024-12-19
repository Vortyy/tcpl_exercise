/************************************************************************************
 * The C Programming Language 4-3, 4-4, 4-5, 4-6, 4-7, 4-8, 4-9, 4-10 :
 * 
 * -> 
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define MATHOP '1'
#define VAR_NUMBER 26

void clear(void);
int getop(char s[]);
void push(double f);
double pop(void);
void mathfun(char s[]);

double vars[VAR_NUMBER]; /* we will use A - Z as variable ranges */ 

/* reverse Polish calculator --> polish calculation ex : (4 + 9) - (4 - 1) => 4 9 + 4 1 - - tree representation */ 
int main(){
  int type;
  double op1, op2; /* this operation allow to guarantee order while doing non commutative operation bcs (pop() - pop()) --> not evaluated)*/
  char s[MAXOP];

  /* initialize our vars */ 
  for(int i = 0; i < VAR_NUMBER; i++){
    vars[i] = 0.0;
  } 

  while((type = getop(s)) != EOF){
    switch (type) {
      case NUMBER:
        push(atof(s));
        break;
      case MATHOP:
        mathfun(s);
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
      case '/':
        op2 = pop();
        if(op2 != 0.0){
          push(pop() / op2);
        }else{
          fprintf(stderr, "error : zero divisor...3\n");
        }
        break;
      case '%':
        op2 = pop();
        if(op2 != 0.0)
          push(fmod(pop(), op2));
        else 
          fprintf(stderr, "error : zero divisor modulus...\n");
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
      case '=': /* set a var */ 
        break;
      case '\n':
        printf("\t%.8g\n", pop());
        break;
      default :
        fprintf(stderr, "error : unknown command... %s\n", s);
        break;
    }
  }
  return 0;
}

void mathfun(char s[]){ /* reads and applies a maths function from the math.h lib */
  double op2;
  if(strcmp(s, "sin") == 0)
    push(sin(pop()));
  else if (strcmp(s, "cos") == 0)
    push(cos(pop()));
  else if (strcmp(s, "exp") == 0)
    push(exp(pop()));
  else if (strcmp(s, "pow") == 0){
    op2 = pop();
    push(pow(pop(), op2));
  } else
    fprintf(stderr, "command not supported");
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

int getch(void);
void ungetch(int);

//4-10 dealing with getline only change getop to play with an array and a global index without calling getch and ungetch because there is no overflow while reading
//the getch() always goes +1 further than the number that why they've put ungetch to keep the on that goes out of the buffer
int getop(char s[]){ /* get next char or numeric operand */
  int i, c;

  while((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';

  if(isupper(c)){
    return c;
  }

  if(islower(c)){ /* a math function */
    while(islower(s[++i] = c = getch()))
      ;
    s[i] = '\0';
    if(c != EOF)
      ungetch(c);
    if(strlen(s) > 1)
      return MATHOP;
    else
      return c;
  }

  if(!isdigit(c) && c != '.' && c != '-')
    return c; /* not a number */

  i = 0;
  if(c == '-') /* 2 case --> its a negative number or a minus operation */ 
    if(isdigit(s[++i] = c = getch()) || c == '.')
      ;
    else{
      if(c != EOF)
        ungetch(c);
      return '-';
    };
  
  if(isdigit(c))
    while(isdigit(s[++i] = c = getch())); /* collecting integer part */
  
  if(c == '.')
    while(isdigit(s[++i] = c = getch())); /* collecting fraction part */
  
  /*printf("last getch : -%c- \n", s[i]); // as we can see last char is always +1 further than we want */
  
  s[i] = '\0';
  if(c != EOF)
    ungetch(c);

  return NUMBER;
}

/* ungets no need to handle buf and bufp because ungetch already handle it */
void ungets(char s[]){
  int len = strlen(s);
  
  while(len > 0)
    ungetch(s[--len]);
}

#define BUFSIZE 100

/* 4-9 just pass buf to int to avoid conversion make -1 become 255 bcs when it does conversion it replace missing left missing byte by 0 here int -> char -> int (ex: 0xFFFF -> 0xFF -> 0x00FF)*/
char buf[BUFSIZE];    /* buffer for ungetch */
int bufp = 0;         /* next free position in buf */

int getch(){    /* get characters maybe a pushed-back one */
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){    /* push back char on input */
  if(bufp >= BUFSIZE){
    fprintf(stderr, "ungetch : too many characters \n");
  } else {
    buf[bufp++] = c;
  }
}
