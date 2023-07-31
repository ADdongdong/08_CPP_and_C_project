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
    int num = 0;
    while (1){
        char sendBuf[1024] = {0};
        fgets(sendBuf, sizeof(sendBuf), stdin);
        //sprintf(sendBuf, "send data %d", num++);
        write(fd, sendBuf, strlen(sendBuf) + 1);
        
        int len = read(fd, sendBuf, sizeof(sendBuf));
        if (len == -1){
            perror("read");
            return -1;
        } else if (len > 0){
            printf("client[%d], recv server data: %s\n", getpid(), sendBuf);
        } else if (len == 0){
            //表示服务器端断开链接
            printf("server closed...\n");
        }
        //sleep(1);
        usleep(1000);
    }
    //关闭链接
    close(fd);
    
    return 0;
}
