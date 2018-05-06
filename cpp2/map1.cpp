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

int main()
{
  long long i;
  long double sum = .0;
  long double sec = .0;

  struct  timeval start;
  struct  timeval end1;
  unsigned  long diff;

  std::map<std::string,int> mm;
  mm["ru1801"] = 6;
  mm["ru18201"] = 6;
  mm["ru18c01"] = 6;
  mm["ru1x801"] = 6;
  mm["ru1m801"] = 6;
  mm["ru1i801"] = 6;
  mm["ru18d01"] = 6;
  mm["ru18f01"] = 6;
  mm["ru18d01"] = 6;
  mm["ru180d1"] = 6;
  mm["ru18s01"] = 6;
  mm["ru18adf01"] = 6;
  mm["ru18d01"] = 6;
  mm["rud1801"] = 6;
  mm["ruc1801"] = 6;
  mm["ru1c801"] = 6;
  mm["rxu18c01"] = 6;
  mm["ru180ss1"] = 6;

  char xx[][15] = {
    "ru1801",
    "ru18201",
    "ru18c01",
    "ru1x801",
    "ru1m801",
    "ru1i801",
    "ru18d01",
    "ru18f01",
    "ru18d01",
    "ru180d1",
    "ru18s01",
    "ru18adf01",
    "ru18d01",
    "rud1801",
    "ruc1801",
    "ru1c801",
    "rxu18c01",
    "ru180ss1",
  };
  char yy[][15] = {
    "ru1801",
    "ru18201",
    "ru18c01",
    "ru1x801",
    "ru1m801",
    "ru1i801",
    "ru18d01",
    "ru18f01",
    "ru18d01",
    "ru180d1",
    "ru18s01",
    "ru18adf01",
    "ru18d01",
    "rud1801",
    "ruc1801",
    "ru1c801",
    "rxu18c01",
    "ru180ss1",
  };


  int pp;

  // Multi-thread compute start
  clock_t t1 = clock();
  gettimeofday(&start,NULL);

  for(int i=0; i<1000000; ++i) {
    for(int j=0; j<18; ++j) {
      for(int x=0; x<18; ++x) {
        if(memcmp(yy[j],xx[x],strlen(yy[j])) ==0) {
          pp = x ;
        }
      }
    }
  }

  gettimeofday(&end1,NULL);
  diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
  printf("the difference is %ld n: \n",diff);


  std::map<std::string,int>::iterator iter;
  gettimeofday(&start,NULL);

  for(int i=0; i<1000000; ++i) {
    for(int j=0; j<18; ++j) {
      iter=mm.find(yy[j]);
      if(iter!=mm.end()) {
        pp = iter->second;
      }
    }
  }

  gettimeofday(&end1,NULL);
  diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
  printf("the difference is %ld n: \n",diff);




  clock_t t2 = clock();
  sec = (t2 - t1);
  std::cout << pp << std::endl;
  printf("Program costs %.2Lf clock tick.\n", sec);
  exit(EXIT_SUCCESS);
}
