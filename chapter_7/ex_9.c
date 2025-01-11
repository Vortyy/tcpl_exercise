/************************************************************************************
 * The C Programming Language 7-9 :
 * 
 * -> write a function htoi(s) -> take a string of hex decimal value and convert it
 *    to its equivalent in integer value
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#define isupper(x) ((x) >= 'A' && (c) <= 'Z') ? 1 : 0 /* becarefull using macro can create double evaluation when using increment operator ++ */

int isupper_fct(char c){
  return c >= 'A' && c <= 'Z';
}
