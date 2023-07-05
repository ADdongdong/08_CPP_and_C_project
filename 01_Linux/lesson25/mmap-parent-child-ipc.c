#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>


/*使用内存映射实现进程间通信

*/
int main(int argc, char const *argv[])
{
    //1.打开一个文件
    int fd = open("test.txt", O_RDWR);
    //2.获取文件的大小
    int size = lseek(fd, 0, SEEK_END);

    //3.创建内存映射区
    void* ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED){
        perror("mmap");
        return -1;
    }

    //3.创建子进程
    pid_t pid = fork();
    if (pid > 0){
        //父进程,父进程写数据
        strcpy((char *)ptr, "你好 啊，son!!!\n");
    }else{
        //子进程,子进程读数据
        char buf[64];
        strcpy(buf, (char *)ptr);
        printf("read data: %s\n", buf);
    }

    //关闭内存区域
    munmap(ptr, size);
    close(fd);


    return 0;
}
