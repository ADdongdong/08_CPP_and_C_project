#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    //创建sockete
    int lfd = socket(PF_INET, SOCK_STREAM, 0);

    //绑定
    struct sockaddr_in saddr;
    saddr.sin_port = htons(9999);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;

    bind(lfd, (struct sockaddr*)&saddr, sizeof(saddr));

    //监听
    listen(lfd, 8);

    //调用epoll_create()创建一个epoll实例
    int epfd = epoll_create(100);

    //将监听的文件描述符相关检测信息加入到
    struct epoll_event epev;
    epev.events = EPOLLIN;//检测读事件
    epev.data.fd = lfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &epev);

    struct epoll_event epevs[1024];
    
    while (1) {
        int ret = epoll_wait(epfd, epevs, 1024, -1);
        if (ret == -1) {
            perror("epoll_wait");
            exit(-1);
        }
        printf("ret = %d\n", ret);

        for (int i = 0; i < ret; i++) {
            int curfd = epevs[i].data.fd;

            if (curfd == lfd) {
                // 监听的文件描述符有数据到达
                // 表示有心的客户端连接进来了
                struct sockaddr_in client;
                int len = sizeof(client);
                int cfd = accept(lfd, (struct sockaddr *)&client, &len);

                epev.events = EPOLLIN;
                epev.data.fd = cfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &epev);
            }else {
                // if (epevs[i].events & EPOLLOUT) {
                //     continue;
                // }
                //有数据到达，需要通信
                //char buf[1024] = "";
                char buf[5] = "";
                int len = read(curfd, buf, sizeof(buf));
                if (len == -1){
                    perror("read");
                    exit(-1);
                } else if (len == 0 ){
                    printf("client closed...\n");
                    epoll_ctl(epfd, EPOLL_CTL_DEL, curfd, NULL);
                    close(curfd);
                } else if (len > 0) {
                    printf("read recv = %s\n", buf);
                    write(curfd, buf, strlen(buf) + 1);
                }
            }
        }

    }
    close(lfd);
    close(epfd);

    return 0;
}
