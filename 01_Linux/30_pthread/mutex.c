#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int tickets = 100;

//创建互斥量,为了让所以线程都能访问，而且不被主线程结束所影响，
//所以，互斥量定义就放在全局
pthread_mutex_t mutex;

void * sellticket(void * arg){

    // 卖票
    while( 1){
        usleep(6000);
        //加锁
        pthread_mutex_lock(&mutex);
        if (tickets > 0){
            printf("%ld 号线程：正在卖 %d张门票\n", pthread_self(), tickets);
            tickets--;
        }else{
            //解锁
            pthread_mutex_unlock(&mutex);//当票卖完的时候，需要解锁，
            //不然程序会执行break直接退出while循环，就不会执行后面的解锁了
            //进程将阻塞
            break;
        }
        //解锁
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main(int argc, char const *argv[]){

    //初始化互斥量
    pthread_mutex_init(&mutex, NULL);

    //创建3个子线程
    pthread_t tid1, tid2, tid3;

    pthread_create(&tid1, NULL, sellticket, NULL);
    pthread_create(&tid2, NULL, sellticket, NULL);
    pthread_create(&tid3, NULL, sellticket, NULL);


    //回收子线程资源
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    //设置线程分离(detach和join用一个就行)
    // pthread_detach(tid1);
    // pthread_detach(tid2);
    // pthread_detach(tid3);

    pthread_exit(NULL);//退出主线程

    //释放互斥量资源
    pthread_mutex_destroy(&mutex);

    return 0;
}
