#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <map>
#include <vector>

double test(double a[],double b[])
{
  b[0] = a[0] ;
  for(int i = 1; i<100; ++i) {
    b[i] = a[i] + a[i-1];
  }
}

int main()
{
  long long i;
  long double sum = .0;
  long double sec = .0;

  struct  timeval start;
  struct  timeval end1;
  unsigned  long diff;

  double a[100000] ;
  std::vector<double> b(100000,0) ;
  std::vector<double> m(100000,0) ;
  std::vector<double> n(100000,0) ;
  for(int i = 0; i<100; ++i) {
      m[i] = i;
  }

  test(&m[0],&n[0]);

  for(int i = 0; i<100; ++i) {
     std::cout <<  n[i]  << std::endl;
  }


  // Multi-thread compute start
  clock_t t1 = clock();
  gettimeofday(&start,NULL);
  for(int i =0; i<100000; ++i) {
    a[i] = random() ;
  }

  gettimeofday(&end1,NULL);
  diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
  printf("the difference is %ld n: \n",diff);


  std::map<std::string,int>::iterator iter;
  gettimeofday(&start,NULL);
  for(int i =0; i<100000; ++i) {
    b[i] = random() ;
    //b.push_back(i);
  }

  gettimeofday(&end1,NULL);
  diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
  printf("the difference is %ld n: \n",diff);




  clock_t t2 = clock();
  sec = (t2 - t1);
  printf("Program costs %.2Lf clock tick.\n", sec);
  exit(EXIT_SUCCESS);
}
