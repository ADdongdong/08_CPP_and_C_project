#include <iostream>

using namespace std;

#define NUM 50 //定义宏NUM为50
			   
void GreedySelector(int n, int s[], int f[], bool b[]){
	b[1] = true;//默认第一个活动是被安排了的
	int j = 1; //记录第一次加入b的活动
	
	//依次检查活动i是否和当前活动相容，相容的意思就是时间不冲突
	//也就是:比如活动1是4点结束的，下一个活动必须从4点以后开始才行
	for (int i = 2; i <= n; i++){
		//f[j] 是f[1]是第一个活动结束的时间
		//s[i] 是s[2]是第二个活动开始的时间
		//只要第二个活动开始的时间在第一个活动结束的时间后面就可以了
		if (s[i] >= f[j]){
			//说明i活动没有问题,将i活动加入被安排的活动列表中
			b[i] = true;
			//并且，此时我们要找j的下一个活动是什么
			j = i;
		} else{
			//如果，如果i活动的开始事件，小于j活动的结束时间
			//那么，i活动就不能加入到活动列表b中
			b[i] = false;
		}
	}
}

int main(){
	int s[] = {0,1,3,0,5,3,5,6,8,8,2,12}; //存储每个活动开始的事件
	int f[] = {0,4,5,6,7,8,9,10,11,12,13,14}; //存储每个活动结束的事件
	bool b[NUM]; //存储活动开始的时间
	int n = (sizeof(s)/sizeof(s[0]))-1;//sizeof以字节8bit为单位返回一个变量的长度
	
	GreedySelector(n,s,f,b);

	for (int i = 1; i <= n; i++){
	//输出被安排的活动编号和这个活动开始和结束的时间	
		if(b[i] != 0) {
			cout << "活动" << i << "时间安排：点" << s[i] << "开始," << f[i] << "点结束" << endl;
		}
	}
	return 0;
}
