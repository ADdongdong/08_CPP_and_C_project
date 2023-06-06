#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    struct stat statbuf;

    //调用stat以后，就会将文件元数据的内容保存在statbuf这个结构体中
    //后面就可以使用statbuf这个结构体进行输出了
    int ret = stat("a.txt", &statbuf);

    if (ret == -1){
        perror("stat");
        return -1;
    }

    printf("size:%ld\n", statbuf.st_size);

    return 0;
}