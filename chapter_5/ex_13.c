/************************************************************************************
 * The C Programming Language 5-13:
 * 
 * -> Write the program tail, which prints the last n lines of its input. By default, 
 *    n is set to 10, let us say, but it can be changed by an optional argument
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000
#define MAXLINES 100
#define DEFAULT_VALUE 10

char *lineptr[MAXLINES];
void writelines(char *lines[], int  nb_lines, int i);

int main(int argc, char *argv[]){
  int nb_lines, nread, i = 0;
  size_t size = 0;

  if(argc <= 1)
    nb_lines = DEFAULT_VALUE;
  else if(argc == 2 && *argv[1] == '-' && (nb_lines = atoi(++argv[1])) && nb_lines < MAXLINES) /* check if there is a real number as arg */
    ;
  else{
    printf("error : no valid arguments\n");
    return 1;
  }

  printf("tail value set to %d \n\n", nb_lines);

  while((nread = getline(lineptr + i, &size, stdin)) >= 1 && *lineptr[i] != '\n'){ /* store line and add a stop when your skip line */
    i++;
  }

  writelines(lineptr, nb_lines, i);
  return 0;
}

void writelines(char *lines[], int nb_lines, int i){
  int pr = (i - nb_lines < 0) ? i : nb_lines;
  lines = lines + i - pr; /* lines set to the start of a tail */;

  while(pr-- > 0)
    printf("%s", *lines++);
}
