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
        printf("i am parent process,pid : %d\n", getpid());
        char buf[1024] = {0};
        while (1){
            int len = read(pipefd[0], buf, sizeof(buf));
            printf("parent recv: %s, pid: %d \n", buf, getpid());
            //读取管道数据不用sleep，因为如果管道中没有数据，read会自动阻塞

            //向管道中写入数据，每写一次，就停止1秒
            char *str = "hello,i am parent";
            write(pipefd[1], str, strlen(str));
            sleep(1);
        }
        
    }else if (pid == 0){
        //子进程
        printf("i am child process,pid : %d\n", getpid());
        char *buf[1024] = {0};
        while (1){
            //向管道中写入数据，每写一次，就停止1秒
            char *str = "hello,i am child";
            write(pipefd[1], str, strlen(str));
            sleep(1);
            
            //从管道中读取数据
            int len = read(pipefd[0], buf, sizeof(buf));
            printf("child recv: %s, pid: %d \n", buf, getpid());
        }
        
    }else{
        perror("fork");
        return -1;
    }
    return 0;
}
