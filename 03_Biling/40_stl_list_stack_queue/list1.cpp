#include <iostream>
#include <list>

using namespace std;

int main(){
	list<int> a;
	a.insert(a.end(), 10);
	//将指定的值插入到list中指定节点的后面
	//将20插入到10的后面
	for (list<int>::iterator i = a.begin(); i != a.end(); i++){
		if (*i == 10){
			a.insert(++i, 20);
			break;
		}
	}

	//输出这个list中的所有元素
	for (list<int>::iterator i = a.begin(); i != a.end(); i++){
		cout<< *i <<endl;
	}


	return 0;
}
