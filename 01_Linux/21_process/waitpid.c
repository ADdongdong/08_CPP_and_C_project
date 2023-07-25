#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    //有一个父进程,现在要创建5个子进程
    pid_t  pid;
    for (int i = 0; i < 5; i++){
        pid = fork();
        //如果当前pid为0，说明已经在子进程中，
        //就不需要再创建子进程的子进程了，即孙子进程
        if (pid == 0) break;
    }

    if (pid > 0){
        //父进程
        while (1){
            printf("parent,pid = %d\n", getpid());
            sleep(1);

            int st;
            int ret = waitpid(-1, &st, WNOHANG);//设置非阻塞
            //int ret = waitpid(NULL);//传入NULL表示不想获取子进程的状态
            //printf("child die, pid = %d\n", ret);
            if (ret == -1){
                //如果如果没有子进程，会直接退出
                perror("waitpid");
                return -1;
            }
            
            if (ret == 0){
                //waitpid的第三个参数设置为WNOHANG，如果还有进程没有回收，那么返回值就是0
                //说明还有子进程存在
                continue;
            }else if(ret >0){

                if(WIFEXITED(st)) {
                    //是不是正常退出
                    printf("退出的状态码是： %d\n", WEXITSTATUS(st));
                }

                if(WIFSIGNALED(st)){
                    //是不是异常终止
                    printf("被%d号信号干掉了\n", WTERMSIG(st));
                }

                sleep(1);
            }

        }
    }else if (pid == 0){
        while(1){
            printf("child,pid = %d\n", getpid());
            sleep(1);
        }
        exit(0);
        //子进程
    }else {
        //调用fork失败
        perror("fork");
        return -1;
    }
    return 0; //exit(0)
}
