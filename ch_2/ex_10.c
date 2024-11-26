/************************************************************************************
 * The C Programming Language 2-10 :
 * 
 * 2-10 -> rewrite lower fct with a ternary operator 
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdlib.h>
#include <stdio.h>

int lower(int c){
  return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

int main(int argc, char *argv[])
{
  char c = 'U';
  printf("%c to %c \n", c, lower(c));
  return EXIT_SUCCESS;
}
