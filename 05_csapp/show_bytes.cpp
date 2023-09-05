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

int main() {
	int a = 10;
	show_int(a);
	float b = 13.23;
	show_float(b);
	int c = 34;
	show_void(&c);
	int val = 0x87654321;
	byte_pointer valp = (byte_pointer) &val;
	
	show_bytes(valp, 1); 
	show_bytes(valp, 2); 
	show_bytes(valp, 3); 
	const char *s = "abcdef";
	show_bytes((byte_pointer) s, strlen(s));

	return 0;
}
