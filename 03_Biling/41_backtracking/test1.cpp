#include <iostream>
#include <cmath>


using namespace std;

//定义三个全局变量
//total 保存有多少种素数环
int total = 0;
//素数环数组
int a[11] = {0};//我们使用下标1->10,下标1的元素不使用
//定义标记，标记这个数字有没有使用过
//比如，3使用过了，那么就把b数组中下标为3的元素标记为1
bool b[11] = {0};

//定义判断是不是素数的函数
bool pd(int x, int y){
	int z = x + y;
	//素数只能被1和自己整除
	//for (int i = 2; i <= sqrt(z); i++)
	for (int i = 2; i <= z-1; i++){
		//如果能被整除
		if (z % i == 0){
			//return 两种能力
			//1.返回一个东西
			//2.结束函数的运行
			return 0;
		}
	}
	return 1;	
}

//输出函数
void print(){
	total++;
	cout << "<" << total << ">";
	for (int i = 1; i <= 10; i++){
		cout << a[i] <<" ";
	}
	cout << endl;
}

//回溯算法
//参数t,表示咱们现在要在哪个位置放入数字了
void search(int t){
	for (int i = 1; i <= 10; i++){
		//1，2，
		if ((b[i] == 0) && (t == 1 || pd(a[t-1], i))){
			a[t] = i;
			b[i] = 1;//i这个数字，已经被使用啦
			if (t == 10){
				//素数环10个数字填写满了
				if(pd(a[10], a[1])){
					print();//total++
				}
			} else {
				search(t+1);
			}
			b[i] = 0;
		}
	}
}

int main(){
	search(1);
	cout << "total:" << total << endl;
	return 0;
}
