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
    int num = 100;
    //判断是父进程还是子进程
    if (pid > 0){
        //说明在父进程中,编写父进程中的代码
        printf("i am parent process, pid:%d, ppid: %d\n", getpid(), getppid());
        printf("parent num = num + 10 = %d\n", num+10);
        num+=10;
    }else{
        //说明在子进程中,编写子进程中的代码
        printf("I am child process, pid:%d, ppid:%d\n", getpid(),getppid());
        printf("child num = num + 100 = %d\n", num+100);
        num+=100;
    }
    printf("num = %d\n", num);
    //for循环
    for (int i = 0; i < 5; i++){
        printf("i:%d, pid:%d\n", i, getpid());
        sleep(1);
    }
    
    return 0;

}
