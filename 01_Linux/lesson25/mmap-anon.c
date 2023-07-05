/*
    匿名映射：不需要文件实体来进行内存映射
    注意：只能进行父子间的进程映射
*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <wait.h>
#include <sys/mman.h>

int main(int argc, char const *argv[])
{
    //1.创建匿名内存映射区
    int len = 4096;
    void * ptr = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED){
        perror("mmap");
        return -1;
    }
    //父子进程间通信
    pid_t pid = fork();
    if (pid > 0){
        strcpy((char *)ptr, "hello,world\n");
        wait(NULL);
    }else if(pid == 0){
        //子进程
        sleep(1);
        printf("我是子进程：%s\n",(char*)ptr);
    }

    //释放内存映射区
    int ret = munmap(ptr, len);
    if (ret == -1){
        perror("munmap");
        return -1;
    }

    return 0;
}
