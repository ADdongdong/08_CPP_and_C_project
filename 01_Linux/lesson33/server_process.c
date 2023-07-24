#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <wait.h>


void recyleChild(int num){
    printf("捕捉到的信号：%d\n", num);

    while (1){
        int ret = waitpid(-1, NULL, WNOHANG);
        if (ret == -1){
            //所有的子进程都回收了
            break;
        }else if (ret == 0){
            //还有子进程活着，继续回收
            break;
        }else if (ret > 0){
            //被回收了
            printf("子进程[%d]被回收了\n", ret);
        }
        
    }
}

int main(int argc, char const *argv[])
{
    //注册信号捕捉
    //定义对信号处理的结构体
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = recyleChild;
    sigemptyset(&act.sa_mask);
    //注册信号捕捉函数
    sigaction(SIGCHLD, &act, NULL);

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

    //不断循环等待客户端连接
    while(1) {
        
        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);
        
        // 接受链接
        int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &len);
        if (cfd == -1) {
            perror("accept");
            return -1;
        }

        // 每一个链接进来的客户端，都创建一个子进程跟客户端进行通信
        pid_t pid = fork();
        if (pid == 0){
            //子进程
            //获取客户端的信息
            char cliIP[16];
            inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, cliIP, sizeof(cliIP));
            unsigned short cliPort = ntohs(cliaddr.sin_port);

            printf("client ip is: %s, port is %d\n", cliIP, cliPort);

            //接受客户端发来的数据
            char recvBuf[1024] = "";
            while (1) {
                int len = read(cfd, &recvBuf, sizeof(recvBuf));

                if (len == -1) {
                    perror("read");
                    return -1;
                } else if (len > 0){
                    printf("recv client data : %s\n", recvBuf);
                }else if (len == 0){
                    printf("client closed ...");
                    break;
                }

                write(cfd, recvBuf, strlen(recvBuf));
                //清楚recvbuf缓存
                //memset(recvBuf, 0 , 1024);
            }

            close(cfd);
            return 0; //退出当前子进程
            
        }
    }

    //关闭监听文件描述符
    close(lfd);
    return 0;
}
