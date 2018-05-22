#include <iostream>
using namespace std;
class a{
  int m;
  public:
  int Set(int x) { m = x;return 0;} 
  int Get() { return m;}
};

int test( a & u) {
 u.Set(9);
 std::cout << u.Get() << std::endl;
}

int test1(int &a) {
  std::cout <<"test1 addr: " << &a << std::endl;
  a = 5;
}

int test2(int *a) {
  std::cout <<"test1 addr: " << a << std::endl;
  *a = 101;
}

void g(string &a,const string &b)
{
    cout<<"a address :"<<&a<<endl;
    cout<<"b address :"<<&b<<endl;
}

void f(string a,const string b)
{
    cout<<"a address :"<<&a<<endl;
    cout<<"b address :"<<&b<<endl;
}



int main() {

  a * yy = new a() ;
  test(*yy); 
  int bb;
  test1(bb);
  std::cout << bb << std::endl;
  test2(&bb);
  std::cout << bb << std::endl;

  std::string r = "haha";
  const char *b="***";
  std::cout <<"r: " << &r << std::endl;
  std::cout <<"b: " << b << std::endl;
  std::cout <<"*b: " << *b << std::endl;
  std::cout <<"&b: " << &b << std::endl;

  const char c[]="***";
  std::cout <<"c: " << c << std::endl;
  std::cout <<"*c: " << *c << std::endl;
  std::cout <<"&c: " << &c << std::endl;

  g(r,r);
  f(r,r);

  return 0;

}
