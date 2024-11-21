/************************************************************************************
 * tcpl ch2 ex1 :
 * 
 * -> write a program to determine range of different data type by 2 methods printing
 *    from headers and direct computation
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>

unsigned long mod(int n){
  /*if(n > 0){*/
  /*  unsigned long res = 1;*/
  /*  for(int i = 0; i < n; i++){*/
  /*   res *= 2;*/
  /*  }*/
  /*  return res;*/
  /*}*/
  /*return 0; */
  return pow(2, n);
}

int main(int argc, char *argv[])
{
  //using header constants to print ranges
  //printf using %[length]specifier -> [hh]d = char signed
  printf("----------------- Signed ----------------\n");
  printf("-> from headers limit.h : \n");
  printf("char from %hhd to %hhd\n", CHAR_MIN, CHAR_MAX);
  printf("short from %hd to %hd\n", SHRT_MIN, SHRT_MAX);
  printf("int from %d to %d\n", INT_MIN, INT_MAX);
  printf("long from %ld to %ld\n", LONG_MIN, LONG_MAX);

  //using computation to print ranges
  //computation is the following -> 2^(nb_bits of a type) and -1 if the higher (take into 0 in our range)
  //in case its signed nb_bits - 1 (bcs of the sign bit)
  printf("\n-> from computation : \n");
  printf("char from -%lu to %lu\n", mod(CHAR_BIT * sizeof(char) - 1), mod(CHAR_BIT * sizeof(char) - 1) - 1);
  printf("short from -%lu to %lu\n", mod(CHAR_BIT * sizeof(short) - 1), mod(CHAR_BIT * sizeof(short) - 1) - 1);
  printf("int from -%lu to %lu\n", mod(CHAR_BIT * sizeof(int) - 1), mod(CHAR_BIT * sizeof(int) - 1) - 1);
  printf("long from -%lu to %lu\n", mod(CHAR_BIT * sizeof(long) - 1), mod(CHAR_BIT * sizeof(long) - 1) - 1);

  printf("\n--------------- Unsigned ----------------\n");
  printf("-> from headers limit.h : \n");
  printf("char from %hhu to %hhu\n", 0, UCHAR_MAX);
  printf("short from %hu to %hu\n", 0, USHRT_MAX);
  printf("int from %u to %u\n", 0, UINT_MAX);
  printf("long from %lu to %lu\n", (long) 0, ULONG_MAX);

  printf("\n-> from computation : \n");
  printf("char from %lu to %lu\n", (long) 0, mod(CHAR_BIT * sizeof(char)) - 1);
  printf("short from %lu to %lu\n", (long) 0, mod(CHAR_BIT * sizeof(short)) - 1);
  printf("int from %lu to %lu\n", (long) 0, mod(CHAR_BIT * sizeof(int)) - 1);
  printf("long from %lu to %lu\n", (long) 0, mod(CHAR_BIT * sizeof(long)) - 1);

  //decimal precision in C use norm IEEE 754 float : [1 sign bit][8 exposant bits][23 mantissa bits]
  //value of float = (-1)^S * (1.0 + 0.M) * 2^(E - 127)
  //specifity to know -> the mantissa is between 1.0 and 2 maximum, and its value bit 23 is 1/2, bit 22 is 1/4 and so o
  //-------------------> the mantissa will no longer use 1.0 when the minimal exponent is used (allow gradual underflow) 
  printf("\n-------------- Floating -----------------\n");
  printf("-> from headers float.h : \n");
  printf("float from %e to %e\n", FLT_MIN, FLT_MAX);
  printf("double from %e to %e\n", DBL_MIN, DBL_MAX);

  printf("-> from computation : \n");
  //aproximate 7 precision 
  printf("float from %e to %e\n", - (1.0 + ))

  
  return EXIT_SUCCESS;
}