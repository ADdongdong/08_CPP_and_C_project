#include <pthread.h>
#include <stdio.h>
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

int main(int argc, char const *argv[])
{
    //创建一个子线程
    pthread_t tid;

    int ret = pthread_create(&tid, NULL ,callback, NULL);
    if (ret != 0){
        char * errstr = strerror(ret);
        printf("err: %s\n", errstr);
        return -1;
    }

    //取消线程
    pthread_cancel(tid);


    for (int i = 0; i < 5; i++){
        printf("main : %d\n", i);
    }

    // 输出主线程和子线程的id
    printf("tid: %ld, main thread id: %ld \n", tid, pthread_self());

    pthread_exit(NULL);//退出子线程
    return 0;
}
