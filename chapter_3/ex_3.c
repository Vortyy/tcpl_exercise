/************************************************************************************
 * The C Programming Language 3-3 :
 * 
 * -> Write a function expand(s1,s2) that expands shorthand notations like a-z into 
 *    the string s1 into the equivalent complete list abc...xyz in s2. Allow for 
 *    letters of either case and digits, and be prepared to handle cases like a-b-c 
 *    and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.
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
