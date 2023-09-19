#include <stdio.h>

int main() {
	//1. 数组名是什么东西
	// 一般情况下，我们就认为，数组名就是指向数组第一数组指针常量
	// 但是，有两个特殊情况
	// 1.对数组名sizof(数组名)
	int a[] = {1, 2, 3};
	printf("a[1]:%d\n", a[1]);
	printf("*(a + 1):%d\n", *(a +1));
	printf("1[a]:%d\n", 1[a]);
	int *pa = a; // 定义指向数组的指针，是pa
	// 我现在想知道的是，指向数组的指针，能不能用下标运算符呢？
	// 首先，array[index] 和 *(array + index) 这两个东西是等价的
	// 这里的array可以是数组名，即指针常量，也可以是一个普通指针
	// index就是下标，说这个指针要往前移动几个单位
	// 这里的单位指的是这个指针的类型，比如,int*就往前移动index*4
	printf("pa[1]:%d\n", pa[1]);
	printf("*(pa + 1):%d\n", *(pa+1));
	printf("1[pa]:%d\n", 1[pa]);
	

	//这里说一下数组指针
	// 网上是这么定义的
	int (*pb)[3] = NULL;
	pb = a;
	printf("pb[0]:%d\n", (*pb)[0]);
	printf("sizeof(pb):%ld\n", sizeof(pb));

	return 0;
}
