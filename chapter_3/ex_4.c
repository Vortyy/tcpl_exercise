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

//Here you can find the math insight about this function :
//https://math.stackexchange.com/questions/1359770/why-does-the-division-algorithm-work-for-converting-between-number-bases
void itob(int n, char s[], int b){
  int sign, i;
  sign = n;
  i = 0;
  do {
    int d = abs(n % b);
    s[i++] = (d > 9) ? d - 10 + 'a' : d + '0';
  } while ((n /= b) != 0);
  
  if(sign < 0)
    s[i++] = '-';

  s[i] = '\0';

  reverse(s);
}

//Where p represent a padding 
//small notice here C doesn't support overloading then it's impossible to set a 2 methodes with the same name even if the signature differt
void itoa_v2(int n, char s[], int p){
  int sign, i;
  sign = n;
  i = 0;
  do {
    s[i++] = abs(n % 10) + '0';
  } while ((n /= 10) != 0);

  if(sign < 0)
    s[i++] = '-';

  while(i < p)
    s[i++] = ' ';

  s[i] = '\0';
  reverse(s);
}

int main(int argc, char *argv[])
{
  int t = 4902;
  char seq[100];
  
  itoa(INT_MIN, seq);
  printf("%d : %s \n", INT_MIN, seq);

  itob(t, seq, 16);
  printf("%d : %s \n", t, seq);

  itoa_v2(t, seq, 8);
  printf("%d : %s \n", t, seq);

  return EXIT_SUCCESS;
}
