#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    //创建文件
    int fd = open("create.cxt", O_RDWR|O_CREAT, 0777);

    if(fd == -1){
        perror("open");
        return -1;
    }
    
    //关闭文件描述符
    close(fd);
    return 0;
}