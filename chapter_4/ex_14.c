 /************************************************************************************
 * The C Programming Language 4-14:
 * 
 * -> 
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/ 

 #include <stdio.h>

 //this example is here to show that macro is just replacement of placeholder then you need
 //to be carefull when used 
 #define square(x) x * x
 #define square_p(x) (x) * (x)

 #define swap(x, y, t) {\
   t _z = x;\
   x = y;\
   y = _z;\
   }

 int main(){
   int z = 5;

   int x = 7;
   int y = 1828;
    
   //as we can see a block is runned like normal line
   {
     printf("block test\n");
   }

   // result = z + 1 * z + 1
   int result = square(z + 1);
   printf("%d \n", result); 

   //result = (z + 1) * (z + 1)
   result = square_p(z + 1);
   printf("%d \n", result);

   printf("x : %d and y : %d\n", x, y);
   swap(x, y, int);
   printf("x : %d and y : %d\n", x, y);

   return 0;
 }
