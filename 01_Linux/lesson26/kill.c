#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t pid = fork();

    if (pid == 0){
        //子进程
        int i = 0;
        for (i = 0; i < 5; i++){
            printf("child process\n");
            sleep(1);
        }
    } else if (pid > 0){
        //父进程
        printf("parent process\n");
        sleep(2);
        printf("kill child process now\n");
        kill(pid, SIGINT);
    }
    return 0;
}
