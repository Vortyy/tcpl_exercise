/************************************************************************************
 * The C Programming Language 5-3:
 * 
 * -> write a function htoi(s) -> take a string of hex decimal value and convert it
 *    to its equivalent in integer value
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>
#include <string.h>

#define stringify(x) #x                 /* turn into a string a token # this macros quote x */
#define concat(i, j) stringify(i ## j)  /* concate 2 token into one but don't quote theme */

void strcat_my(char *s, char *t){
  int i = 0;
  while(*s)
    s++; 
  while((*s++ = *t++));
}

int strend(char *s, char *t){
  int size = strlen(t);

  while(*(s + size))
    s++;

  for(; *s == *t; s++, t++){
    if(*s == '\0')
      return 1;
  }

  return 0;
}

void strcpy_n(char *s, char *t, int n){
  while(*t && n-->0)
    *s++ = *t++;

  while(n-->0)
    *s++ = '\0';
}

void strcat_n(char *s, char *t, int n){
  while(*s) s++;
  while(*t && n-->0)
    *s++ = *t++;

  if(n <= 0)
    *s = '\0';
}

int strcmp_n(char *s, char *t, int n){
  for(; *s == *t; s++, t++)
    if(*s == '\0' || n--<=0)
      return 0;

  return *s - *t;
}

int main(){
  char s[100] = "Hello ";
  char *t = "World";

  char *word = "testing";
  char *endFilter = "fing";

  printf("concat macro : %s", concat(concat_, macro));
  strcat_my(s, t);
  printf("strcat : %s \n", s);

  printf("strend(%s, %s) : %d\n", word, endFilter, strend(word, endFilter));
  return 0;
}
