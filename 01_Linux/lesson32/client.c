#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    //1. 创建一个套接字
    int fd =socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1){
        perror("socket");
        return -1;
    }

    //2.连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(9999);
    int ret = connect(fd,(struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (ret == -1){
        perror("connect");
        return -1;
    }

    //3.通信，发送数据
    char *data = "hello, I am client";
    //给服务器发送数据
    write(fd, data, strlen(data));
    
    char recvBuf[1024] = {0};
    int len = read(fd, recvBuf, sizeof(recvBuf));
    if (len == -1){
        perror("read");
        return -1;
    } else if (len >0){
        printf("recv server data: %s\n", recvBuf);
    } else if (len == 0){
        //表示客户端断开链接
        printf("server closed...\n");
    }

    //关闭链接
    close(fd);
    
    return 0;
}
