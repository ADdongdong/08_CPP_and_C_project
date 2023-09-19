#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

int main(){
	int ia[6] = {27, 210, 12, 47, 109, 83};
	// 分配器，是容器的默认会传入的东西，一般可以不写
	// allocator<int> 告诉我们，每次分配的内存是int
	vector<int, allocator<int>> vi(ia, ia+6);
	// count_if 算法，帮我们计算在给定条件下，符合条件的元素有几个
	// 参数：告诉我们范围，这里范围传入的迭代器
	cout << count_if(vi.begin(), vi.end(),
			not1(bind2nd(less<int>(), 40))) <<endl; //找出小于40的元素有几个
											 //less 是仿函数
											 //bind2nd 是适配器
											 //这里的作用是绑定/固定第二参数
											 //本来是a 和b 比大小，a,b都是不知道的
											 //现在使用bind2nd将第二个参数固定为40
											 //就是说，所有的数字都和40比大小
											 //not1 表示否定，从<40变成>= 40
	return 0;
}

