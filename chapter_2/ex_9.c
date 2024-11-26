/************************************************************************************
 * The C Programming Language 2-9:
 * 
 * 2-9 -> change the bitcount fct that count the number of bit set has 1 in a int
 *        using x &= (x - 1) instead of a rightshift around the whole bits of the VALUE
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdlib.h>
#include <stdio.h>

//Here the trick is to understand that x &= x-1 always delete the rightmost 1 in a two
//complement number system allow the bit_count function to compute a lot faster by skipping
//all 0s between each one
//NOTICE : Here that in the worst case MAX_VALUE(full of 1) this bit_count will be <=> to 
//bit_count with rightshift the entire value
int bit_count(unsigned x){
  int b;
  for(b = 0; x != 0; x &= x-1){
    ++b;
  }
  return b;
}

int main(int argc, char *argv[])
{ 
  printf("Inside 7 there is %d bits set to 1\n", bit_count(7));
  return EXIT_SUCCESS;
}
