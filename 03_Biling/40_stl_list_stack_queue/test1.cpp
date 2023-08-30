rinclude <iostream>
#include <list>

using namespace std;

void printlist(list<int> l){
	for (list<int>::iterator i = l.begin(); i != l.end(); i++){
		cout << *i << " ";
	}
	cout << endl;
}

int main(){
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(10);

	//1,2,3,10
	printlist(l);

	//给指定位置插入一个元素
	for(list<int>::iterator i = l.begin(); i != l.end(); i++){
		if (*i == 10){
			l.insert(++i, 20);
			break;
		}
	}
	printlist(l);//1，2，3，20，10

	return 0;
}
