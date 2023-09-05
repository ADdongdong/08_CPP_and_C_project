#include <stdio.h>

int main(){
	// 1.指向常量的指针
	// 也就是说，这个指针所指向的这个变量是个常量
	// 这个常量不能被改变
	// 但是，这个指针是可以指向别的常量的
	const double pi = 3.14;// 定义一个常量
	const double *pip = &pi;//定义指向常量的指针pip
	//double* pip2 = &pi; // 不能用指向普通变量的指针来保存常量的地址
						// 这样写是会报错的
	
	const double n = 34.2;
	pip = &n; // 让指向常量的指针指向另一个常量，没有问题
	printf("n:%f\n", *pip);


	// 2.常量指针(const指针)
	// 解释一下，这个指针变量本身就是个常量
	// 比如一个const int a = 10; 那这个a就不能改变了
	// 那常量指针
	// int *const pa = &a; 这个pa就不能改变了，
	// 也就是说pa不能指向别人了
	// int b =20;
	// int *const pb = &b;
	// *pb = 30; 这样子是可以的，因为我们并没有改变pb存的内容
	
	int a = 10;
	int *const pa = &a;
	printf("*pa:%d\n", *pa);
	*pa = 20;
	printf("*pa:%d\n", *pa);

	//3.const指针加强版
	//先看代码
	const int num = 10;
	const int *const nump = &num; 
	// 解释
	// 首先想让一个指针指向一个const常量，那这个指针必须是指向常量的指针
	// 即，*的前面得有const
	// 其次，nump我只想让它保存num的地址，不能再指向别的变量或者常量了
	// 即，*的后面得有const
	// 这样，nump和num就深度绑定了就完全不能被改变了
	printf("*num:%d\n", *nump);


}
