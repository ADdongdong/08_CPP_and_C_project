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
    char recvBuf[1024] = "";
    //创建字符串
    char data[1024]= "";
    while (1){
        //清空原来数组中的信息
        memset(data, 0, 1024);
        //获取标准输入的数据到数组buf中
        fgets(data, 1024, stdin);
        //给服务器发送数据
        write(fd, data, strlen(data));
        
        int len = read(fd, recvBuf, sizeof(recvBuf));
        if (len == -1){
            perror("read");
            return -1;
        } else if (len > 0){
            printf("client[%d], recv server data: %s\n", getpid(), recvBuf);
            memset(recvBuf, 0, 1024);//接受到数据后，清楚接受缓存
        } else if (len == 0){
            //表示服务器端断开链接
            printf("server closed...\n");
        }
    }
    //关闭链接
    close(fd);
    
    return 0;
}
