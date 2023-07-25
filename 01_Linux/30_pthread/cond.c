/*
    生产者消费者模型（粗略版本）
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


//创建互斥量
pthread_mutex_t mutex;

//创建条件变量
pthread_cond_t cond;

//定义数据结构体
struct Node{
    int num;
    struct Node *next; 
};

//定义头结点
struct Node * head = NULL;

//定义生产者线程
void * producer(void *arg){
    //不断创建新的结点添加到链表中
    while (1){
        //共享数据加锁
        pthread_mutex_lock(&mutex);

        //使用头插法加入新的结点
        struct Node * newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000;
        printf("add node, num : %d, tid : %ld \n", newNode->num, pthread_self());

        //只要生产了一个，就同时消费者
        pthread_cond_signal(&cond);
        //使用结束了，解锁
        pthread_mutex_unlock(&mutex);
        usleep(1000);
    }
    return NULL;
}

//定义消费者线程
void * customer(void *arg){
    while (1){
        //共享数据加锁
        pthread_mutex_lock(&mutex);
        //删除结点
        struct Node *tmp = head;
        //判断容器中是否有数据
        if (head != NULL){
            //有数据
            head = head->next;
            printf("del node, num : %d, tid : %ld\n", tmp->num, pthread_self());
            free(tmp);
            //使用结束了，解锁
            pthread_mutex_unlock(&mutex);
            usleep(1000) ;
        } else {
            //没有数据需要等待(只要生产者执行到pthread_cond_signal(&cond);)
            //下面的代码就会结束等待
            //当这个函数调用阻塞的时候，会对指定的互斥锁进行解锁
            //当不阻塞的时候，会重新加锁，然后继续向下执行
            pthread_cond_wait(&cond, &mutex);
            //使用结束了，解锁
            pthread_mutex_unlock(&mutex);
        } 
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // 创建5个生产者线程，和5个消费者线程
    pthread_t ptids[5], ctids[5];

    for (int i = 0; i < 5; i++){
        pthread_create(&ptids[i], NULL, producer, NULL);
        pthread_create(&ctids[i], NULL, customer, NULL);
    }

    for (int i = 0; i < 5; i++){
        pthread_detach(ptids[i]);
        pthread_detach(ctids[i]);
    }

    while (1){
        sleep(10);
    }

    while (1){
        sleep(10);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    pthread_exit(NULL);


    return 0;
}
