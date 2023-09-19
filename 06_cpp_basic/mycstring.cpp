#include <iostream>
#include <cstring>

using namespace std;

// 定义计算string长度的strlen函数
size_t mystrlen(char const* mystr){
	int length;
	for (length = 0; *mystr++ != '\0';)
		length++;
	return length;
}

int main() {
	// 定义一个字符串数组，每个元素都是一个指向字符串首元素的指针
	// 同时，这是一个字符串常量
	char mystr1[] = {'h', 'e', 'l', 'l','o', '\0'};
	char mystr2[] = {'h', 'e', 'l', 'l','o', '\0'};
	char mystr3[] = {'h', 'e', 'l', 'l','o', '\0'};
	char mystr4[] = {'h', 'e', 'l', 'l','o', '\0'};
	const char *mystrs[] = {mystr1, mystr2, mystr3,mystr4};
	char const* keyword[] = {
		"do",
		"for",
		"if",
		"register",
		"return",
		"switch",
		"while"
	};
	for(int i = 0; i < 7; i++) {
		cout << mystrlen(keyword[i]) << " " << endl;
	}
	cout << endl;
	// 7 * 8 = 56
	cout << "sizeof(keyword)" << sizeof(keyword) <<endl;

	
	return 0;
}
