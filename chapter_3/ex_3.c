/************************************************************************************
 * The C Programming Language 3-3 :
 * 
 * -> write escape(s, t) that take a string t and convert all the \n and \t into a 
 *    real sequence of character and write the inverse of this function
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void expand(char s1[], char s2[]){
  char start, end;
  int i = 0, j = 0;

  while(s1[i] != '\0'){
    if(isdigit(s1[i]) || islower(s1[i])){
      start = s1[i];
      i += 2;
      end = s1[i++];
      for(int c = start; c <= end; c++){
        s2[j++] = c;
      }
    }

    if(s1[i] == '-'){
      if(j == 0){
        s2[j++] = '-';
        i++;
      } else {
        start = end;
        end = s1[++i];
        i++;
        for(int c = start; c <= end; c++){
          s2[j++] = c;
        }
      }
    }
  }

  s2[j] = '\0';
}

int main(int argc, char *argv[])
{
  char test[] = "a-z";
  char test2[] = "a-b-e";
  char test3[] = "a-z0-9";
  char test4[] = "-t-z";
  
  char result[100];
  expand(test, result);
  printf("%s -> %s \n", test, result);
 
  expand(test2, result);
  printf("%s -> %s \n", test2, result);

  expand(test3, result);
  printf("%s -> %s \n", test3, result);

  expand(test4, result);
  printf("%s -> %s \n", test4, result);
  return EXIT_SUCCESS;
}
