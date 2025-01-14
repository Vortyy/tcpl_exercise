/************************************************************************************
 * The C Programming Language 8-5 :
 * 
 * -> Modify the fsize program to print the other information contained in the inode
 *    entry.
 * 
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>

void dirwalk(char *, void (*fcn) (char *));
void fsize(char *);

int main(int argc, char *argv[]){
  if(argc == 1){
    fsize(".");
  } else{
    while (--argc > 0)
      fsize(*++argv);
  }
  return 0;
}

void fsize(char *name){
  struct stat stbuf;
  if(stat(name, &stbuf) == -1){
    fprintf(stderr, "fsize: can't access %s\n", name);
    return;
  }
  if((stbuf.st_mode & S_IFMT) == S_IFDIR) { /* S_IFMT filter the bit corresponding to type then compare it to id of dir */
    dirwalk(name, fsize);
  }
  printf("ino:%ld - s:%8ld bytes - %s of user %d\n", stbuf.st_ino, stbuf.st_size, name, stbuf.st_uid);
  /* i choose to write ino of the file + size and user owner */
}

#define MAX_PATH 1024

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn) (char *)){
  char name[MAX_PATH];
  struct dirent *dp;
  DIR *dfd;

  if((dfd = opendir(dir)) == NULL){
    fprintf(stderr, "dirwalk: can't open %s\n", dir);
    return;
  }
  while((dp = readdir(dfd)) != NULL){
    if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
      continue;
    if(strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
      fprintf(stderr, "dirwalk: d_name %s %s too long...\n", dir, dp->d_name);
    else{
      sprintf(name, "%s/%s", dir, dp->d_name);
      (*fcn) (name);
    }
  }
  closedir(dfd);
}
