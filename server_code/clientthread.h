// 声明客户线程类
#ifndef _CLINETTHREAD_H
#define _CLIENTTHREAD_H
#include "logthread.h"
// 客户线程类
class ClientThread : public LogThread{
public:
    // 构造函数
    ClientThread(int connfd);
    // 线程处理
    virtual void run(void);
private:
    int m_connfd;   // 通信套接字
};
#endif // _CLIENTTHREAD_H
