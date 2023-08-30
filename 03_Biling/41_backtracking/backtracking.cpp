#include <iostream>
#include <cmath>

using namespace std;

int total = 0;//定义整数total,保存一共有多少种情况
int a[11] = {0};//定义a[11]我们使用下标为1-10的元素
bool b[11] = {0};//定义b[11]标记这个数字是否被使用过，
				 //比如3使用过了，那下标为3的元素就为True
				 //如果3没有被使用过，就将下标3对应的元素标记为false

//定义判断x和y的和否为素数的函数
bool pd(int x, int y){
	int z = x + y;
	for (int i = 2; i <= sqrt(z); i++){
		//如果这个范围内 ，有数字可以整除z
		//说明z不是素数
		if (z % i == 0){
			return 0;
		}
	}
	return 1;
}

//打印所可能得素数环
void print(){
	total ++;
	cout << "<" << total << ">";
	for (int i = 1; i <= 10; i++){
		cout << a[i] << " ";
	}
	cout << endl;
}

//现在来确定下标为t这个位置的数字应该放几
//回溯算法本身 
void search(int t){
	for (int i = 1; i <= 10;i++){
		//如果a[t-1] 和i这两个数字之和为素数
		//并且，b[i]这个数字还没有被使用
		if ((t==1 || pd(a[t-1], i)) && (b[i] == 0)){
			a[t] = i;
			b[i] = 1;
			//当将第10个数字放入进去后
			//要判断这是不是一个素数环，
			//就要判断第10个元素和第1个元素之和是否为素数
			if (t == 10){
				if (pd(a[10], a[1])){
					print();
				}
			}else{
				search(t+1);
			}
			b[i] = 0;
		}
	}
}


int main(){
	search(1);
	cout << total << endl;

	return 0;
}
