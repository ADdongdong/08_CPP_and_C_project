/*
    生产者消费者模型（粗略版本）
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>


//创建互斥量
pthread_mutex_t mutex;
//创建两个信号量
sem_t psem;
sem_t csem; 


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
        //调用wait
        sem_wait(&psem);
        //共享数据加锁
        pthread_mutex_lock(&mutex);

        //使用头插法加入新的结点
        struct Node * newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000;
        printf("tid : %ld, add node, num : %d\n", pthread_self(), head->num);

        //使用结束了，解锁
        pthread_mutex_unlock(&mutex);
        sem_post(&csem);//表示消费者有一个可以去消费
    }
    return NULL;
}

//定义消费者线程
void * customer(void *arg){
    while (1){
        sem_wait(&csem);
        //共享数据加锁
        pthread_mutex_lock(&mutex);
        //删除结点
        struct Node *tmp = head;
        //有数据
        head = head->next;
        printf("tid : %ld, del node, num : %d\n", pthread_self(), tmp->num);
        free(tmp);
        //使用结束了，解锁
        pthread_mutex_unlock(&mutex);
        
        sem_post(&psem);
    }

    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&mutex, NULL);
    sem_init(&psem, 0, 8);
    sem_init(&csem, 0, 0);

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

    pthread_exit(NULL);


    return 0;
}
