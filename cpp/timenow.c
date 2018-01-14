#include <stdio.h>
#include <time.h>
 
int main(void)
{
    time_t now;
    //time_t kkk = 1514530652000000000;
    time_t kkk = 1514530651500000000;
    //time_t kkk = 1.514530652e+18;
    kkk = 1.514529912e+18;
    kkk = 1.514529915e+18;
    kkk = 1.514529915e+18;
	kkk = 1452841140000000000;
    kkk = 1463146500000000000;
    
    now = kkk/1000000000;

    struct tm *tm_now;
 
    //time(&now);
    tm_now = localtime(&now);
 
    printf("now datetime: %4d-%02d-%02d %02d:%02d:%02d\n", tm_now->tm_year+1900, tm_now->tm_mon+1, tm_now->tm_mday, tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);
 
    return(0);
}
