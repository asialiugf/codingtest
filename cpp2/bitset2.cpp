#include <iostream>
#include <bitset>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <memory.h>
using namespace std;
struct A {
  int a:3;
  unsigned int b:5;
  int c:2;
  int d:1;
  int e:1;
  int f:9;
};
int main(void)
{
  char str[100] = "0134324324afsadfsdlfjlsdjfl";
  struct A d;
  memcpy(&d, str, sizeof(A));
  cout << sizeof(A) << endl;
  cout << d.a << endl;
  cout << d.b << endl;
  cout << d.c << endl;

  std::bitset<8> bitf1 = std::bitset<8>(str[0]);
  cout << bitf1 << endl;
  bitf1 = std::bitset<8>(str[1]);
  //std::bitset<64> bitz1 = std::bitset<64>(*(unsigned long*)&dz1);
  cout << bitf1 << endl;
  cout <<  endl;
  cout <<  endl;
  d.b = 31 ;
  memcpy(str,&d,sizeof(A));
  cout << bitf1 << endl;

  std::bitset<8> b[20] ;
  std::bitset<32> a ;
  for(int i=0; i<20; ++i) {
    b[i] = std::bitset<8>(str[i]);
    cout << b[i] << endl;
  }
  a.set(3,10);
  cout << a << endl;

  return 0;
}
