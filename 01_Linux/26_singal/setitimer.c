#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

//定义捕获函数

void handle(int  n){
    printf("捕捉到了信号的编号是： %d\n", n);
    printf("---------------------\n");
    return;
}

//过3秒以后，每间2秒定时一次
int main(int argc, char const *argv[])
{
    // 注册信号捕捉, 注册信号捕捉要提前说
    signal(SIGALRM,  handle);


    struct itimerval new_value;
    
    //设置值,设置间隔的时间
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;

    //设置延迟的时间,到3秒只后开始第一次定时
    new_value.it_value.tv_sec = 5;
    new_value.it_value.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &new_value, NULL);//非阻塞
    printf("定时器开始了\n");
    if (ret == -1){
        perror("setitimer");
        return -1;
    }

    getchar();

    return 0;
}
