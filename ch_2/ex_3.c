/************************************************************************************
 * The C Programming Language 2-3 :
 * 
 * -> write a function htoi(s) -> take a string of hex decimal value and convert it
 *    to its equivalent in integer value
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getHexValue(char c){
  if(c >= '0' && c <= '9')
    return c - '0';

  if(c >= 'a' && c <= 'f')
    return c - 'a' + 10;

  if(c >= 'A' && c <= 'f')
    return c + 'a' - 'A' + 10; // lower : convert char c to lower case; WARNING ASCII only 

  return -1;
}

int htoi(char hex[]){
  int i = strlen(hex) - 1;
  int result = 0, padding = 0, j = 0;

  if(hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
    padding += 2;

  while(i >= 0 + padding){
    int char_val = getHexValue(hex[i]);
    if(char_val != -1){
      printf("%d \n", char_val);
      result += char_val * (int) pow(16, j);
      i--;
      j++;
    } else {
      fprintf(stderr, "Error inside char %c is outside of hexRange", hex[i]);
      return 0;
    }
  }
    
  return result;
}

int main(int argc, char *argv[])
{
  char hex_nb[] = "5e36";
  printf("hex : %s \n", hex_nb);

  int convert = htoi(hex_nb);
  printf("int : %d \n", convert);
    
  return EXIT_SUCCESS;
}
