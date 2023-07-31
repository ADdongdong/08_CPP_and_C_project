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

    //2.客户端绑定本地的端口和IP
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);//绑定和服务器端相同的端口号
    addr.sin_addr.s_addr = INADDR_ANY;
    
    int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if (ret == -1){
        perror("bind");
        return -1;
    }
    
    //3.通信
    while (1) {
        char buf[128];
        //接收数据
        int nums = recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);

        printf("client say: %s\n", buf);

        sleep(1);

    }
    
    close(fd);
    return 0;
}
