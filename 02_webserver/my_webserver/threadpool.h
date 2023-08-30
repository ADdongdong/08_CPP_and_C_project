#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <cstdio>
#include <pthread.h>
#include <list>
#include <exception>
#include "locker.h"

// 线程池类，定义成模板类是为了代码的复用，模板参数T就是任务类
template<typename T>
class threadpool {
private:
    //线程的数量
    int m_thread_number;
    // 线程池数组，大小为m_thread_number
    pthread_t * m_threads;
    // 请求队列中最多允许的，等待处理的请求数量
    int m_max_request;
    // 请求队列
    std::list<T*> m_wrokqueue;
    // 互斥锁
    locker m_queuelocker;
    // 信号量：用来判断是否有任务需要吃力
    sem m_queuestat;
    // 是否结束线程
    bool m_stop;

    // 定义静态成员函数
    // 在静态函数中只能访问静态成员static,不能访问普通成员
    static void* worker(void * arg);

    //定义线程池启动函数
    void run();
public:
    threadpool(int thread_number = 8, int max_request = 10000);
    ~threadpool();
    bool append(T* request);
};

template<typename T>
threadpool<T>::threadpool(int thread_number, int max_request):
        m_thread_number(thread_number),m_max_request(max_request),
        m_stop(false), m_threads(NULL) {
        
    if((thread_number <= 0) || (max_request <= 0)){
        throw std::exception();
    }

    m_threads = new pthread_t[m_thread_number];
    if (!m_threads) {
        throw std::exception();
    }

    //创建thread_number个线程，并将他们设置为线程脱离
    //分离一个线程。被分离的线程会在终止的时候，会自动释放资源返回给系统。
    for (int i = 0; i < thread_number; i++) {
        printf("create the %dth thread\n", i);

        //这里，第四个参数串this，因为,worker函数为类中的static函数
        //static成员函数是不能使用类中的普通成员的，但是我们又要使用普通成员
        //所以，给worker这个static成员函数传入的参数就是this，
        //即指向调用这个函数的对象
        //这样，就可以通this指针来访问这个函数中的所有对象了
        if( pthread_create(m_threads + i, NULL, worker, this) != 0) { 
            delete[] m_threads;
            throw std::exception();
        }

        if(pthread_detach(m_threads[i])) {
            delete[] m_threads;
            throw std::exception();
        }
    }
}

template<typename T>
threadpool<T>::~threadpool() {
    delete[] m_threads;
    m_stop = true;
}

template<typename T>
bool threadpool<T>::append(T* request) {
    m_queuelocker.lock();

    if(m_wrokqueue.size() > m_max_request) {
        m_queuelocker.unlock();
        return false;
    }

    //可以往里面添加
    m_wrokqueue.push_back(request);
    m_queuelocker.unlock();
    m_queuestat.post();
    return true;
}

template<typename T>
void* threadpool<T>::worker(void *arg) {
    threadpool * pool = (threadpool *)arg;
    pool->run();

    return pool;
}

template<typename T>
void threadpool<T>::run() {
    while(!m_stop) {
        //对信号量加锁，调用一次，对信号量-1，如果值为0，就阻塞
        m_queuestat.wait();
        m_queuelocker.lock();
        if (m_wrokqueue.empty()){
            m_queuelocker.unlock();
            continue;
        }

        T* request = m_wrokqueue.front();
        m_wrokqueue.pop_front();
        m_queuelocker.unlock();

        if (!request) {
            continue;
        }

        request->process();
    }
}

#endif