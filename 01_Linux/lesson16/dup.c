#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd = open("a.txt", O_RDWR|O_CREAT, 0644);
    if (fd == -1){
        perror("open");
        return -1;
    }

    //首先用fd1保存fd
    //那现在是连个文件描述符都指向a.txt了
    int fd1 = dup(fd);
    if (fd1 == -1){
        perror("dup");
        return -1;
    }

    printf("fd:%d, fd1:%d\n", fd, fd1);

    close(fd);
    char * str = "hello, world";
    char * str1 = "你好西安";
    int ret = write(fd1, str, strlen(str));
    int ret1 = write(fd1, str1, strlen(str1));
    if (ret == -1 || ret1 == -1){
        perror("write");
        return -1;
    }

    close(fd1);
    return 0;
}
