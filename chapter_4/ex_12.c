/************************************************************************************
 * The C Programming Language 4-12, 4-13 :
 * 
 * -> 
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define abs(x) ((x < 0) ? -(x) : (x))

//We could easily do an interface wrapper to keep the same interface with reverse which is only char s[] as argument
void reverse_wrapper(char s[]){
  void reverse_rec(char s[], int i, int j);
  reverse_rec(s, 0, strlen(s) - 1);
}

void reverse(char t[]){
  int c, i, j;
  for(i = 0, j = strlen(t) - 1; i < j; i++, j--){
    c = t[i];
    t[i] = t[j];
    t[j] = c;
  }
}

void reverse_rec(char t[], int i, int j){
  if(i < j){
    char tmp = t[i];
    t[i] = t[j];
    t[j] = tmp;
    reverse_rec(t, ++i, --j);
  }
}

//same as itoa written in ex_4 chapter 3 unless using recursive fucntion (still need to reverse it a the end) 
void itoa_rec(int n, char s[], int i){
  if(n/10){
    s[i] = abs(n%10) + '0';
    itoa_rec(n/10, s, ++i);
  }else { 
    s[i++] = abs(n%10) + '0';
    if(n < 0){
      s[i++] = '-';
    } 
    s[i] = '\0';
  }
}

//Here we make a great use of internal static variable to get index into sequence s and adding corresponding number and end marker at 
//each step of the process
void itoa_rec_stat(int n, char s[]){
  static int i;

  if(n/10){
    itoa_rec_stat(n/10, s);
  }else{
    i = 0;
    if(n < 0)
      s[i++] = '-';
  }

  s[i++] = abs(n%10) + '0';
  s[i] = '\0';
}

int main(){
  char s[100]; 
  int n = -19952;

  itoa_rec(n, s, 0);
  /*reverse_rec(s, 0, strlen(s) - 1);*/
  reverse_wrapper(s);

  printf("%s \n", s);

  itoa_rec_stat(n, s);
  printf("%s \n", s);

  return 0;
}
