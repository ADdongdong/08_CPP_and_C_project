#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    //fork函数，在父进程中返回自进程的进程号
    //在子进程中返回0
    //通过fork的返回值来区分父子进程
    //在父进程中返回-1表示fork失败

    //创建子进程
    pid_t pid = fork();
    if (pid == -1){
        perror("fork");
        return -1;
    }

    //判断是父进程还是子进程
    if (pid > 0){
        printf("i am parent process, pid:%d, ppid: %d\n", getpid(), getppid());
    }else{
        sleep(1);
        printf("I am child process, pid:%d, ppid:%d\n", getpid(),getppid());
    }

    //for循环
    for (int i = 0; i < 5; i++){
        printf("i:%d, pid:%d\n", i, getpid());
    }
    return 0;
}
