#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int main()
{
//    struct tm *ptr;
  time_t lt;
  char tmpbuf[1288];
  struct tm *newtime;
  //lt =(time_t)1218246780;
  double db = 1.46519639950003e+18;
  double mm = db/1000000000;
  int kk = mm*1000;
  double cc = mm*1000 - kk;
  double dd = cc * 1000000;
  lt =(time_t)mm;
  newtime = localtime(&lt);
  strftime(tmpbuf, 128, "%F %T\n", newtime);
  printf((char *)tmpbuf);
  
  printf( "%lf\n",mm);




  char ca_dt[100];
  char ca_ms[7];
  memset(ca_dt,'\0',100);
  memset(ca_ms,'\0',7);
  sprintf(ca_dt,"%lf",mm);
  int len = strlen(ca_dt);
  int len2 = len-6;
  memcpy(ca_ms,&ca_dt[len2],6);

  printf(ca_ms);


  double lf = 3.14560000000;
  printf("\n%lf\n",lf );
  printf( "%g\n",lf);


  printf("-----------------------------\n");
  char DATE[]="20180108" ;
  char wday[][6]= {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

  char y[5];
  char m[3];
  char d[3];
  memset(y,'\0',5);
  memset(m,'\0',3);
  memset(d,'\0',3);
  int iy,im,id;
  memcpy(y,DATE,4);
  memcpy(m,DATE+4,2);
  memcpy(d,DATE+6,2);
  std::cout << y << m << d << std::endl;
  iy = atoi(y);
  im = atoi(m);
  id = atoi(d);
  std::cout << iy << im << id << std::endl;
  struct tm *p;
  struct tm timetm;
  time_t sec;
  timetm.tm_mday = id;
  timetm.tm_mon  = im;
  timetm.tm_year = iy;
  timetm.tm_hour = 0;
  timetm.tm_min  = 0;
  timetm.tm_sec  = 0;
  sec = mktime(&timetm);
  p = gmtime(&sec);
  printf("y:%d m:%d d:%d \n",(1900+p->tm_year), (1+p->tm_mon),p->tm_mday);
  printf("%s %d; %d; %d\n", wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);

int iWeek = (id + 2 * im + 3 * (im + 1) / 5 + iy + iy / 4 - iy / 100 + iy / 400) % 7;  
 
std::cout << "week:" << iWeek+1 << std::endl;






  return 0;
}
