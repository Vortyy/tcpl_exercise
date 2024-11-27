/************************************************************************************
 * The C Programming Language 3-2 :
 * 
 * -> write escape(s, t) that take a string t and convert all the \n and \t into a 
 *    real sequence of character and write the inverse of this function
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#define NEW_LINE_CHAR '\010'

void escape(char *s, char *t){
  int i, j;

  for(i = j = 0; t[i] != '\0'; i++){
    switch(t[i]){
      case '\n' :
        s[j++] = '\\';
        s[j++] = 'n';
        break;
      case '\t' :
        s[j++] = '\\';
        s[j++] = 't';
        break;
      default :
        s[j++] = t[i]; 
        break;
    }
  }

  s[j] = '\0';
}

void escape_invert(char *s, char *t){
  int i, j;

  for(i = j = 0; t[i] != '\0'; i++){
    if(t[i] != '\\')
      s[j++] = t[i];
    else 
      switch(t[++i]){
        case 'n' :
          s[j++] = '\n';
          break;
        case 't' :
          s[j++] = '\t';
          break;
        default :
          s[j++] = '\\';
          s[j++] = t[i];
          break;
      }
  }

  s[j] = '\0';
}


int main(int argc, char *argv[])
{
  char *t = "\n\t\t\t\ntest\nt\t\t";
  char s[100];
  char s2[100];//for pratical reason i used a tab to store the result but equivalent (reason avoid allocation)

  escape(s, t);
  printf("converted : %s \n", s);

  escape_invert(s2, s);
  printf("unconverted : %s \n", s2);

  return EXIT_SUCCESS;
}
