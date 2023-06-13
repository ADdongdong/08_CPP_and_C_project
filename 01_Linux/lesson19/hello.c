#include <stdio.h>
#include <unistd.h>

int main(){
	printf("我是子进程pid = %d, ppid = %d\n", getpid(), getppid());
	return 0;
}
