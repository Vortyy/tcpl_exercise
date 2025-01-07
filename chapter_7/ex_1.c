/************************************************************************************
 * The C Programming Language 7-1:
 * 
 * -> Write a program that converts upper case to lower or lower case to upper,
 *    depending on the name it is invoked with, as found in argv[0]. 
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* interesting fact the <file operator cause to the program to read the content into
 * a char stream that can be read via getchar(), as example you can run this prog 
 * after compiled it such ./ex_1 <test.txt and it will upper or lower case inside*/

/* second fact interestion you can run one program that will flow it's output into 
 * another such otherprog | prog -> in that case the output of otherprog will be 
 * read by prog, as example you can do echo "test" | ./ex_1 */

int main(int argc, char *argv[]){
  int c, lower, upper; /* type of conv */

  if((lower = strcmp("./lower", argv[0])) == 0 || (upper = strcmp("./upper", argv[0])) == 0){
    while((c = getchar()) != EOF){
      if(lower == 0)
        putchar(tolower(c));
      else if (upper == 0)
        putchar(toupper(c));
    }
  } else {
    printf("wrong argv[0]\n");
  }

  return 0;
}
