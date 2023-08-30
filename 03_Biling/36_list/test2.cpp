#include <iostream>

using namespace std;

int main(){
	int a[3] = {1, 2,3};
	//目标是，给这个数组后面添加一个元素4
	int b[4];
	b[3] = 4;
	for (int i= 0; i < 3; i++){
		b[i] = a[i];
	}

	for (int i = 0; i < 4; i++){
		cout << b[i] <<" ";
	}//1, 2, 3, 4
	cout << endl;
	return 0;
}
