#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main()
{
  long long i;
  long double sum = .0;
  long double sec = .0;

  struct  timeval start;
  struct  timeval end1;
  unsigned  long diff;

  // Multi-thread compute start
  clock_t t1 = clock();
  gettimeofday(&start,NULL);
  #pragma omp parallel for
  for(i = 0; i < 1000000000; i++) {
    sum += i/100;
  }
  gettimeofday(&end1,NULL);
  diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
  printf("the difference is %ld n: \n",diff);



  clock_t t2 = clock();

  sec = (t2 - t1);
  //sec = (t2 - t1);
  printf("Program costs %.2Lf clock tick.\n", sec);
  exit(EXIT_SUCCESS);
}
