#include <iostream>
#include <string>

using namespace std;

//定义小学生结构体
struct student{
	string name; //学生的名字
	int age;//学生的年龄
};

int main() {
	student s[3];
	s[0].name = "xiaoli";
	s[0].age = 10;
	s[1].name = "xiaozhang";
	s[1].age = 10;
	s[2].name = "xiaowang";
	s[2].age = 10;
	//输出三个学生的姓名
	for (int i = 0; i < 3; i++) {
		cout << s[i].name << " ";
	}
	cout << endl;

	return 0;
}
