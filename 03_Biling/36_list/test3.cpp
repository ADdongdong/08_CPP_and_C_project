#include <iostream>

using namespace std;

struct mylist{
	int val;
	mylist *next = NULL;
};

void mydelete(int node_val, mylist* l){
	mylist *temp = l;
	while (temp->next->val != node_val && temp != NULL){
		temp = temp->next;
	}
	mylist *p = temp->next;
	temp->next = temp->next->next;
	delete p;
}

void myinsert(int sval, int node_val, mylist* l){
	mylist *temp = l;
	while (temp->val != node_val && temp != NULL){
		temp = temp->next;
	}
	mylist *newnode = new mylist;
	newnode->val = sval;
	newnode->next = temp->next;
	temp->next = newnode;
}

int main(){
	mylist * node1 = new mylist;
	node1->val = 1;
	mylist * node2 = new mylist;
	node2->val = 2;
	node1->next = node2;
	mylist * node3 = new mylist;
	node3->val = 3;
	node2->next = node3;
	mylist * node4 = new mylist;
	node4->val = 4;
	node3->next = node4;
	myinsert(20, 3, node1);
	myinsert(100, 4, node1);
	//1,2,3,20,4,100
	//删除值为2的结点
	mydelete(2, node1);
	//1,3,20,4,100
	mylist * temp = node1;
	while (temp != NULL){
		cout << temp << " ";
		cout << temp->val << endl;
		temp = temp->next;
	}
	
	return 0;
}
