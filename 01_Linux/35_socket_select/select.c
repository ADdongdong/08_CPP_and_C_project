#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>

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
    
    //创建一个fd_set的集合，存放的是需要检测的文件描述符
    fd_set rdset, tmp;
    FD_ZERO(&rdset);//将标志位都置为0
    FD_SET(lfd, &rdset);
    int maxfd = lfd;

    while (1) {

        tmp = rdset;
        //调用select系统函数，让内核帮着检测哪些文件描述符有数据
        //注意，select只会标记刚才I/O过的客户端，可能有客户端，刚才没有I/O,但是后面要I/O
        //这时候，这个客户端就会被标记为0,
        //所以，为了避免将我们已经链接上，最近这段时间没有通信，但是后面可能I/O的客户端置为0
        //这时候就要传入tmp,而不是传入rdset,只有当我们判断该客户端确实关闭的时候
        //我们才会将rdset中的该客户端的文件描述符位置为0

        //此时，已经有数据的文件描述符会在tmp中被置为1
        int ret = select(maxfd + 1, &tmp, NULL, NULL, NULL);
        if (ret == -1) {
            perror("select");
            return -1;
        } else if(ret == 0){
            //过了超时时间了，但是还是没有检测到I/O就会返回0
            continue;
        } else if(ret > 0){
            //说明检测到了有文件描述符对应的缓冲区的数据发生了改变
            if (FD_ISSET(lfd, &tmp)) {
                //select不会告诉你那个是那个客户端连接进来了
                //表示有新的客户端连接进来了
                struct sockaddr_in cliaddr;
                int len = sizeof(cliaddr);
                int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);

                //将新的文件描述符加入到集合中
                FD_SET(cfd, &rdset);//注意，这里是添加到rdset而不是tmp中

                // 更新最大的文件描述符
                maxfd = maxfd > cfd ? maxfd : cfd;
            }

            char buf[1024] = "";
            for (int i = lfd + 1; i <= maxfd; i++) {
                if (FD_ISSET(i, &tmp)) {
                    //说明这个文件描述符对应的客户端发来了数据
                    int len = read(i, buf, sizeof(buf));
                    if (len == -1){
                        perror("read");
                        exit(-1);
                    } else if (len == 0) {
                        //说明与该客户端通信的文件描述符已经关闭
                        //也就是该客户端已经关闭
                        printf("client close...\n");
                        close(i);
                        FD_CLR(i, &rdset);//该客户端移除rdset
                    } else if (len > 0) { 
                        printf("read buf = %s\n", buf);
                        write(i, buf, strlen(buf));
                    }
                }
            }
        }

    }

    close(lfd);

    return 0;
}
