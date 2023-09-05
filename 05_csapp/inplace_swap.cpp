#include <iostream>
#include "show_bytes.h"

using namespace std;

//定义交换两个int值的函数
void inplace_swap(int *x, int *y) {
	*y = *x ^ *y;
	cout << "*y:";
	show_int(*y);
	cout << "*x:";
	show_int(*x);
	*x = *x ^ *y;
	cout << "*y:";
	show_int(*y);
	cout << "*x:";
	show_int(*x);
	*y = *x ^ *y;
	cout << "*y:";
	show_int(*y);
	cout << "*x:";
	show_int(*x);
}

int main() {
	int a = 10;
	int b = 20;
	inplace_swap(&a, &b);
	cout << "a:" << a << endl;
	cout << "b:" << b << endl;
	return 0;
}
