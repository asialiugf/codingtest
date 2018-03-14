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
  int s=0;

  int i = 0;
  gettimeofday(&start,NULL);
  n=0;
  h=0;
  m=0;
  s=0;
  memset(tt+8,'\0',1) ;
  for(i = 0 ; i<86000 ; i++) {
    n++;
    h = n/3600;
    m = (n-h*3600)/60;
    s = n%60;
    sprintf(tt,"%02d:%02d:%02d",h,m,s);
    memcpy(temp,tt,9);
  }
  gettimeofday(&end1,NULL);
  diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
    std::cout << i << ":" << temp << std::endl;
  printf("the difference is %ld n:%d \n",diff,n);


  std::cout << p1 << " " << p2 <<  " " << a1 << b1 << ":" << n<< std::endl;

  gettimeofday(&start,NULL);
  n=0;
  h=0;
  m=0;
  s=0;
  memset(tt+8,'\0',1) ;
  memcpy(temp,"00:00:00",8);
  temp[9] = '\0';
  for(i = 0 ; i<86000 ; i++) {
    s+=1;
    if(s>=60) {
      s -=60;
      m+=1;
      if(m>=60) {
        m-=60;
        h+=1;
        sprintf(tt,"%02d:%02d:%02d",h,m,s);
        memcpy(temp,tt,9);
      } else {
        memcpy(tt,temp,3);
        sprintf(tt+3,"%02d:%02d",m,s);
        memcpy(temp,tt,9);
      }
    } else {
      memcpy(tt,temp,6);
      sprintf(tt+6,"%02d",s);
      memcpy(temp,tt,9);
    }
  }
  gettimeofday(&end1,NULL);
  diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
    std::cout << i << ":" << temp << std::endl;
  printf("the difference is %ld n:%d \n",diff,n);

  std::cout << p1 << " " << p2 <<  " " << a1 << b1 << ":" << n<< std::endl;




  gettimeofday(&start,NULL);
  n=0;
  for(int i = 0 ; i<1000000001 ; i++) {
  }
  gettimeofday(&end1,NULL);
  diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
  printf("the difference is %ld n:%d \n",diff,n);


  std::cout << p1 << " " << p2 <<  " " << a1 << b1 << ":" << n<< std::endl;
}
