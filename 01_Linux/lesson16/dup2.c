#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd1 = open("1.txt", O_RDWR|O_CREAT, 0644);
    if (fd1 == -1){
        perror("open");
        return -1;
    }

    int fd2 = open("2.txt", O_RDWR|O_CREAT, 0644);
    if (fd2 == -1){
        perror("open");
        return -1;
    }

    printf("fd1:%d fd2:%d\n", fd1, fd2);

    //使用dup2指向fd指向的文件，现在就可以用fd2来操作1.txt了
    int fd3 = dup2(fd1, fd2);//所以返回的fd3和fd2是一样的

    //使用fd2想1.txt写入数据
    char * str = "hello world";
    int ret = write(fd3, str, strlen(str));

    printf("fd1:%d fd2:%d fd3:%d\n", fd1, fd2, fd3);
    close(fd3);
    close(fd2);

    return 0;
}
