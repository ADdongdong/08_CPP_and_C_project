#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

int val = 10;
void * callback(void * arg){
    //获取当前线程的线程id, 返回值为pthread_t
    printf("child thread id: %ld \n", pthread_self());
    //sleep(3);//只要子线程没有结束，pthread_join就会阻塞等待回收子线程资源。
    //return NULL;//相当区域pthread_exit(NULL);
    //int val = 10; //局部变量，子线程有子的栈区
    pthread_exit((void *)&val);
    //相当于 return (void *)&val
}

int main(int argc, char const *argv[])
{
    //创建一个子线程
    //1.定义tid,是传出参数，一会线程id会被tid传出
    pthread_t tid;

    //2.创建线程
    int ret = pthread_create(&tid, NULL, callback, NULL);
    if (ret != 0){
        char * errstr = strerror(ret);
        printf("%s\n", errstr);
        return -1;
    }

    //主线程
    for(int i = 0; i < 6; i++){
        printf("i: %d\n", i);
    }

    printf("tid: %ld, main thread id: %ld \n", tid, pthread_self());

    // 主线程调用pthread_join()回收子线程的资源
    int * thread_retval;
    ret = pthread_join(tid, (void **)&thread_retval); // 如果不需要获取子线程退出时的返回值，传递NULL

    if (ret != 0){
        char * errstr = strerror(ret);
        printf("%s\n", errstr);
        return -1;
    }
    printf("exit data : %d\n", *thread_retval);

    printf("回收子线程资源成功!\n");
    //让主线程退出, 当主线程退出是，不会影响其他正常运行的线程
    pthread_exit(NULL);

    //当主线程结束以后，后面的内容就不会执行了
    //所以，下面的printf就不会执行了
    printf("main thread exit\n");

    return 0;
}
