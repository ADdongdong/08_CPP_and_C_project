#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>

//使用内存映射实现文件拷贝的功能
/*
    思路：
        1.对原始文件进行内存映射
        2.创建一个新的文件
            2.1 对新文件进行拓展，拓展到原始文件同样的大小
        3.把新文件的数据映射到内存中
        4.通过内存拷贝，将一个文件的内存数据拷贝到新的文件内存中
        5.释放资源
*/


int main(int argc, char const *argv[])
{
    
    //1.对原始文件进行拷贝 
    int fd = open("english.txt", O_RDWR);
    if (fd == -1){
        perror("open");
        return -1;
    }

    //1.1 获取原始文件的大小，方便扩展拷贝文件
    int len = lseek(fd, 0, SEEK_END);

    //2.创建一个新的文件
    int fd1 = open("cpy.txt", O_RDWR | O_CREAT, 0664);
    if (fd1 == -1){
        perror("open");
        return -1;
    }
    
    //2.1 对创建的文件进行内存扩展
    truncate("cpy.txt", len);
    write(fd1, " ", 1);

    //3. 分别做内存映射
    void * ptr = mmap(NULL, len, PROT_READ |PROT_WRITE, MAP_SHARED, fd, 0);
    void * ptr1 = mmap(NULL, len, PROT_READ |PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED){
        perror("mmap");
        return -1;
    }
    
    if (ptr1 == MAP_FAILED){
        perror("mmap");
        return -1;
    }

    //4. 开始内存拷贝
    memcpy(ptr1, ptr, len);//memcpy 参数1：往哪里拷贝，参数2：从哪里拷贝，参数3：拷贝多少数据

    //5.释放资源
    //先打开的资源后释放
    munmap(ptr1, len);
    munmap(ptr, len);

    close(fd1);
    close(fd);

    return 0;
}

