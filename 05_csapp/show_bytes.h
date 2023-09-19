#ifndef SHOW_BYTES_H
#define SHOW_BYTES_H
#include <stdio.h>
#include <string.h>

typedef unsigned char* byte_pointer; //

void show_bytes(byte_pointer start, size_t len) {
	size_t i;
	printf("0x");
	// 这里用下标元素符来进行取值，相当于*
	for (i = 0; i < len; i++) {
		// printf("%.2x", start[i]);
		printf("%.2x", *(start + i)); //这一行和上面哪一行的写法是一样的
	}
	printf("\n");
}

//使用16进制展示int变量
void show_int(int x) {
	// sizeof查看这个变量有几个Byte,因为，一般我们操作系统都是按字节byte寻址的
	show_bytes((byte_pointer) &x, sizeof(int));
}

//使用16进制展示指针变量
void show_float(float x) {
	show_bytes((byte_pointer) &x, sizeof(float));
}

//使用16进制展示地址
// 这里期待传入的参数是void* 也就是说，我们传入任意一个地址变量都是可以的
void show_void(void* x) {
	show_bytes((byte_pointer) &x, sizeof(void *));
}


#endif
