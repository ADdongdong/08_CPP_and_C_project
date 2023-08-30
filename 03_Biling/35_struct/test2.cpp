#include <iostream>
#include <cstring>
#include <string>

using namespace std;

//定义学生结构体
struct student{
	string name;
	int num;
};
int main() {
	student stu[3];
	stu[0].name = "xiaoli",stu[0].num = 0;
	stu[1].name = "xiaozhang",stu[1].num = 0;
	stu[2].name = "xiaowang",stu[2].num = 0;
	//开始投票
	string voteName;
	for (int i = 1; i <= 7;i++){
		cin >> voteName;//开始投票
		for (int j = 0; j < 3; j++) {
			if (stu[j].name == voteName ) {
				stu[j].num++;
			}
		}
	}
	for(int i = 0; i< 3;i++){
		cout << stu[i].name << "得了"  << stu[i].num <<"票"<<endl;
	}

	return 0;
}
