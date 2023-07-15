/*
    案例
    创建8个线程，操作同一个全局变量
    3个线程不定时写一个全局变量，其余5个线程，不定时读一个全局变量
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


//创建一个共享数据
int num = 1;
//定义互斥锁
pthread_mutex_t mutex;
pthread_rwlock_t rwlock;

void * writeNum(void *arg){
    while (1){
        //pthread_mutex_lock(&mutex);
        pthread_rwlock_wrlock(&rwlock);
        num ++;
        printf("++write, tid : %ld, num : %d\n", pthread_self(), num);
        //pthread_mutex_unlock(&mutex);
        pthread_rwlock_unlock(&rwlock);

        usleep(100);
    }
    return NULL;
}

void * readNum(void *arg){
    while (1){
        //pthread_mutex_lock(&mutex);
        pthread_rwlock_wrlock(&rwlock);
        printf("===read, tid : %ld, num : %d\n", pthread_self(), num);
        pthread_rwlock_unlock(&rwlock);
        usleep(100);
    }

    return NULL;
}

int main(int argc, char const *argv[])
{

    //pthread_mutex_init(&mutex, NULL);
    pthread_rwlock_init(&rwlock, NULL);
    //创建3个写线程，5个读线程
    pthread_t wtids[3], rtids[5];

    for (int i = 0; i < 3; i++){
        pthread_create(&wtids[i], NULL, writeNum, NULL);
    }

    for (int i = 0; i < 5; i++){
        pthread_create(&rtids[i], NULL, readNum, NULL);
    }


    //设置线程分离
    for (int i = 0; i < 3; i++){
        pthread_detach(wtids[i]);
    }

    for (int i = 0; i < 5; i++){
        pthread_detach(rtids[i]);
    }

    pthread_exit(NULL);
    //pthread_mutex_destroy(&mutex);
    printf("main线程已经结束\n");//这一行不会运行
    pthread_rwlock_destroy(&rwlock);
    return 0;
}
