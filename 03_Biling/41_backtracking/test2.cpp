#include <iostream>

using namespace std;

int total = 0;
int n,r,a[10001] = {0};

bool b[10001] = {0};


void print(){
	total++;
	for(int i = 1; i <= r; i++){
		cout << a[i] << " ";
	}
	cout << endl;
}

//定义递归函数
void search(int t){
	for (int i = 1; i <= n; i++){
		//如果b[i],也就是i这个数字没有被选择过
		if (b[i] == 0){
			a[t] = i;
			b[i] = 1;
			//如果t就是最后一个数字了
			if(t==r){
				print();
			}else{
				search(t+1);
			}
			//在这个位置进行回溯
			b[i] = 0;
		}
	}
}

int main(){
	cin >> n >> r;//输入n和r
	search(1);
	cout << total;
	return 0;
}
