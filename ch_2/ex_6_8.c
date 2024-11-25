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
void printBits(unsigned int t){
  printf("%-10u : ", t);

  for(int i = 31; i >= 0; i--){
    if(((i + 1) & 7) == 0) //here he check if one of 3 first bits is set meaning that is not divisible by eigth; 
      printf(" ");
    printf("%u", (t >> i) & 1);
  }

  printf("\n");
}

unsigned set_bits(int x, int p, int n, int y){
  printBits(x); printBits(y);
  x = ~(~(~0 << n) << (p + 1 - n)) & x; // give the mask type 1111 1100 1111 1111 --> then the AND reset those 00 on x
  y = (~(~0 << n) & y) << (p + 1 - n); // give the y full of 0 execpt on p + n range where it is y values
  printBits(x); printBits(y);
  return x | y;
}

//best way to write it the upper case is only demonstrative purpose
/*unsigned set_bits(int x, int p, int n, int y){*/
/*  return ~(~(~0 << n) << (p + 1 - n)) & x */
/*  | (~(~0 << n) & y) << (p + 1 - n); */
/*}*/

unsigned invert(int x, int p){
  return 0;
}

int main(int argc, char *argv[])
{
  //when constant are initialise if there is 0 in front means its an octal
  //and when 0x it's an hexadecimal
  unsigned int x = 255;//11111111
  unsigned int p = 4;
  unsigned int n = 2;
  unsigned int y = 18; //random value here

  printf("set_bits operations : \n");
  x = set_bits(x, p, n, y);

  printf("set_bits result : \n");
  printBits(x);
  //shift bit not erase them which is really different 
  return EXIT_SUCCESS;
}
