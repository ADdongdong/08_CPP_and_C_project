#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


//自线程代码
void *callback(void * arg){
    printf("child thread...\n");
    printf("arg value: %d\n", *(int *)arg);
    //使用(int *)将这个指针转换成int指针，然后，使用*取值运算符
    //取到这个地址所指向内存所保存的数据。
    return NULL;
}

//主线程代码
int main(int argc, char const *argv[])
{
    pthread_t tid;
    
    int num = 10;

    //创建一个子线程NULL
    int ret = pthread_create(&tid, NULL, callback, (void *)&num);
    if (ret != 0){
        char * errstr = strerror(ret);
        printf("error: %s\n", errstr);
        return -1;
    }

    for (int i = 0; i < 6; i++){
        printf("i: %d\n", i);
        sleep(1);
    }


    return 0;
}
