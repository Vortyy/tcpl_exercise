/************************************************************************************
 * The C Programming Language 3-1 :
 * 
 * -> Our binary search makes two tests inside the loop, when one would suffice (at
 *    the price of more tests outside.) Write a version with only one test inside The
 *    loop and measure the difference in run-time.
 *
 * Copyright (c) 2024 CHABOT Yohan 
 ************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Error in the version provided by the book of binsearch high was equal to mid + 1
// -> Causing infinite loop cause never ending in certain case
//This is the corrected version
int binsearch_book(int x, int v[], int n){
  int low, high, mid;
  low = 0;
  high = n - 1;
  while(low <= high){
    mid = (low + high)/2;
    if(x < v[mid])
        high = mid - 1;
    else if (x > v[mid])
        low = mid + 1;
    else
      return mid; // match
  }
  return -1; // no match
}

//binasearch exercise
int binsearch(int x, int v[], int n){
  int low, high, mid;
  low = 0;
  high = n - 1;
  mid = (low + high)/2;
  while(low <= high && x != v[mid]){
    if(x < v[mid])
      high = mid - 1;
    else
      low = mid + 1;
    mid = (low + high)/2;
  }

  if(x == v[mid]){ //
    return mid;
  } else {
    return -1;
  }
}

void generate_array(int *arr, int n){
  for(int i = 0; i < n; i++){
    arr[i] = i * 3;
  }
}

double get_time(clock_t begin, clock_t end){
  return ((double) (end - begin) * 1000 / CLOCKS_PER_SEC); 
}

int main(int argc, char *argv[])
{
  clock_t begin, end;
  int n = 1000000;
  int x = 9;

  int arr[n];
  generate_array(arr, n);

  printf("array of %d elements generated \n", n);

  begin = clock();
  int b_result = binsearch_book(x, arr, n);
  end = clock();
  printf("binary search from book find idx : %d - took : %fms\n", b_result, get_time(begin, end));
 
  begin = clock();
  b_result = binsearch(x, arr, n);
  end = clock(); 
  printf("binary search new version find idx : %d - took : %fms\n", b_result, get_time(begin, end));

  return EXIT_SUCCESS;
}
