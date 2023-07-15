#include <stdio.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void * callback(void * arg){
    printf("child thread id： %ld\n", pthread_self());
    for (int i = 0; i < 5; i++){
        printf("child : %d\n", i);
        //sleep(1);
    }
    
    pthread_exit(NULL);
}

int main(){
    //创建一个线程属性变量
    pthread_attr_t attr;
    //初始化属性变量
    pthread_attr_init(&attr);

    //设置属性
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    //获取线程栈的大小
    size_t size;
    pthread_attr_getstacksize(&attr, &size);

    printf("thread stack size : %ld\n", size);
    //创建一个子线程
    pthread_t tid;

    int ret = pthread_create(&tid, &attr, callback, NULL);

    // 输出主线程和子线程的id
    printf("tid: %ld, main thread id: %ld \n", tid, pthread_self());

    //释放线程属性资源
    pthread_attr_destroy(&attr);

    pthread_exit(NULL);
    return 0;
}