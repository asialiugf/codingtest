#include <iostream>
#include <string.h>
using namespace std;

int main()
{
  char str1[9] ;
  char str2[9] ;
  //char str3[] = "00:00:00";
  char str3[] = "00000000";
  memset(str2,'\0',9);
  if(memcmp(str3,str2,8)>0) {
    std::cout << " str3 > str2 !!" << std::endl;
    }else if(memcmp(str3,str2,8)<0) {
      std::cout << " str3 < str2 !!" << std::endl;
    } else {
      std::cout << " str3 = str2 !!" << std::endl;
    }

    return 0;
  }
