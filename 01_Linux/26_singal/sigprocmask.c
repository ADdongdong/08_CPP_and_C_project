//编写议程程序，将所有的常规信号(1-31)未决状态打印到屏幕
//设置某些信号是阻塞的，通过键盘产生这些信号。
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


int main(){
    //设置2ctrl + c,3 ctrl + \号新号阻塞
    sigset_t set;
    sigemptyset(&set);
    // 将2号和3号信号添加到新号集中
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    //修改内核中的阻塞xihao
    sigprocmask(SIG_BLOCK, &set, NULL);
    
    int num = 0;
    while (1){
        num++;
        // 获取当前未决信号集的数据
        sigset_t pendingsets;

        sigemptyset(&pendingsets);
        sigpending(&pendingsets);

        //遍历前32位
        for (int  i = 1; i <= 31; i++)
        {
            if(sigismember(&pendingsets, i) == 1){
                printf("1");
            }else if (sigismember(&pendingsets, i) == 0){
                printf("0");
            }else{
                perror("sigismember");
                return -1;
            }
        }
        printf("\n");
        sleep(1);
        if (num == 10){
            //解除阻塞
            sigprocmask(SIG_UNBLOCK, &set, NULL);
        }
        
    }
    return 0;
}
