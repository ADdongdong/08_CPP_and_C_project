#include <iostream>
#include <string>
#include <stack>


using namespace std;

bool areParenthesesBalanced(const string& expression){
	stack<char> st;
	for (int i = 0; i < expression.size(); i++){
		if (expression[i] == '('){
			st.push(expression[i]);
		}else if (expression[i] == ')' ){
			if (st.empty()){
				return false;//如果此时栈为空，则返回false
			}
			//否则，就说明，括号匹配成功了，将栈顶元素弹出
			st.pop();
		}
	}
	return st.empty();//返回栈是否为空，若栈空，则说名整个字符串匹配成功,注意，这里栈空，st.empty会返回True
}


int main(){
	string expression;

	cout << "请输入你的表达式" << endl;
	//getline(cin, expression);
	cin >> expression;
	if (areParenthesesBalanced(expression)){
		cout << "小括号匹配成功" << endl;
	} else {
		cout << " 小括号匹配失败" << endl;
	}
	return 0;
}
