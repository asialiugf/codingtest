#include <iostream>
#include <bitset>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

using namespace std;
int main()
{
  int a = 100;
  long b;
  double c;
  char d;
  wchar_t e;
  bool f;
  float g;
  int* p;
  int& i=a;
  long long l;
  std::cout << "int: " << sizeof(a) << std::endl;
  std::cout << "long: " << sizeof(b) << std::endl;
  std::cout << "double: " << sizeof(c) << std::endl;
  std::cout << "char: " << sizeof(d) << std::endl;
  std::cout << "wchar_t: " << sizeof(e) << std::endl;
  std::cout << "bool: " << sizeof(f) << std::endl;
  std::cout << "float: " << sizeof(g) << std::endl;
  std::cout << "int*: " << sizeof(p) << std::endl;
  std::cout << "int&: " << sizeof(i) << std::endl;
  std::cout << "long long: " << sizeof(l) << std::endl << std::endl << std::endl;
//----------------
  double df1 = -639.6;
  double df2 = -790.2;
  double dz1 = 14.06251;
  double dz2 = 5;

  //std::bitset<64> bit_df1 = std::bitset<64>(df1);
  std::bitset<64> bit_df1 = std::bitset<64>(*(int64_t *)&df1);
  std::bitset<64> bit_df2 = std::bitset<64>(*(int64_t *)&df2);
  std::bitset<64> bit_dz1 = std::bitset<64>(*(int64_t *)&dz1);
  std::bitset<64> bit_dz2 = std::bitset<64>(*(int64_t *)&dz2);

  std::bitset<64> xor_df = bit_df1^bit_df2 ;
  std::bitset<64> xor_dz = bit_dz1^bit_dz2 ;

  std::bitset<64> r_df = xor_df^bit_df1 ;
  std::bitset<64> r_dz = xor_dz^bit_dz1 ;

  cout << "bit_df1:" << bit_df1 << endl;
  cout << endl;
  cout << "bit_df2:" << bit_df2 << endl;
  cout << "r_df   :" << r_df << endl;
  cout << endl;
  cout << "bit_dz1:" << bit_dz1 << endl;
  cout << endl;
  cout << "bit_dz2:" << bit_dz2 << endl;
  cout << "r_dz   :" << r_dz << endl;

  cout << "xor_df :" << xor_df << endl;
  cout << "xor_dz :" << xor_dz << endl;


  int64_t lf1 = df1*100000;
  int64_t lf2 = df2*100000;
  int64_t lz1 = dz1*100000;
  int64_t lz2 = dz2*100000;

  int64_t lcz = lz1^lz2 ;
  int64_t lcf = lf1^lf2 ;

  int leadingZeros = __builtin_clzll(lcf);
  int Zeros = __builtin_ffsll(lcf);
  cout <<"leadingZeros:"<< leadingZeros << endl;
  cout <<"Zeros:"<< Zeros << endl;

  int64_t uiz = dz1*100000;
  int64_t uif = df1*100000;


//  memcpy((char *)&d1,(char *)&dd,4) ;
//  memcpy((char *)&d2,(char *)&dd+4,4) ;

  std::cout << "df1:  " << df1 <<std::endl;
  std::cout << "df2:  " << df2 <<std::endl;
  std::cout << "dz1:  " << dz1 <<std::endl;
  std::cout << "dz2:  " << dz2 <<std::endl;

  std::bitset<64> bitf1 = std::bitset<64>(*(int64_t*)&df1);
  std::bitset<64> bitz1 = std::bitset<64>(*(int64_t*)&dz1);

  std::bitset<64> data ;
  //data.reset();
  //std::cout <<"data:" << data << std::endl;

  std::cout << "df1:"<< std::bitset<64>(*(int64_t *)&df1) << std::endl;
  std::cout << "dz1:"<< std::bitset<64>(*(int64_t *)&dz1) << std::endl;
  std::cout << "df2:"<< std::bitset<64>(*(int64_t *)&df2) << std::endl;
  std::cout << "dz2:"<< std::bitset<64>(*(int64_t *)&dz2) << std::endl;
  data = std::bitset<64>(*(unsigned long*)&dz2);
  int64_t dt1 = data.to_ullong();
  cout << dt1 << endl;

  std::cout << "lf1:"<< std::bitset<64>(lf1) << std::endl;
  std::cout << "uif:"<< std::bitset<64>(*(int64_t *)&uif) << std::endl;
  std::cout << "lz1:"<< std::bitset<64>(*(int64_t *)&lz1) << std::endl;
  std::cout << "uiz:"<< std::bitset<64>(*(int64_t *)&uiz) << std::endl;
  std::cout << "lf2:"<< std::bitset<64>(lf2) << std::endl;
  std::cout << "lz2:"<< std::bitset<64>(*(int64_t *)&lz2) << std::endl;

  std::cout << "lcf:"<< std::bitset<64>(*(int64_t *)&lcf) << std::endl;
  std::cout << "lcz:"<< std::bitset<64>(*(int64_t *)&lcz) << std::endl;

  bitf1 = std::bitset<64>(*(unsigned long*)&lf1) ;
  data = bitf1^(std::bitset<64>(*(unsigned long*)&lcf));
  int64_t dt = data.to_ullong();
  std::cout << "result is: " << dt << std::endl;

  cout <<"leadingZeros:"<< leadingZeros << endl;
  cout <<"Zeros:"<< Zeros << endl;
  std::bitset<64> haha = std::bitset<64>(*(int64_t*)&lcf);
  for(int i = Zeros-1; i< 64-leadingZeros ; ++i) {
    cout << haha[i];
  }

  /*
  int const yy = sizeof(double)*8*1000000 ;
  std::bitset<yy> data1 ;
  int ii = yy;
  while(--ii) {
    std::cout << data1[ii];
  }
  */



  //std::cout << "ll1:"<< std::bitset<64>(ll) << std::endl;
  //std::cout << "llz:"<< std::bitset<64>(llz) << std::endl;
  //std::cout << "ll2:"<< std::bitset<64>(ll2) << std::endl;
  //std::cout << "llx:"<< std::bitset<64>(llx) << std::endl;

  double ex = 0.999;
  cout << endl;
  int ex2 = ex * 1000 ;
  int ex1 = static_cast<int>(ex);
  cout << "ex1:"<<  ex1 << endl;
  cout << "ex2:"<<  ex2 << endl;
}
