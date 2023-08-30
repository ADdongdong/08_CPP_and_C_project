#include <iostream>

using namespace std;

void greedy(int n, float M, float v[], float w[], float x[]){
	int i;
	for (i = 1; i <= n; i++){
		x[i] = 0;
	}	
	//定义当前背包剩余容量的大小
	float c = M;

	//循环遍历物品
	for (i = 1; i <= n; i++){
		//物品的重量，比背包剩余的重量还大，那就退出循环
		//说明背包已经放满啦
		if (w[i] > c){
			break;
		} else{
		//此时背包还能把第i个物品放进去
			x[i] = 1;
			c -= w[i];//跟新背包剩余的容量
		}
	}

	if (i <= n)	{
		x[i] = c/w[i];
	}
}

int main(){
	float M = 50;//定义背包的重量
	float w[] = {0,10,20,30};
	float v[] = {0,60,100,120};
	float x[20];

	int n = (sizeof(w)/sizeof(w[0])) - 1;

	greedy(n, M ,v ,w, x);
	
	for (int i = 1; i <= n; i++){
		cout <<"物品" << i << "装入的比例:" <<x[i] <<endl;
	}

	return 0;
}
