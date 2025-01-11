/************************************************************************************
 * The C Programming Language 7-9 :
 * 
 * -> Functions like isupper can be implemented to save space or to save time.
 *    Explore both possibilities. 
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

/* save time --> because less instructions since there is no fct overhead */
#define isupper(x) ((x) >= 'A' && (c) <= 'Z') ? 1 : 0 /* becarefull using macro can create double evaluation when using increment operator ++ */

/* save space --> because it is not rewritten in the entire file */
int isupper_fct(char c){
  return c >= 'A' && c <= 'Z';
}
