#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

main()
{
  struct  timeval start;
  struct  timeval end1;
  unsigned  long diff;


  char aa[] = "21:00:00";
  char bb[] = "22:00:00";
  char aaa[] = "21:00:00";
  char bbb[] = "22:00:00";

  char tt[9] ;
  char temp[9] ;

  char cc[] = "301";
  char dd[] = "302";

  char *p1;
  char *p2;

  int a1, b1;
  a1 = 100;
  b1 = 200;

  int n=1000;

  //uBEE::SaveBin("../tick/tick.json",(const char*)message,length);
  int h=0;
  int m=0;
  int s=1000;
  int i = 0;
  gettimeofday(&start,NULL);
  for(i = 0 ; i<8600000 ; i++) {
    s = 2*s +i ;
    s = s/2;
  }
  gettimeofday(&end1,NULL);
  diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
  printf("the difference is %ld n:%d \n",diff,n);
  std::cout << s << std::endl;

  i = 0;
  gettimeofday(&start,NULL);
  for(i = 0 ; i<8600000 ; i++) {
    s = 2*s +i/2 ;
    s = s/2;
  }
  gettimeofday(&end1,NULL);
  diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
  printf("the difference is %ld n:%d \n",diff,n);
  std::cout << s << std::endl;

}
