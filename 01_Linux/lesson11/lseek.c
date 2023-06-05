#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    //打开文件
    int fd = open("hello.txt", O_RDWR);
    if (fd == -1){
        perror("open");
        return -1;
    }

    //扩展文件hello.txt的大小
    int ret = lseek(fd, 100, SEEK_END);
    if (ret == -1){
        perror("lseek");
        return -1;
    }
    
    //扩展完以后，必须得写入一个空数据才能完成扩展
    //写入一个空数据
    write(fd, " ", 1);
    close(fd);
    return 0;
}