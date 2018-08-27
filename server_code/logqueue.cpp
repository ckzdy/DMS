// 实现日志队列
#include <iostream>
using namespace std;
#include "logqueue.h"
#define MAX_LOGS 1024*1024
LogQueue g_logQueue;
// 构造函数
LogQueue::LogQueue(void){
    pthread_mutex_init(&m_mutex, 0);
    pthread_cond_init(&m_noEmpty, 0);
    pthread_cond_init(&m_noFull, 0);
}
// 析构函数
LogQueue::~LogQueue(void){
    pthread_cond_destroy(&m_noFull);
    pthread_cond_destroy(&m_noEmpty);
    pthread_mutex_destroy(&m_mutex);
}
// 压入匹配日志记录
LogQueue& LogQueue::operator << (MLogRec const& log){
    cout << "压入匹配日志记录开始..." << endl;
    pthread_mutex_lock(&m_mutex);
    //在此案例中，不会进入while循环
    while(m_logs.size()>=MAX_LOGS){
        cout << "等待日志记录非满..." << endl;
        pthread_cond_wait(&m_noFull,&m_mutex);
    }
    m_logs.push_back(log);
    pthread_cond_signal(&m_noEmpty);
    pthread_mutex_unlock(&m_mutex);
    cout << "压入匹配日志记录完成。" << endl;
    return *this;
}
// 弹出匹配日志记录
LogQueue& LogQueue::operator >> (MLogRec& log){
    cout << "弹出匹配日志记录开始..." << endl;
    pthread_mutex_lock(&m_mutex);
    while(m_logs.empty()){
        cout << "等待日志记录非空..." << endl;
        pthread_cond_wait(&m_noEmpty,&m_mutex);
    }
    log = m_logs.front();
    m_logs.pop_front();
    pthread_cond_signal(&m_noFull);
    pthread_mutex_unlock(&m_mutex);
    cout << "弹出匹配日志记录完成。" << endl;
    return *this;
}

