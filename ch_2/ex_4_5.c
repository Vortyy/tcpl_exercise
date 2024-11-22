/************************************************************************************
 * The C Programming Language 2-4 and 2-5 :
 * 
 * 2-4 -> write a fct squeeze(s1, s2) that deletes each char in s1 that matches any 
 *        char in s2
 *
 * 2-5 -> write a fct any(s1, s2) that return the first location in a string s1 where
 *        any character from the string s2 occurs, or -1 if s1 contains no char from
 *        s2. (<=> strpbrk)
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdlib.h>
#include <stdio.h>

//this is done by a linear search a each char of s a faster way will be to create 
//a HashTable base on filter and make loop through using char as key and check if 
//there is key if yes no keep it, else keep it
void squeeze(char* s, char* filter){
  int i, j, k;

  for(i = j = 0; s[i] != '\0'; i++){
    int remove = 0;
    for(k = 0; filter[k] != '\0'; k++){
      if(filter[k] == s[i])
        remove = 1; 
    }

    if(remove == 0){
      s[j++] = s[i];
    }
  }

  s[j] = '\0';
}

//Same constat with any --> HashMap could be useful if optimization needed
int any(char *s, char *match){
  int result = -1;
  int i, j;

  for(i = 0; s[i] != '\0'; i++)
    for(j = 0; match[j] != '\0'; j++)
      if(s[i] == match[j] && result == -1)
        result = i;

  return result;
}

int main(int argc, char *argv[])
{
  char line[] = "This so weird i like writing in C";
  char filter[] = "isT "; //with space char squeeze gives so weird result
  char match[] = "z";

  printf("before squeeze : %s \n", line);
  printf("any match of %s find at : %d \n", match, any(line, match));

  squeeze(line, filter);

  printf("squeezed by %s : %s \n", filter, line);

  return EXIT_SUCCESS;
}
