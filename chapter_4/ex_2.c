/************************************************************************************
 * The C Programming Language 4-2:
 * 
 * -> 
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <ctype.h>
#include <stdio.h>
#define MAXLINE 1000

int get_line(char s[], int lim);

int main()
{
  double sum, atof(char s[]);
  char line[MAXLINE];
  
  while (get_line(line, MAXLINE) > 0)
    printf("\t%f += %f\n", atof(line), sum += atof(line));
  
  return 0;
}

/* get_line: get line into s, return length */
//rename was require because this name was taken in stdio.h lib
int get_line(char s[], int lim){
  int c,i;
  i = 0;

  while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
    s[i++] = c;

  if(c == '\n')
    s[i++] = c;

  s[i] = '\0';
  return i;
}

//atof : convert a string into a double with scientific notation
//the trick here is to add a whole part about the exponant and divide or multiple power dependant of his sign
//important to note that multiple by 0.1 leads to more loss in accuracy than use division --> from C answer book
double atof(char s[]){
  double val, power;
  int i, sign;

  for(i=0; isspace(s[i]); i++)
    ;

  sign = (s[i] == '-') ? -1 : 1;
  if(s[i] == '+' || s[i] == '-')
    i++;

  for(val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');

  if(s[i] == '.')
    i++;

  for(power = 1.0; isdigit(s[i]); i++){
    val = 10.0 * val + (s[i] - '0');
    power *= 10;
  }
  
  if(s[i] == 'e' || s[i] == 'E'){
    i++; //skipping e
    int e, e_sign = 1;
    if(s[i] == '-'){
      e_sign = -1;
      i++;
    }
    
    printf("%d\n", e_sign);

    for(e = 0; isdigit(s[i]); i++){
      e = 10 * e + (s[i] - '0');
    }

    while(e > 0){
      (e_sign < 0) ? power *= 10 : (power /= 10);
      e--;
    }
  }

  return sign * val / power;
}
