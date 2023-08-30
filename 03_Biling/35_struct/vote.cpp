#include <iostream>
#include <cstring>
#include <string>

using namespace std;

struct ans{
	string name;
	int num;
};

int main() {
	//将这三个学生的信息定义出来
	ans stu[3];
	stu[0].name = "xiaoli", stu[0].num = 0;
	stu[1].name = "xiaozhang", stu[1].num = 0;
	stu[2].name = "xiaowang", stu[2].num = 0;
	//定义voteName准备模拟投票
	string voteName;
	for (int i = 1; i <= 7; i++) {
		cin >> voteName;
		for (int j = 0; j < 3; j++) {
			if(stu[j].name == voteName)
				stu[j].num++;
		}
	}
	for (int i = 0; i < 3; i++) {
		cout << stu[i].name << " " << stu[i].num << endl;
	}
	return 0;
}
