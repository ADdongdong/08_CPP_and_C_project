#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct sockInfo {
    int fd;//通信的文件描述符
    struct sockaddr_in addr;
    pthread_t tid;//线程号
};

struct sockInfo sockinfos[128];//表示可同时支持128个客户端连接进来

void *working(void * arg){
    //子线程和客户端进行通信,这里需要很多信息，比如 cfd 客户端的信息 线程号
    //所以，为了保证传入参数的方便，将这些信息打包为结构体，传入函数中
    //这个结构体为struct sockInfo
    struct sockInfo * pinfo = (struct sockInfo*)arg;
    //获取客户端的信息
    char cliIP[16];
    inet_ntop(AF_INET, &pinfo->addr.sin_addr.s_addr, cliIP, sizeof(cliIP));
    unsigned short cliPort = ntohs(pinfo->addr.sin_port);

    printf("client ip is: %s, port is %d\n", cliIP, cliPort);

    //接受客户端发来的数据
    char recvBuf[1024] = "";
    while (1) {
        int len = read(pinfo->fd, &recvBuf, sizeof(recvBuf));

        if (len == -1) {
            perror("read");
            return NULL;
        } else if (len > 0){
            printf("recv client data : %s\n", recvBuf);
        }else if (len == 0){
            printf("client closed ...\n");
            break;
        }

        write(pinfo->fd, recvBuf, strlen(recvBuf));
        //清楚recvbuf缓存
        //memset(recvBuf, 0 , 1024);
    }

    close(pinfo->fd);

    return NULL;
}


int main(int argc, char const *argv[])
{
    
    //创建socket
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1){
        perror("socket");
        return -1;
    }

    //绑定
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1){
        perror("bind");
        return -1;
    }

    //监听
    ret = listen(lfd, 128);
    if (ret == -1){
        perror("listen");
        return -1;
    }

    //初始化客户端信息数组
    int max = sizeof(sockinfos)/sizeof(sockinfos[0]);
    for (int i = 0; i < max; i++){
        bzero(&sockinfos[i], sizeof(sockinfos[i]));//将所每个元素的内容都初始化为0
        sockinfos[i].fd = -1;
        sockinfos[i].tid = -1;
    }

    //循环等待客户端连接，一旦一个客户端连接进来，就创建一个子线程进行通信连接
    while (1){
        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);
        //接受链接
        int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &len);


        struct sockInfo * pinfo;
        for (int i = 0; i < max; i++){
            //从这个数组中，找到一个可用的sockInfo元素
            if (sockinfos[i].fd == -1){
                pinfo = &sockinfos[i];
                break;
            }

            //如果第129个客户端来链接了，那就等1秒时间
            if (i == max - 1){
                sleep(1);
                i--;
            }
        }
        
        //初始化要传递的信息
        pinfo->fd = cfd;
        memcpy(&pinfo->addr, &cliaddr, len);

        // 创建子线程
        pthread_create(&pinfo->tid, NULL, working, pinfo);
        
        //回收线程资源
        pthread_detach(pinfo->tid);

    }

    //关闭listen文件描述符
    close(lfd);
    
    return 0;
}
