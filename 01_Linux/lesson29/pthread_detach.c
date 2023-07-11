#include <pthread.h>
#include <stdio.h>
#include <string.h>

void * callback(void * arg){
    printf("child thread id： %ld\n", pthread_self());
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

    // 输出主线程和子线程的id
    printf("tid: %ld, main thread id: %ld \n", tid, pthread_self());

    //设置子线程分离, 子线程分离后，子线程结束时候对应的资源就不需要主线程释放。
    ret = pthread_detach(tid);
    if (ret != 0){
        char * errstr = strerror(ret);
        printf("err: %s\n", errstr);
        return -1;
    }

    ret = pthread_join(tid, NULL);//分离后再链接，会报错
    if (ret != 0){
        char * errstr = strerror(ret);
        printf("err3: %s\n", errstr);
        return -1;
    }

    pthread_exit(NULL);//退出子线程
    return 0;
}
