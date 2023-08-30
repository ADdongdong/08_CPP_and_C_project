#include <iostream>
#include <list>

using namespace std;

int main() {
	//定义一个链表
	list<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	//定义一个链表迭代器
	list<int>::iterator i; 
	//给迭代器赋值，让迭代器指向l1的第一个元素
	i = l1.begin();
	//使用迭代器来遍历list
	for (i; i != l1.end(); i++){
		cout << *i <<endl;
	}
	cout << endl;
	return 0;
}
