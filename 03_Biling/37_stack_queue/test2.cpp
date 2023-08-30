#include <iostream>
#include <cstring>

using namespace std;

struct myqueue{
	int ele[10];
	int front, back;//front 队头指针，指向队头元素
					 //back 队尾指针，指向对尾元素的下一个位置
	int size;

	//队列初始化
	void init()	{
		memset(ele, 0, sizeof(ele));
		size = 0;
		front = 0;//top -1
		back = 0;
	}

	//入队操作
	void push(int val){
		//队尾，队尾巴/吧
		ele[back++] = val;
		size++;
	}

	//出队操作
	int pop(){
		int val = ele[front];
		front++;
		size--;
		return val;
	}

	//获取队头元素
	int getfront(){
		return ele[front];
	}

	//获取队尾元素
	int getback(){
		//back:最后一个元素的后一个位置
		//back - 1
		return ele[back-1];
	}

	//判断是否队空
	bool isempty(){
		return front == back;
	}

	//往队列里面添的个数
	int getsize(){
		return size;
	}
};

int main(){
	//创建一个队列
	myqueue q1;	
	//往队列里面添加3个元素
	q1.push(1);
	q1.push(2);
	q1.push(3);
	//输出这三个，看看输出顺序
	cout << q1.pop() << endl;
	cout << q1.pop() << endl;
	cout << q1.pop() << endl;
	//判断是不是队空
	cout << "is empty?" << q1.isempty() << endl;
	return 0;

}
