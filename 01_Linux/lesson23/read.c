//这个进程负责往有名管道fifo1中读取数据
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

//从管道中读取数据
int main(int argc, char const *argv[])
{
    //1.打开管道文件
    int fd = open("test", O_RDONLY);
    if (fd == -1){
        perror("open");
        return -1;
    }

    //2.读取数据
    while (1){
        char buf[1024] = {0};
        int ret = read(fd, buf, sizeof(buf));
        if (ret == -1){
            perror("read");
        }else if(ret == 0 ){
            printf("写端断开链接...\n");
            break;
        }

        printf ("recv buf: %s\n", buf);
    }
    close(fd);
    
    return 0;
}
