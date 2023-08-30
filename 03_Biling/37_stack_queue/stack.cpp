#include <iostream>
#include <cstring>

using namespace std;

//定义一个栈
struct mystack{
	int ele[105];//用来存储栈内存元素的数组
	int top;//栈顶元素的下标
	int size;//栈内有多少元素
	//定义函数
	//初始化栈
	void init(){
		memset(ele, 0, sizeof(ele));//栈内元素初值设为0
		size = 0;
		top = 0;
	}
	//入栈
	void push(int value){
		ele[++top] = value;
		size++;
	}
	
	//出栈
	int pop(){
		int val = ele[top];
		top--;
		size--;
		return val;
	}
	//取栈顶元素
	int gettop(){
		return ele[top];
	}

	//判断栈是否为空
	bool empyt(){
		return size == 0;
	}
	
	//取栈的大小
	int getsize(){
		return size;
	}
};


int main(){
	mystack s1;
	s1.init();
	cout << s1.top << endl;
	cout << s1.size << endl;
	for (int i = 0; i < 10; i++ ){
		cout << s1.ele[i] << endl;
	}
	return 0;
}
