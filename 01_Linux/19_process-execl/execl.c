#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //创建一个子进程，在子进程中执行exec族中的函数
    pid_t pid = fork();
    if (pid == -1){
        perror("fork");
        return -1;
    }
    if (pid > 0){
        //父进程
        printf("I am parent process, pid = %d\n", getpid());
        sleep(1);
    }else{
        //子进程
        printf("i am child process, pid = %d, ppid = %d\n", getpid(), getppid());
        //int ret = execl("hello","hello", NULL);
        //int ret = execl("/bin/ps","ps","aux",NULL);
        char *argv[] = {"ps", "aux",NULL};
        //int ret = execlp("ps", "ps", "aux", NULL);
        int ret = execvp("ps", argv);
        if (ret == -1){
            perror("execl");
            return -1;
        }
        printf("i am child process, pid = %d, ppid = %d\n", getpid(), getppid());
    }

    //在判断外面在写代码，验证子进程的代码段有没有被替换
    for (int i = 0; i < 5; i++)
    {
       printf("i = %d, pid = %d\n", i, getpid());
    }
    
    return 0;
}
