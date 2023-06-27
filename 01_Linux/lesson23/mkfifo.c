/*
    创建fifo文件
    1.通过命令 mkfifo 名字
    2.通过mkfifo函数
*/
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //创建一个有名管道，名称为fifo1
    //1.判断fifo文件是否存在
    int ret = access("fifo1", F_OK);
    if (ret == -1){
        printf("管道不存在，创建管道\n");
        //2.创建管道文件
        ret = mkfifo("fifo1", 0664);
        if (ret == -1){
            perror("mkfifo");
            return -1;
        }
    }

    //3.打开管道
    int fd = open("test", O_WRONLY);
    if (fd == -1){
        perror("open");
        exi
    }
    return 0;
}
