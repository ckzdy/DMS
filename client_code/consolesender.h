//声明控制台发送器类
#ifndef _CONSOLESENDER_H
#define _CONSOLESENDER_H
using namespace std;
#include "logsender.h"
// 控制台发送器类
class ConsoleSender : public LogSender{
public:
    // 发送日志
    void sendLog(list<MLogRec>& logs) throw();
};
#endif //_CONSOLESENDER_H
