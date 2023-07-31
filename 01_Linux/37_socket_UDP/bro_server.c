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
    
    //2.设置广播属性
    int op = 1;//op为1表示允许广播
    setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &op, sizeof(op));

    //3.创建一个广播的地址
    struct sockaddr_in cliaddr;
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(9999);
    inet_pton(AF_INET, "192,168,4,39", &cliaddr.sin_addr.s_addr);


    //3.通信
    int num = 0;
    while (1) {
        char sendBuf[128];
        sprintf(sendBuf, "hello, client....%d\n", num++);

        //发送数据
        sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
        printf("广播的数据:%s\n", sendBuf);
        sleep(1);
    }
    
    close(fd);
    return 0;
}
