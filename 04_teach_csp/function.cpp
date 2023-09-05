#include <iostream>

using namespace std;


void printvec(int a[]){
	for (int i = 0; i <= 4; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
	return;
}

// 计算2*x+3
// x = c
int fn(int c) {
	int y = c+3;
	return y;
}

//定义一个函数，计算一个小数数的平方
//1.这个函数有没有返回值
float pingfang(float x) {
	float y;
	y = x * x;
	return y;
}


int main() {
	int c[] = {1,2,3,4,5,6};
	printvec(c);
	int b[] = {4,3,5,6,7,5};
	printvec(b);
	float a = 11.1;
	float f = pingfang(a);//pingfang这个函数算出来的结果呀
	cout << "f:" << f << endl;
	int d = 10;
	int g = fn(d);
	cout << "g:" << g << endl;
	return 0;
}
