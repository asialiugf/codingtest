#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template<class T1>
class SlotBase
{
public:
  virtual void Exec(T1 param1) = 0;
};

template<class T, class T1>
class SlotImpl : public SlotBase<T1>
{
public:
  SlotImpl(T* pObj, void (T::*func)(T1))
  {
    m_pObj = pObj;
    m_Func = func;
  }

  void Exec(T1 param1)
  {
    (m_pObj->*m_Func)(param1);
  }

private:
  T* m_pObj;
  void (T::*m_Func)(T1);
};

template<class T1>
class Slot
{
public:
  template<class T>
  Slot(T* pObj, void (T::*func)(T1))
  {
    m_pSlotBase = new SlotImpl<T,T1>(pObj, func);
  }

  ~Slot()
  {
    delete m_pSlotBase;
  }

  void Exec(T1 param1)
  {
    m_pSlotBase->Exec(param1);
  }

private:
  SlotBase<T1>* m_pSlotBase;
};

template<class T1>
class Signal
{
public:
  template<class T>
  void Bind(T* pObj, void (T::*func)(T1))
  {
    m_pSlotSet.push_back(new Slot<T1>(pObj,func));
  }

  ~Signal()
  {
    for(int i=0; i<(int)m_pSlotSet.size(); i++) {
      delete m_pSlotSet[i];
    }
  }

  void operator()(T1 param1)
  {
    for(int i=0; i<(int)m_pSlotSet.size(); i++) {
      m_pSlotSet[i]->Exec(param1);
    }
  }

private:
  vector< Slot<T1>* > m_pSlotSet;
};

#define Connect( sender, signal, receiver, method) ( (sender)->signal.Bind(receiver, method) )

class A
{
public:
  void FuncOfA(int param)
  {
    printf("A::FuncOfA(%d)\n", param);
  }
};

class B
{
public:
  void FuncOfB(int param)
  {
    printf("B::FuncOfB(%d)\n", param);
  }
};

class C
{
public:
  C()
  {
    m_Value = 0;
  }
  void SetValue(int value)
  {
    if(m_Value != value) {
      m_Value = value;
      ValueChanged(m_Value);
    }
  }
  void MakeIt(int x)
  {
    MI[x]("test!!!") ;
  }

public:
  Signal<int> ValueChanged;
  Signal<std::string> MI[100];

private:
  int m_Value;
};

class X
{
  int mm ;
public:
  X(C *pC,int k)
  {
    mm = k*k ;
    //Connect(pC, ValueChanged, this, &X::Xupdate);
    //Connect(pC, MI[1], this, &X::Xupdate);  // Connect是define，所以 MI可以直接用。
    pC->MI[1].Bind(this, &X::Xupdate);
    pC->MI[9].Bind(this, &X::Xupdate);
    //Connect(pC, MI[9], this, &X::Xupdate);
  }
  //void Xupdate(int x)
  void Xupdate(std::string kk)
  {
    printf("ixxxxxxxxxx %s\n",kk.c_str());
    kkk(3,5,mm);
  }
  void kkk(int a, int b, int c)
  {
    printf("result:%d\n",a+b+c);
  }
};

int main()
{
  C* pC = new C;
  A* pA = new A;
  B* pB = new B;
  B* pB1 = new B;
  X* pX = new X(pC,5);
  X* pX1 = new X(pC,10);

  Connect(pC, ValueChanged, pA, &A::FuncOfA);
  Connect(pC, ValueChanged, pB, &B::FuncOfB);
  Connect(pC, ValueChanged, pB1, &B::FuncOfB);
  //Connect(pC, ValueChanged, pX, &X::Xupdate);
  //Connect(pC, ValueChanged, pX1, &X::Xupdate);

  //Connect(pC, MI[1], pX, &X::Xupdate);
  //Connect(pC, MI[9], pX1, &X::Xupdate);

  pC->SetValue(10);
  pC->SetValue(5);
  pC->SetValue(5);
  pC->SetValue(100);

  pC->MakeIt(1);
  pC->MakeIt(9);

  delete pC;
  delete pB;
  delete pA;

  scanf("%*s");
}
