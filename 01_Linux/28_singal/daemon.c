/*
    写一个守护进程，每隔2s获取一下系统时间，将这个时间写入到磁盘文件中。
*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <string.h>

void work(int num){
    //捕捉到信号之后，获取系统时间，写入磁盘文件
    time_t tm = time(NULL);
    struct tm  *local_tm = localtime(&tm);
    char buf[1024];
    
    // sprintf(buf, "%d-%d-%d %d:%d:%d\n", local_tm->tm_year, local_tm->tm_mon,
    // local_tm->tm_mday, local_tm->tm_hour, local_tm->tm_min, local_tm->tm_sec);
    // printf("%s\n", buf);
    

    char * str = asctime(local_tm);
    //写入文件中
    int fd = open("time.txt", O_RDWR | O_CREAT | O_APPEND, 0664);
    write(fd, str, strlen(str));
}

int main(int argc, char const *argv[])
{
    //1.创建子进程，退出父进程
    pid_t pid = fork();
    
    if (pid > 0){
        return 0;
    }

    //2.将子进程重新创建一个会话
    setsid();//返回值为新会话的sid
    //新会话是没有控制终端的

    //3.设置掩码
    umask(022);

    //4.更改工作目录
    chdir("/home/headong/");

    //5.关闭、重定向文件描述符
    int fd = open("/dev/null", O_RDWR);
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    //6.业务逻辑

    // 捕捉定时信号
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = work;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM, &act, NULL);

    //创建定时器
    struct itimerval val;
    val.it_value.tv_sec = 2;
    val.it_value.tv_usec = 0;
    val.it_interval.tv_sec = 2;
    val.it_interval.tv_usec = 0;
    
    setitimer(ITIMER_REAL, &val, NULL);
    

    //不让进程结束
    while(1){
        sleep(10);
    }
    return 0;
}
