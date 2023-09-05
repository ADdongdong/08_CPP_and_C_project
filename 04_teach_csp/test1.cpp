#include <iostream>

using namespace std;

//定义冒泡排序函数
void bubble(int a[], int len) {
	for (int i = len -1; i >= 1; i--) {
		for (int j = 0; j < i; j++) {
			if (a[j] > a[j+1]) {
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}


void printVect(int a[], int len){
	for (int i = 0; i < len; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int main(){
	//定义一个数组
	int a[] = {3,4,2,5,8,1,6};
	bubble(a, sizeof(a)/sizeof(a[0]));
	printVect(a, sizeof(a)/sizeof(a[0]));
	printf("helloworld\n");
	return 0;
}
