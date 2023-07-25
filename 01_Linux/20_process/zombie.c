#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    //创建子进程
    pid_t pid = fork();
    if (pid == -1){
        perror("fork");
        return -1;
    }

    //判断是父进程还是子进程
    if (pid > 0){
        while (1){
            printf("i am parent process, pid:%d, ppid: %d\n", getpid(), getppid());
            sleep(1);
        }
        
    }else{
        printf("I am child process, pid:%d, ppid:%d\n", getpid(),getppid());
    }

    //for循环
    for (int i = 0; i < 5; i++){
        printf("i:%d, pid:%d\n", i, getpid());
    }
    return 0;
}
