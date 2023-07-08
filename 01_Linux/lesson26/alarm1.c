#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

/*
    程序运行实际时间 = 内核时间(系统调用) + 用户时间 + 消耗时间(I/O等)
    进行文件IO操作的时候比较浪费时间

    定时器：与进程状态无关（自然定时法）无论进程处于什么状态，alarm都会计时。
*/
//计算1秒中电脑能数多少个数字
int main(int argc, char const *argv[])
{
    int ret = alarm(1);
    int i = 0;
    while(1){
        printf("%i\n", i++);
    }
    return 0;
}
