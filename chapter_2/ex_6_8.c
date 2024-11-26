/************************************************************************************
 * The C Programming Language 2-6, 2-7 and 2-8:
 * 
 * 2-6 -> write a fct setbits(x,p,n,y) that return x with n bits that begin at p set
 *        set to the rightmost n bits of y, leaving the other bits unchanged
 *
 * 2-7 -> write invert(x, p, n) a fonction that invert the n bit from p position 
 *
 * 2-8 -> write a rightrotation(x, n) a fct that return x right rotated by a n value
 *
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

//XOR here produce 1 wher bitA != bitB everything else produce 0
unsigned invert(int x, int p, int n){
  return x ^ (~(~0 << n) << (p + 1 - n));
}

unsigned right_rot(int x, int n){
  unsigned tmp;
  while(n-- > 0){
    tmp = (x & 1) << 31; // shift rightmost value to the leftmost part
    x = x >> 1;
    x = x | tmp; 
  }
  return x;
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

  printf("\ninvert bits : \n");
  x = invert(x, p, n);
  printBits(x);

  printf("\nright rotation by 3 : \n");
  x = right_rot(x, 3);
  printBits(x);
  //shift bit not erase them which is really different 
  return EXIT_SUCCESS;
}
