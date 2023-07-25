#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    //通过open打开english.txt文件
    int srcfd = open("english.txt", O_RDONLY);
    if (srcfd == -1){
        perror("open");
        return -1;
    }

    //创建一个新的文件
    int destfd = open("cpy.txt", O_WRONLY|O_CREAT, 0664);
    if (destfd == -1){
        perror("destfd");
        return -1;
    }

    //频繁的读写操作

    char buf[1024] = {0};
    int len = 0; 
    while ((len = read(srcfd, buf, sizeof(buf))) > 0) {
        write(destfd, buf, len);//这里用len,写入读取的长度的内容
    }

    //关闭文件
    close(destfd);
    close(srcfd);
    return 0;
}