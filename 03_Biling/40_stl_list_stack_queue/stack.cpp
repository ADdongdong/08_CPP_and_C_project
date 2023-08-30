rinclude <iostream>
#include <stack>

using namespace std;

int main(){
	stack<char> st;//定义一个栈数据类型
	bool judge = true;//定义bool类型的变量，保存这个表达式是否匹配成功
	char ch;//待输入的字符
	
	do{
		ch = getchar();
		if (ch == '(') st.push(ch);
		else if(ch == ')') {
			if (!st.empty()) st.pop();
			else {
				judge = false;
				break;
			}
		}
	}while(ch != '@');

	if (!st.empty()) judge = false;
	if (judge) cout << "yes" <<endl;
	else cout << "NO"<<endl;
	return 0;
}
