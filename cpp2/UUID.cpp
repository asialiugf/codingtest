#include <stdio.h>
#include <iostream>
#include <uuid/uuid.h>

int main()
{
  uuid_t uu;
  int i;
  uuid_generate(uu);

  for(i=0; i<16; i++) {
    printf("%02X-",uu[i]);
  }
  printf("\n");

  char buf[33];
  uuid_generate(uu);
  snprintf(buf,33,"%02X",uu[0]);
  snprintf(buf,33, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
           uu[0],uu[1],uu[2], uu[3], uu[4], uu[5], uu[6], uu[7],
           uu[8],uu[9],uu[10],uu[11],uu[12],uu[13],uu[14],uu[15]);

  std::cout << buf << std::endl;
  return 0;
}
