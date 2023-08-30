#include <iostream>
#include <cstring>

using namespace std;

struct myqueue{
	int ele[105];
	int front, back;
	int size;
	//队列初始化
	void init(){
		memset(ele, 0, sizeof(ele));//队列值初始化为0
		size = 0;
		front = 0;
		back = 0;
	}

	//入队操作
	void push(int val){
		ele[back++] = val;
		size ++;
	}

	//出队操作
	int pop(){
		int val = ele[front];
		front++;
		size--;
	}

	//获得队首元素
	int getfront(){
		return ele[front];
	}
	
	//获得队尾元素
	int getback(){
		return ele[back-1];
	}
	//判断是否队列为空
	bool empty(){
		return front == back;
	}

	//返回队列元素个数
	int getsize(){
		return size;
	}
};

int main(){

}
