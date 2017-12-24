#include <iostream>

template <void C(int a, bool error)>
static void connect_cb(int b, bool status) {
    C(b, status < 0);
}

void abc(int a,bool b){
	if(b){
		std::cout << a << std::endl;
	}
}

int main(){
    connect_cb<abc>(25,1);
    return 0; 
}
