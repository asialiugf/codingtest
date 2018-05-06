#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <string>
using namespace std ;

typedef void (*FUNCPTR)(void) ;
class A
{
  //typedef void (A :: *FUNCPTR)(void) ;
public:
  A(string _n): name(_n) {} ;
  ~A() {} ;
  void registerCallBack(A *inst, FUNCPTR pFun) ;
  void removeCallBack(A *inst, FUNCPTR pFun) ;
  void trigger() ;

  inline void funA()
  {
    cout << string(name).append("--A") << endl;
  } ;
  inline void funB()
  {
    cout << string(name).append("--B") << endl;
  } ;
  inline void funC()
  {
    cout << string(name).append("--C") << endl;
  } ;
private:
  //判断一个回调函数是否已经被注册
  size_t isIn(const pair<A*, FUNCPTR> &p) ;
  string name ;
  vector< pair<A*, FUNCPTR> > callBackList ;
};

size_t A :: isIn(const pair<A *, FUNCPTR> &p)
{
  size_t index = -1 ;
  for(size_t i = 0; i < callBackList.size(); ++ i)
    if(p == callBackList[i]) {
      index = i ;
      break ;
    }
  return  index ;
}

void A :: registerCallBack(A *inst, FUNCPTR pFun)
{
  pair<A*, FUNCPTR> addPair = make_pair(inst, pFun) ;
  if(isIn(addPair) == -1)
    callBackList.push_back(addPair) ;
}

void A :: removeCallBack(A *inst, FUNCPTR pFun)
{
  pair<A*, FUNCPTR> rmPair = make_pair(inst, pFun) ;
  size_t index = isIn(rmPair) ;
  if(index != -1) {
    swap(callBackList[index], callBackList.back()) ;
    callBackList.pop_back() ;
  }
}

void A:: trigger()
{

  for(size_t i = 0; i < callBackList.size(); ++ i) {
    A *pInst = callBackList[i].first ;
    FUNCPTR pFun = callBackList[i].second ;
    (pInst->*pFun)() ;
  }
}

class B
{
public:
  B(string _n): name(_n) {} ;
  ~B() {} ;

  inline void funA()
  {
    cout << string(name).append("--A") << endl;
  } ;
  inline void funB()
  {
    cout << string(name).append("--B") << endl;
  } ;
  inline void funC()
  {
    cout << string(name).append("--C") << endl;
  } ;
private:
  string name ;
};

int main(int argc, char **argv)
{
  A a("cat") ;
  A b("dog") ;
  B b1("aaaaaaaaaaaaaaaaa") ;
  B b2("bbbbbbbbbbbbbbbbb") ;

  cout << "Add a.funA, a.funB, a.funC" << endl ;
  a.registerCallBack(&a, &A::funA) ;
  a.registerCallBack(&a, &A::funB) ;
  a.registerCallBack(&a, &A::funC) ;

  a.registerCallBack(&a, &B::funA) ;
  a.registerCallBack(&a, &B::funB) ;

  a.trigger() ;

  cout << "Remove a.funA" << endl ;
  a.removeCallBack(&a, &A::funA) ;
  a.trigger() ;

  cout << "Add b.funA, b.funB" << endl;
  a.registerCallBack(&b, &A::funA) ;
  a.registerCallBack(&b, &A::funB) ;
  a.trigger() ;

  cout << "Remove a.funB, a.funC" << endl ;
  a.removeCallBack(&a, &A::funB) ;
  a.removeCallBack(&a, &A::funC) ;
  a.trigger() ;
  return  0 ;
}
