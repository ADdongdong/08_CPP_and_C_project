#include <iostream>

using namespace std;

int main(){
	int a[3];
	//看看，这个3个元素，是不是真的在内存中是挨着存的
	for (int i = 0; i < 3; i++){
		cout << &a[i] <<endl;
	}
	
	return 0;
}
