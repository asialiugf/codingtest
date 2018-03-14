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

  char cc[] = "301";
  char dd[] = "302";

  char *p1;
  char *p2;

  int a1, b1;
  a1 = 100;
  b1 = 200;

  int n=1000;

  //uBEE::SaveBin("../tick/tick.json",(const char*)message,length);
  gettimeofday(&start,NULL);

  n=0;
  for(int i = 0 ; i<1000000001 ; i++) {
    if(a1!=b1) {
      if(i > 2) {
        p1 = aa;
        p2 = bb;
        n++;
      }
    } else {
      p1= bb;
      p2= aa;
    } ;
    a1++;
    b1++;
    if(i%2 ==0) {
      p1 = cc;
      p2 = dd;
    } else {
      p1 = dd;
      p2 = cc;
    }
  }
  gettimeofday(&end1,NULL);
  diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
  printf("the difference is %ld n:%d \n",diff,n);


  std::cout << p1 << " " << p2 <<  " " << a1 << b1 << ":" << n<< std::endl;

  gettimeofday(&start,NULL);

  n=0;
  for(int i = 0 ; i<1000000001 ; i++) {
    if(i > 2) {
      p1 = aa;
      p2 = bb;
      n++;
    }
    a1++;
    b1++;
    if(i%2 ==0) {
      p1 = cc;
      p2 = dd;
    } else {
      p1 = dd;
      p2 = cc;
    }
    if(a1!=b1) {
        p1 = bb;
        p2 = aa;
    }
  }

  gettimeofday(&end1,NULL);
  diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
  printf("the difference is %ld n:%d \n",diff,n);

  std::cout << p1 << " " << p2 <<  " " << a1 << b1 << ":" << n<< std::endl;

}
