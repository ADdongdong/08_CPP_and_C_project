#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

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
        while (1){
            int len = read(pipefd[0], buf, sizeof(buf));
            printf("parent recv: %s, pid: %d \n", buf, getpid());
            bzero(buf, 1024);
            //读取管道数据不用sleep，因为如果管道中没有数据，read会自动阻塞

            //向管道中写入数据，每写一次，就停止1秒
            // char *str = "hello,i am parent";
            // write(pipefd[1], str, strlen(str));
            //sleep(1);
        }
        
    }else if (pid == 0){
        //子进程
        //子进程不去读
        close(pipefd[0]);
        printf("i am child process,pid : %d\n", getpid());
        char *buf[1024] = {0};
        while (1){
            //向管道中写入数据，每写一次，就停止1秒
            char *str = "hello,i am child\n";
            write(pipefd[1], str, strlen(str));
            //sleep(1);
            //如果去掉sleep,在向管道中写完数据以后，就可能继续直接执行子进程中后面的读操作了
            //这时候就会出现，子进程从管道中读取自己写入管道的数据
            //父进程同理，当时间片轮转到父进程的时候，又出现了和子进程一样的问题
            
            //从管道中读取数据
            // int len = read(pipefd[0], buf, sizeof(buf));
            // printf("child recv: %s, pid: %d \n", buf, getpid());
        }
        
    }else{
        perror("fork");
        return -1;
    }
    return 0;
}
