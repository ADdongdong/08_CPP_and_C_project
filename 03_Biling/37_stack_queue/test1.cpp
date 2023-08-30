#include <iostream>
#include <cstring>

using namespace std;

//定义栈结构体
struct mystack{
	int ele[10];
	int size;
	int top;

	//初始化，让数组值都为0,size为0，top为-1
	void init(){
		memset(ele, 0, sizeof(ele));
		size = 0;
		top = -1;//栈顶指针先指向-1,方便加入元素
	}

	//栈顶/压加入元素
	void push(int val){
		//++top和top++
		ele[++top] = val;
		size++;
	}

	//出栈：删除栈顶元素
	int pop(){
		//用val保存栈顶元素
		int val = ele[top];
		top--;//栈顶指针往下移动
		size--;
		return val;
	}

	//取栈顶元素
	int gettop(){
		return ele[top];
	}

	//判断栈是否为空
	bool isempty(){
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
	for (int i = 0; i < 10; i++){
		cout << s1.ele[i] << " ";
	}
	cout << endl;
	//打印这个时候栈内的元素个数
	cout << "size:" << s1.size << endl;
	//打印top指针指向哪个元素
	cout <<"top" << s1.top<< endl;
	//加入两个元素1,2
	s1.push(1);
	s1.push(2);//1,2 
	cout << s1.gettop() << endl;//2
	s1.pop();//删除栈顶元素
	cout << s1.gettop() << endl;//1
	cout << "is empty?"<< s1.isempty()<<endl;
	s1.pop();//还有元素吗？
	cout << "is empty?" << s1.isempty() <<endl;

	return 0;
}
