/************************************************************************************
 * The C Programming Language 4-1 :
 * 
 * -> 
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

//fun fact if return type is omitted then the return int is assumed until C99
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int get_line(char line[], int max);
int strindex(char source[], char searchfor[]);
int strindex_rightmost(char source[], char searchfor[]);

char pattern[] = "te";
/* find all lines matching pattern */
int main()
{
  char line[MAXLINE];
  int found = 0;
  
  while (get_line(line, MAXLINE) > 0)
    if (strindex_rightmost(line, pattern) >= 0) {
      printf("%s", line);
      found++;
    }
  return found;
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

/* strindex: return index of t in s, -1 if none */ 
int strindex(char s[], char t[]){
  int i,j,k;

  for(i = 0; s[i] != '\0'; i++){
    for(j = i, k=0; t[k] !='\0' && s[j] == t[k]; j++, k++)
      ;
    if(k>0 && t[k] == '\0')
      return i;
  }

  return -1;
}

//here the solution is to go read the line from the end so the first match will be always the right most
int strindex_rightmost(char s[], char t[]){
  int i, j, k;

  for(i = strlen(s) - 1; i > 0; i--){ //Error here the best optimisation would be to substract by strlen(t) because the first loop until i >= t will be false
    for(j = i, k=0; t[k] != '\0' && s[j] == t[k]; j++, k++)
      ;
    if(k>0 && t[k] == '\0')
      return i;
  }

  return -1;
}
