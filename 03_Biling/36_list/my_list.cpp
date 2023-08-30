#include <iostream>

using namespace std;

struct mylist{
	int val;
	mylist * next = NULL;
};

int main() {	
	mylist *node = new mylist;
	node->val = 1;
	mylist *node2 = new mylist;
	node->next  = node2;
	node2->val = 2;
	mylist *node3 = new mylist;
	node3->val = 3;
	node2->next = node3;
	
	//开始遍历这个链表
	//先定义一个指针指向链表的第一个元素
	mylist *i = node;
	while(i!jNULL){
		cout << i->val << " ";
		i = i->next;
	}
	cout << endl;
	return 0;
}
