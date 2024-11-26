/************************************************************************************
 * The C Programming Language 2-2 :
 * 
 * -> rewrite for loop below w/o using && and || operators 
 *    for(i = 0; i < lim - 1 && (c=getchar()) != '\n' && c != EOF; i++)
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#define LINE_SIZE 7

int main(int argc, char *argv[])
{
  int i, c;
  char line[LINE_SIZE];

  //Here we use multiplication that correspond to logical && because TRUE = 1 and FALSE = 0 
  //then the multiplication will be 1 only if all the values will be one. The || operator 
  //can be translate by + arimethic... 
  for(i = 0; (i < LINE_SIZE - 1) * ((c = getchar()) != '\n') * (c != EOF); i++)
    line[i] = c;
 
  if(c == '\n'){
    line[i] = c;
    i++;
  }

  line[i] = '\0';

  printf("%s", line);

  return EXIT_SUCCESS;
}
