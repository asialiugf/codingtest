#include<iostream>
#include<string>
using namespace std;

string CaculateWeekDay(int y,int m,int d);
string get_Month_string(int m);
bool is_valid(int m,int d,int y);

int main()
{
  int month,day,year;
  cout<<"Enter a date in the yyyy: ";
  cin>>year;
  cout<<"Enter a date in  mm: ";
  cin>> month;
  cout<<"Enter a date in  dd: ";
  cin>>day;
  if(is_valid(month,day,year))
    cout<<CaculateWeekDay(year,month,day)<<endl;
  else
    cout<<day<<" "<<month<<" "<<year<<" is an invalid date."<<endl;

  return 0;

}

int CaculateWeekDay(int y,int m, int d)
{
  int week = 0;
  if(m==1) {
    m=13;
    y--;
  }
  if(m==2) {
    m=14;
    y--;
  }
  if((y<1752)||((y==1752)&&(m<9))||((y==1752)&&(m==9)&&(d<3))) //判断是否在1752年9月3日之前
    week =(d+2*m+3*(m+1)/5+y+y/4+5)%7; //1752年9月3日之前的公式
  else
    week =(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7; //1752年9月3日之后的公式
  return week;
}

bool is_valid(int m,int d,int y)
{
  if(m<0||m>12||d<0||d>31||y<0)
    return false;
  return true;
}

string get_Month_string(int m)
{
  switch(m) {
  case 1: {
    return "January";
    break;
  }
  case 2: {
    return "February";
    break;
  }
  case 3: {
    return "March";
    break;
  }
  case 4: {
    return "April";
    break;
  }
  case 5: {
    return "May";
    break;
  }
  case 6: {
    return "June";
    break;
  }
  case 7: {
    return "July";
    break;
  }
  case 8: {
    return "August";
    break;
  }
  case 9: {
    return "September";
    break;
  }
  case 10: {
    return "October";
    break;
  }
  case 11: {
    return "November";
    break;
  }
  case 12: {
    return "Desember";
    break;
  }
  }
}
