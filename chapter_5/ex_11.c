/************************************************************************************
 * The C Programming Language 5-11 and 5-12 :
 * 
 * -> rewrite entab and detab to accept a list of tab stop as arguments (use default:
 *    if no args)
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB_SIZE 8
#define DEFAULT_INC_SIZE 1

void entab();                         /* replace blanck space by tabulation */
void detab();                         /* replace tabulation by equivalent size of blanck space */ 
void set_tab(int argc, char *argv[]); /* reads arguments set check methods */
int check_tab(int pos);               /* check if pos % tab_size is equal to 0 */

int tab_mode = 0;
int tab_stop = 0;
int tab_size = DEFAULT_TAB_SIZE;

char **tab_argv;

int main(int argc, char *argv[]){
  set_tab(argc, argv);
  
  entab();
  //detab()
  return 0;
}

void detab(){
  int c, pos = 0;
  while((c=getchar()) != EOF)
    if(c == '\t')
      while(!check_tab(pos++))
        putchar(' ');
    else if(c == '\n'){
      putchar(c);
      pos = 0;
    } else{
      putchar(c);
      ++pos;
    }
}

void entab(){
  int c, pos;
  int nb = 0;
  int nt = 0;

  for(pos = 0; (c=getchar()) != EOF; pos++){
    if(c == ' '){
      if(!check_tab(pos))
        ++nb;
      else{
        nb = 0;
        ++nt;
      }
    } else {
      for(; nt > 0; nt--)
        putchar('\t');
      if(c == '\t')
        nb = 0;
      else{
        for(; nb > 0; nb--)
          putchar(' ');
      }
      putchar(c);
      if(c == '\n')
        pos = 0;
      else if(c == '\t')
        while(!check_tab(pos))
          ++pos;
    }
  }
}

int check_tab(int pos){
  if(tab_mode == 2){
    if(--tab_stop > 0)
      tab_size = atoi(*++tab_argv);
    else
      return 0;
  }
 
  return pos % tab_size == 0;
}

void set_tab(int argc, char *argv[]){
  if(argc == 1); /* no arguments */
  else if (argc == 3 && *argv[1] == '-' && *argv[2] == '+'){ /* range provided by user ex_12 */
    tab_mode = 1;
    tab_size = atoi(argv[1]);
  } 
  else{ /* user provided tab stops */
    tab_mode = 2;
    tab_stop = argc;
    tab_argv = argv;
    tab_size = atoi(*++tab_argv);
  } 
}
