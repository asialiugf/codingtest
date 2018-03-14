#include <cstdlib>
#include <iostream>

using namespace std;

struct kk{
  char mm[10];
};

class Test
{
  public:
        static kk *m_kk;
        static int ci;       
  public:  
        static int GetI()
        {
            return ci;    
        }
        static void SetI(int i)
        {
              ci = i;  
        }
};
int Test::ci = 0;
kk * Test::m_kk = new(kk);

int main(int argc, char *argv[])
{
    
	//kk * Test::m_kk = new(kk);
    Test uu ;
    Test::m_kk->mm[0] = 'a'; 
    Test::m_kk->mm[1] = 'a'; 
    Test::m_kk->mm[2] = 'a'; 
    Test::m_kk->mm[3] = 'a'; 
    uu.m_kk->mm[2] = 'b';
    
    Test::m_kk->mm[4] = '\0'; 
    Test::SetI(5);
    cout<<"Test::ci = " << Test::GetI() << "\n";

    //Test uu ;
    cout<< uu.m_kk->mm << endl;
    
    cout << "Press the enter key to continue ...";
    cin.get();
    return EXIT_SUCCESS;
}
