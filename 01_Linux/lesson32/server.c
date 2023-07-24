#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    //1.创建socket（用于监听的套接字）
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1){
        perror("sokcet");
        return -1;
    }

    //2.绑定
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    //inet_pton(AF_INET, "127.0.0.1", saddr.sin_addr.s_addr );
    saddr.sin_addr.s_addr = INADDR_ANY;//这个宏就是 0.0.0.0 表示任意地址网卡地址
    saddr.sin_port = htons(9999);//指定端口
    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1){
        perror("bind");
        return -1;
    }

    //3.监听listen
    ret = listen(lfd, 8);
    if (ret == -1){
        perror("listen");
        return -1;
    }

    //4.接受客户端连接
    struct sockaddr_in clientaddr;
    socklen_t slen = sizeof(clientaddr);
    int cfd = accept(lfd, (struct sockaddr *)&clientaddr, &slen);
    if (cfd ==-1){
        perror("accept");
        return -1;
    }

    //输出客户端的信息
    char clientIP[16];
    inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, clientIP, sizeof(clientIP));
    unsigned short clientPort = ntohs(clientaddr.sin_port);//网络字节序转换为主机字节序
    printf("client ip is %s, port is %d\n", clientIP, clientPort);

    //5.和客户端进行通信
    //将客户端发送过来的信息原样返还给客户端
    char recvBuf[1024] = "";
    while (1){
        //5.1 获取客户端信息
        int len = read(cfd, recvBuf, sizeof(recvBuf));
        if (len == -1){
            perror("read");
            return -1;
        } else if (len >0){
            printf("recv client data: %s\n", recvBuf);
        } else if (len == 0){
            //表示客户端断开链接
            printf("client closed...\n");
            break;
        }

        //5.2 给客户端方发送数据
        //char *data = "hello, I am server";
        write(cfd, recvBuf, strlen(recvBuf));
        //清空recvBuf的内容
        memset(recvBuf, 0, 1024);
    }

    //6.关闭文件描述符
    close(cfd);
    close(lfd);
    return 0;
}
