/*
    SIGCHLD信号产生的三个条件
        1.子进程结束了
        2.子进程暂停了
        3.子进程继续运行
        都会给父进程发送该信号，父进程默认是忽略该信号。

    使用SIGCHLD信号解决僵尸进程的问题。
*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>


void myFunc(int num){
    printf("捕捉到的信号：%d\n", num);
    //回收子进程pcb的资源
    // while(1)
    //     wait(NULL);//回收子进程

    while(1){
        int ret = waitpid(-1, NULL, WNOHANG);
        if (ret > 0 ){
            printf("child die, pid = %d\n", ret);
        } else if (ret == 0){
            break;
        } else if (ret == -1){
            break;
        }
    }
    return;
}

int main(){
    //提前设置好阻塞信号集，阻塞SIGCHLD，
    //因为有可能子进程很快结束，父进程还没有注册完，这样，父进程还没来的及设置回收函数
    //子进程已经结束了
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);

    //创建一些子进程
    pid_t pid;
    for (int i = 0; i < 20; i++){
        pid = fork();
        if (pid == 0){
            break;
        }
    }

    if (pid >0){
        //父进程

        //捕捉子进程在死亡时发送的SIGCHLD信号
        struct sigaction act;

        act.sa_flags = 0;
        act.sa_handler = myFunc;
        sigemptyset(&act.sa_mask);
        sigaction(SIGCHLD, &act, NULL);
        //注册完信号捕捉以后，就接触阻塞
        sigprocmask(SIG_UNBLOCK, &set, NULL);

        while(1){
            printf("parent process pid: %d\n", getpid());
            sleep(2);
        }
    } else if(pid == 0){
        //子进程
        printf("child process pid: %d\n", getpid());
    }
    return 0;
}