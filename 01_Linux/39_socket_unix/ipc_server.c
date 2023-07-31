#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/un.h>

int main(int argc, char const *argv[])
{
    unlink("server.sock");
    // 1. 创建监听的套接字
    int lfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (lfd == -1){
        perror("socket");
        return -1;
    }

    //2.绑定本地套接字文件
    struct sockaddr_un addr;
    addr.sun_family = AF_LOCAL;
    //这里server.sock就是服务端套接字生成的套接字文件
    //这里说的套接字文件，其实是一个伪文件，
    //本质上就是内核的一块缓冲区，有读缓冲和写缓冲
    strcpy(addr.sun_path, "server.sock");

    int ret = bind(lfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1){
        perror("bind");
        return -1;
    }

    //3.a监听
    ret = listen(lfd, 100);
    if (ret == -1) {
        perror("listen");
        return -1;
    }

    //4.等待客户端的链接
    struct sockaddr_un cliaddr;
    int len = sizeof(cliaddr);
    int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &len);
    if (cfd == -1){
        perror("accept");
        return -1;
    }

    printf("client socket filename: %s\n", cliaddr.sun_path);

    //5. 通信
    while (1) {
        /* code */
        char buf[128];
        int len = recv(cfd, buf, sizeof(buf), 0);

        if (len == -1) {
            perror("read");
            return -1;
        } else if (len == 0){
            printf("client closed...\n");
            break;
        } else if (len > 0) {
            printf("client say: %s\n", buf);
            send(cfd, buf, len, 0);
        }
    }

    close(cfd);
    close(lfd);
    
    return 0;
}
