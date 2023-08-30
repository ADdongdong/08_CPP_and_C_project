#include <iostream>

using namespace std;

int main(){
	int a[3] = {1, 2, 3};
	//现在想在末尾添加一个新元素4
	int b[4];
	b[3] = 4;
	for (int i = 0; i < 3; i++) {
		b[i] = a[i];
	}
	for (int i = 0; i < 4; i++) {
		cout << b[i] << " ";
	}
	cout << endl;
	return 0;
}
