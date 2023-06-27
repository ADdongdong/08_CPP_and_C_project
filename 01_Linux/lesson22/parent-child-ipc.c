#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

/*
    实现 ps aux | grep xxx 父子进程之间通信
    子进程： ps aux, 子进程结束后，将数据发送给傅进臣
    父进程：获取收到的数据，过滤

      本代码仅仅实现，父进程获取到数据ps aux，然后通过管道发送给子进程，然后进行打印，
    不去实现过滤的功能。 

    pipe() 
    execlp()
    子进程将标准输出重定向到管道的写端。 dup2
*/

int main(int argc, char const *argv[])
{
    //创建一个管道
    int fd[2];
    int ret = pipe(fd);

    if (ret == -1){
        perror("pipe");
        return -1;
    }
    
    //创建子进程
    pid_t pid = fork();

    if (pid > 0){
        // 父进程
        // 关闭写端
        // 从管道中读取数据
        close(fd[1]);
        char buf[1024] = {0};
        int len = -1;
        while (len = read(fd[0], buf, sizeof(buf) - 1))
        {
            //过滤数据，然后输出
            printf("%s", buf);
            //清空数组中的内容
            memset(buf, 0, 1024);
        }
        
        wait(NULL);
        

    }else if (pid == 0){
        // 子进程
        // 子进程负责写数据，关于读端
        // fd[0] 指向管道的读端
        // fd[1] 指向管道的写端
        close(fd[0]);
        // 进行文件描述符的重定向 stdout_fileno -> fd[1]
        // 这里将管道的写入，也就是文件描述符fd[1] 重定向到stdout,标准输出文件描述符上
        // 也就是说，本来要写入到标准输出的文件，会写入到fd[1]中
        dup2(fd[1], STDOUT_FILENO);
        // 执行ps aux
        execlp("ps", "ps", "aux", NULL);
        perror("execlp");
        return -1;
    }else{
        perror("fork");
        return -1;
    }
    return 0;
}
