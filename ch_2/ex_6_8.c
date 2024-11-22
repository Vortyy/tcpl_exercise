/************************************************************************************
 * The C Programming Language 2-6, 2-7 and 2-8:
 * 
 * 2-6 -> write a fct setbits(x,p,n,y) that return x with n bits that begin at p set
 *        set to the rightmost n bits of y, leaving the other bits unchanged
 *
 * 2-7 -> write a fct any(s1, s2) that return the first location in a string s1 where
 *        any character from the string s2 occurs, or -1 if s1 contains no char from
 *        s2. (<=> strpbrk)
 * 
 * 2-8 -> ...
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// << or >> an unsigned will always fill vacated bits with 0
// >> a signed depend of machines implemetation (cf. logical shift don't touch sign bit, etc...)
void printBits(unsigned char c){
  printf("%3d : ", c);

  for(int i = 7; i > 0; i--){
    unsigned char byte = (c >> i) & 1;
    printf("%u", byte);
  }

  printf("\n");
}

int main(int argc, char *argv[])
{
  //when constant are initialise if there is 0 in front means its an octal
  //and when 0x it's an hexadecimal
  unsigned char n = 255;//11111111

  printBits(n);
  n = n & ~0177; // <=> n & 127
  printBits(n);
  return EXIT_SUCCESS;
}
