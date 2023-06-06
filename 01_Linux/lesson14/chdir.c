/*
    #include <unistd.h>
    
    int chdir(const char *path);
    作用：修改进程的工作目录（进程在哪个目录下工作的/启动的）
        比如在/home/headong启动了进程a.out,那么进程的工作目录就是/home/headong
    参数：
        -path:需要修改的工作目录

    #include <unistd.h>
    char *getcwd(char *buf, size_t size);
    作用：获取当前工作目录
    参数：
        - bug: 存储的路径，指向的是一个数组（传出参数）
        - size: 数组的大小
    返回值：
        返回的是指向的一块内存，这个数据就是第一个参数buf。
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    //获取当前的工作目录
    char buf[128];
    getcwd(buf, sizeof(buf));
    printf("当前的工作目录是：%s\n", buf);

    //修改工作目录
    int ret = chdir("/home/headong/08_CPP_and_C_project/01_Linux/lesson13");
    if (ret == -1){
        perror("chdir");
        return -1;
    }

    //创建一个新的文件
    int fd = open("new.txt", O_RDWR|O_CREAT, 0644);
    if (fd == -1){
        perror("open");
        return -1;
    }

    close(fd);

    //获取当前工作目录
    char buf1[128];
    getcwd(buf1, sizeof(buf1));
    printf("当前的工作目录是：%s\n", buf1);

    return 0;
}

