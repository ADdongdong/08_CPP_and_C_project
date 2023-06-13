/*
    #include <unistd.h>
    #include <fcntl.h>
    int fcntl(int fd, int cmd, ...);
    参数：
        fd 表示要操作的文件描述符
        cmd 表示对文件描述符进行那种操作 
            - F_DUPFD 复制文件描述符,得到一个新的文件描述符
                int ret = fcntl(fd, F_DUPFE);//返回值就是新复制的文件描述符的编号
            - F_GETFL 获取指定文件描述符的状态flag
                获取的flag和我们通过open函数传递的flag是一个东西
            - F_SETFL 设置文件描述符文件状态flag
                必选项：O_RDONLY, O_WRONLY, O_RDWR,不可被修改
                可选项：O_APPEND, O_NOBLOCK
                    - O_APPEND 表示追加数据
                    - O_NOBLOCK 设置为非阻塞
    
    阻塞和非阻塞：描述的是函数调用的行为。add()
*/
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char const *argv[]){
    
    //1 复制文件描述符
    // int fd =  open("1.txt", O_RDONLY);
    // if (fd == -1){
    //     perror("open");
    //     return -1;
    // }
    // int ret = fcntl(fd, F_DUPFD);

    // if (ret == -1){
    //     perror("fcntl");
    //     return -1
    // }

    //2.修改或者获取文件状态
    int fd2 = open("1.txt", O_RDWR);
    if (fd2 == -1){
        perror("open");
        return -1;
    }

    //获取原来的文件描述符装填flag
    //int flag = fcntl(fd2, F_GETFL);
    //flag |= O_APPEND;//flag = flag | O_APPEND
    //修改文件描述符状态的flag, 给flag加入O_APPEND这个标记
    //O_RDONLY | O_APPEND
    //int ret = fcntl(fd2, F_SETFL, flag);
    // if (ret == -1){
    //     perror("fcntl");
    //     return -1;
    // }
    char *str = "nihao";
    //如果在同一个进程中连续写入，则不会覆盖前面的内容
    //如果从新一个进程写，并且没有指定append，那么不会追加到文件的末尾
    //而是会从文件开头直接替换文件的内容
    write(fd2, str, strlen(str));
    write(fd2, str, strlen(str));
    write(fd2, str, strlen(str));
    write(fd2, str, strlen(str));

    close(fd2);

    return 0;
}
