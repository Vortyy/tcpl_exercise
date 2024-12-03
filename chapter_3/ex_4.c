/************************************************************************************
 * The C Programming Language 3-4, 3-5 and 3-6 :
 * 
 * -> write escape(s, t) that take a string t and convert all the \n and \t into a 
 *    real sequence of character and write the inverse of this function
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define abs(x) ((x < 0) ? -(x) : (x))

void reverse(char t[]){
  int c, i, j;
  for(i = 0, j = strlen(t) - 1; i < j; i++, j--){
    c = t[i];
    t[i] = t[j];
    t[j] = c;
  }
}

//Here in the book's version there is a probleme when handling lowest max because the lowest
//number a int can take is -21... (bin = 1 0*31 bits) or when turn to a positif number this value
//become 0 then you won't be able to print it because you lose it
void itoa(int n, char s[]){
  int sign, i;
  sign = n;
  i = 0;
  do {
    s[i++] = abs(n % 10) + '0';
  } while ((n /= 10) != 0);

  if(sign < 0)
    s[i++] = '-';

  s[i] = '\0';
  reverse(s);
}

int main(int argc, char *argv[])
{
  char seq[100];
  
  itoa(INT_MIN, seq);
  printf("%d : %s \n", INT_MIN, seq);

  return EXIT_SUCCESS;
}
