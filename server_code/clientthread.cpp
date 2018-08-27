// 实现客户线程类
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;
#include "clientthread.h"
#include "logqueue.h"
// 构造函数
ClientThread::ClientThread(int connfd):m_connfd(connfd){}
// 线程处理
void ClientThread::run(void){
    unsigned int logs;
    MLogRec log;
    for(logs=0;;logs++){
        ssize_t rlen;//实际接收的字节数
        //一次可能无法将一条数据完全接收，以下循环是为了应对这一点
        for(size_t len = sizeof(log);len;len-=rlen){
            if((rlen = recv(m_connfd,(char*)&log+(sizeof(log)-len),len,0))<=0)
                goto escape;
        }
        log.pid = ntohl(log.pid);
        log.logintime = ntohl(log.logintime);
        log.logouttime = ntohl(log.logouttime);
        log.durations = ntohl(log.durations);
        g_logQueue << log;
    }
escape:
    cout << "接收到" << logs << "条匹配日志记录" << endl;
    close(m_connfd);
    delete this;  // 线程结束自毁
}

