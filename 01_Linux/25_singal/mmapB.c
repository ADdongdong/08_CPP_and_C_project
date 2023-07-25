#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    //1.打开要映射的磁盘文件
    int fd = open("test.txt", O_RDWR);
    //2.获取文件的大小，mmap函数要用
    int size = lseek(fd, 0, SEEK_END);

    //3.创建内存映射区
    //进程mmapA,在通信中负责写入信息
    void *ptr = mmap(NULL, size, PROT_EXEC | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED){
        perror("mmap");
        return -1;
    }

    //4.向共享文件中写入内容
    char buf[64];
    strcpy(buf, (char *)ptr);
    printf("read data: %s\n", buf);

    //5.关闭内存区域
    munmap(ptr, size);
    //6.关闭文件描述符
    close(fd);

    return 0;
}
