#include <stdio.h>
#include <string.h>

void test1() {
	int a[] = {1, 2, 3, 4};
	int c[] = {2, 3, 4, 5};
	int b = 5;
	//这里我们试图改变a的值，让a去保存别的地址
	//a = c; 编译失败，报错
	//a = &b; 编译失败，报错
	printf("a:%p\n", a);
	printf("a[0]:%d\n", a[0]);
	printf("&a:%p\n", &a);
	printf("sizeof(a):%ld\n", sizeof(a));
	printf("sizeof(&b):%ld\n", sizeof(&b));
}

// 这个test2主要用于验证，数组名，我们可以认为他是一个指针常量
void test2() {
	int a = 1;
	int *const pa = &a;// 这里真的定义一个指针常量
	int b[] = {1, 2, 3, 4, 5}; //这里定义一个数组
	// 我们看看操作哈
	// 关于指针的操作:*, 关于数组的操作:[]
	printf("*pa:%d\n", *pa);
	printf("*b:%d\n", *b);
	
	printf("*(pa + 0):%d\n", *(pa + 0));
	printf("*(b + 0):%d\n", *(b + 0));
	
	printf("pa[0]:%d\n", pa[0]);
	printf("b[0]:%d\n", b[0]);

	//最离谱的来了
	printf("0[pa]:%d\n", 0[pa]);
	printf("0[b]:%d\n", 0[b]);
	
	//正常数组通过下标取别的元素
	printf("b[2]:%d\n", b[2]);
	printf("*(b + 2):%d\n", *(b + 2));
	printf("2[b]:%d\n", 2[b]);

}

void test3() {
	char* strs[] = {
		"hello",
		"world"
	};
	char* (*pstars)[] = strs;
	printf("%ld\n", strlen((*pstars)[0]));
}
int main() {
	test3();
	return 0;
}
