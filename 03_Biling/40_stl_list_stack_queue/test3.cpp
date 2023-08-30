#include <iostream>
#include <stack>
#include <string>
#include <cstring>

using namespace std;

bool pipei(string s){
	stack<char> st;	
	//   3*(3+5)
	//st:
	//
	for(int i = 0; i< s.size(); i++){
		if(s[i] == '('){
			st.push(s[i]);
		}else if(s[i] == ')'){
			if (st.empty()){
				return false;
			}else{
				st.pop();
			}
		}
	}
	return st.empty();
	//如果栈是空的，返回True
	//如果栈不是空的，就返回False
}

int main(){
	string s;
	cout << "请输入一个表达式：" << endl;
	cin >> s;
	if (pipei(s)){
		cout << "小括号匹配成功" << endl;
	}else{
		cout << "小括号匹配失败" << endl;
	}
	return 0;

}
