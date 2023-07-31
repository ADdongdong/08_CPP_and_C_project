#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/un.h>

int main(int argc, char const *argv[])
{
    //每次调用这个程序，都要先删除上次创建的sock文件，不然就不能连接
    //unlink("client.sock");
    // 1. 创建套接字
    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (fd == -1){
        perror("socket");
        return -1;
    }

    //2.绑定本地套接字文件
    struct sockaddr_un caddr;
    caddr.sun_family = AF_LOCAL;
    //这里server.sock就是服务端套接字生成的套接字文件
    //这里说的套接字文件，其实是一个伪文件，
    //本质上就是内核的一块缓冲区，有读缓冲和写缓冲
    strcpy(caddr.sun_path, "client.sock");

    int ret = bind(fd, (struct sockaddr *)&caddr, sizeof(caddr));
    if (ret == -1){
        perror("bind");
        return -1;
    }


    //3. 链接服务器
    struct sockaddr_un seraddr;
    seraddr.sun_family = AF_LOCAL;
    strcpy(seraddr.sun_path, "server.sock");
    ret = connect(fd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    if (ret == -1){
        perror("connect");
        return -1;
    }

    //5. 通信
    int num = 0;
    while (1) {

        //发送数据，接收数据
        char buf[128];
        sprintf(buf, "hello i am client %d\n", num++);
        send(fd, buf, strlen(buf) + 1, 0);
        printf("client say: %s\n", buf);

        //接收数据
        int len = recv(fd, buf, sizeof(buf), 0);

        if (len == -1) {
            perror("recv");
            return -1;
        } else if (len == 0){
            printf("server closed...\n");
            break;
        } else if (len > 0) {
            printf("server say: %s\n", buf);
        }

        sleep(1);
    }

    close(fd);
    
    return 0;
}
