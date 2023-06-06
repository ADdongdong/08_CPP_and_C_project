#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int fd = open("a.txt", O_RDWR|O_CREAT, 0644);
    if (fd == -1){
        perror("open");
        return -1;
    }

    //首先用fd1保存fd
    int fd1 = dup(fd);
    if (fd1 == -1){
        perror("dup");
        return -1;
    }

    return 0;
}
