#include <iostream>

using namespace std;

void greedy(int n, int s[], int f[], bool b[]){
	//先把第一个会议放进去
	b[1] = true;
	int j = 1;

	//开始从2号会议一次检查，看看相容不相容，
	//也就是，看看后面的会议时间冲突吗
	for(int i = 2; i <= n; i++){
		if (s[i] >= f[j]){
			b[i] = true;
			j = i;//当前会议，变成了i号会议了，
				  //下一次判断会议能不能放进去，就要和这个会议的
				  //结束时间相比较了
		} else{
			b[i] = false;
		}
	}
}

int main(){
	int s[] = {0,1,3,0,5,3,5,6,8,8,2,12};
	int f[] = {0,4,5,6,7,8,9,10,11,12,13,14};
	bool b[20];
	//计算一下，我们一共有多少个会议
	int n = (sizeof(s)/sizeof(s[0])) - 1;
	greedy(n,s,f,b);
	
	//把加入到会议室的会议打印一下吧
	for (int i = 1; i <= n; i++) {
		if (b[i] != 0) {
			cout << "活动" << i << "时间安排是：" << s[i] << "点，开始"
			   	 << f[i] << "点结束"<< endl;
		}
	}

	return 0;
}
