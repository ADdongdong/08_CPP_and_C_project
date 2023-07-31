#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <poll.h>


int main(int argc, char const *argv[])
{
    //创建socket,返回值是一个监听的fd
    int lfd = socket(AF_INET, SOCK_STREAM, 0);

    //绑定
    struct sockaddr_in saddr;
    saddr.sin_addr.s_addr = INADDR_ANY;//可以分配任何IP
    saddr.sin_port = htons(9999);//本机字节序转换为网络字节序
    saddr.sin_family = AF_INET;//指定协议族

    bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    

    //监听
    listen(lfd, 8);
    
    //初始化检测的文件描述符数组
    struct pollfd fds[1024];
    for (int i = 0; i < 1024; i++){
        fds[i].fd = -1;
        fds[i].events = POLLIN;
    }

    fds[0].fd = lfd;

    int nfds = 0;

    while (1) {

        //调用poll系统函数
        int ret = poll(fds, nfds + 1, -1);
        if (ret == -1) {
            perror("poll");
            return -1;
        } else if(ret == 0){
            //过了超时时间了，但是还是没有检测到I/O就会返回0
            continue;
        } else if(ret > 0){
            //判断文件描述符实际发生的事件是不是POLLIN
            if (fds[0].revents & POLLIN) {
                //select不会告诉你那个是那个客户端连接进来了
                //表示有新的客户端连接进来了
                struct sockaddr_in cliaddr;
                int len = sizeof(cliaddr);
                int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);

                //将新的文件描述符加入到集合中
                for (int i = 1; i < 1024; i++){
                    if (fds[i].fd == -1) {
                        fds[i].fd = cfd;
                        fds[i].events = POLLIN;
                        break;
                    }
                }

                // 更新最大的文件描述符的索引
                nfds = nfds > cfd ? nfds : cfd;
            }

            for (int i = 1; i <= nfds; i++) {
                //检测文件描述符是不是发生了POLLIN读取操作
                if (fds[i].revents & POLLIN) {
                    //说明这个文件描述符对应的客户端发来了数据
                    char buf[1024] = "";
                    int len = read(fds[i].fd, buf, sizeof(buf));
                    if (len == -1){
                        perror("read");
                        exit(-1);
                    } else if (len == 0) {
                        printf("client close...\n");
                        close(fds[i].fd);
                        fds[i].fd = -1;
                    } else if (len > 0) { 
                        printf("read buf = %s\n", buf);
                        write(fds[i].fd, buf, strlen(buf));
                    }
                }
            }
        }

    }

    close(lfd);

    return 0;
}
