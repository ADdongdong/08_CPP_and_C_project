#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    //1.判断管道文件是否存在，如果存在，直接使用，若不存在，则创建
    int ret = access("fifo1", F_OK);
    if (ret == -1){
        //文件不存在
        printf("管道fifo1不存在，创建对应的有名管道\n");
        int fifo1 = mkfifo("fifo1", 0664);//参数为创建的这个管道文件的路径和权限
        if (fifo1 == -1){
            perror("mkfifo");
            return -1;
        }
    }

    ret = access("fifo2", F_OK);
    if (ret == -1){
        //文件不存在
        printf("管道fifo1不存在，创建对应的有名管道\n");
        int fifo2 = mkfifo("fifo2", 0664);//参数为创建的这个管道文件的路径和权限
        if (fifo2 == -1){
            perror("mkfifo");
            return -1;
        }
    }

    //2.以只读的方式打开管道fifo1
    int fdr = open("fifo1", O_RDONLY);
    if (fdr == -1){
        perror("open");
        return -1;
    }
    printf("打开管道fifo1成功, 等待读取...\n");

    //3.以只写的方式打开管道fifo2
    int fdw = open("fifo2", O_WRONLY);
    if (fdw == -1){
        perror("open");
        return -1;
    }
    printf("打开管道fifo2成功，等待写入...\n");

    char buf[128];
    
    //4.循环读写数据
    while (1){

        //5.从fifo1中读管道数据
        memset(buf, 0, 128);
        ret = read(fdr, buf, 128);
        if (ret <= 0){
            perror("read");
            break;
        }
        printf("buf: %s\n", buf);

        //6.往fifo2中写入数据
        //清空原来数组中的数据,如果不清空的话，可能出现问题
        memset(buf, 0, 128);
        //获取标准输入的数据到数组buf中
        fgets(buf, 128, stdin);
        //写数据
        ret = write(fdw, buf, strlen(buf));
        if (ret == -1){
            perror("write");
            return -1;
        }

        
    }

    //关闭文件描述符
    close(fdr);
    close(fdw);
    
    return 0; 
}
   
   
   
   
