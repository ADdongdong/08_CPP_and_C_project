#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    //1.创建一个socket
    int fd = socket(PF_INET, SOCK_DGRAM,  0);

    if (fd == -1){
        perror("socket");
        return -1;
    }

    //服务端的地址信息
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr.s_addr);
    
    int num = 0;
    //3.通信
    while (1) {
        char sendBuf[128];
        sprintf(sendBuf, "hello, i am client %d\n", num++);
        //发送数据
        sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&saddr, sizeof(saddr));


        //接收数据
        int nums = recvfrom(fd, sendBuf, sizeof(sendBuf), 0, NULL, NULL);

        printf("client say: %s\n", sendBuf);

        sleep(1);

    }
    
    close(fd);
    return 0;
}
