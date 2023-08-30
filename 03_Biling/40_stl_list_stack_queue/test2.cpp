#include <iostream>
#include <stack>

using namespace std;

int main(){
	stack<char> s;
	s.push('a');
	s.push('b');
	s.push('c');
	s.push('d');

	while( !s.empty()){
		cout << s.top() << " ";
		s.pop();//删除栈顶元素
	}

	cout << endl;
	return 0;
}
