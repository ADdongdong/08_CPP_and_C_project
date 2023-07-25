#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>


/*
    设置管道非阻塞
    int flags = fcntl(fd[0], F_GETFL);//获取原来的flag
    flags = O_NONBLOCK; //修改flags的值
    fcntl(fd[0], F_SETFL, flags);//这是新的flag
*/
//子进程发送数据给父进程，父进程读取到数据输出
int main(int argc, char const *argv[])
{
    
    //创建一个管道,在fork之前，在父进程中创建
    int pipefd[2];//定义保存pipe读写端文件描述符的数组
    int ret = pipe(pipefd);
    if (ret == -1){
        perror("pipe");
        return -1;
    }
    //管道创建成功pipefd[0]为读端，pipefd[1]为写端
    pid_t pid = fork();
    if (pid > 0){
        //父进程
        //父进程不去写
        close(pipefd[1]);
        printf("i am parent process,pid : %d\n", getpid());
        char buf[1024] = {0};

        //设置父进程的读端文件描述符的flags为非阻塞
        //也就是说，读完数据以后，后面读read返回的结果就是-1了
        //我们把-1的error信息打印出来看看
        int flags = fcntl(pipefd[0], F_GETFL);//获取原来的flag
        flags |= O_NONBLOCK; //修改flags的值
        fcntl(pipefd[0], F_SETFL, flags);//这是新的flag

        while (1){
            //这里，父进程就只能成功读取一次，printf打印一次就不会再打印
            //虽然没有阻塞，但是，读不到数据了
            int len = read(pipefd[0], buf, sizeof(buf));
            if (len == -1){
                perror("read");
            }
            printf("len: %d\n", len);
            printf("parent recv: %s, pid: %d \n", buf, getpid());
            sleep(1);
            bzero(buf, 1024);
        }
        
    }else if (pid == 0){
        //子进程
        //子进程不去读
        close(pipefd[0]);
        printf("i am child process,pid : %d\n", getpid());
        char *buf[1024] = {0};
        while (1){
            //向管道中写入数据，每写一次，就停止1秒
            char *str = "hello,i am child";
            write(pipefd[1], str, strlen(str));
            sleep(10);
        }
        
    }else{
        perror("fork");
        return -1;
    }
    return 0;
}
