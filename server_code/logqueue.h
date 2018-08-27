// 声明日志队列
#ifndef _LOGQUEUE_H
#define _LOGQUEUE_H
#include <pthread.h>
#include <list>
using namespace std;
#include "data.h"
// 日志队列类
class LogQueue{
public:
    // 构造函数
    LogQueue(void);
    // 析构函数
    ~LogQueue(void);
    // 压入匹配日志记录
    LogQueue& operator << (MLogRec const& log);
    // 弹出匹配日志记录
    LogQueue& operator >> (MLogRec& log);
private:
    pthread_mutex_t m_mutex;    // 互斥锁
    pthread_cond_t m_noEmpty;   // 非空条件变量
    pthread_cond_t m_noFull;    // 非满条件变量
    list<MLogRec> m_logs;       // 匹配日志记录集
};
extern LogQueue g_logQueue;
#endif // _LOGQUEUE_H
