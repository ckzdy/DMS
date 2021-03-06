﻿// 声明客户机类
#ifndef _CLIENT_H
#define _CLIENT_H
#include "logreader.h"
#include "logsender.h"
// 客户机类
class Client{
public:
    // 构造函数
    Client(LogReader& reader, LogSender& sender);
    // 数据采集
    void dataMine() throw (ClientException);
private:
    LogReader& m_reader;    // 日志读取器
    LogSender& m_sender;    // 日志发送器
};
#endif // _CLIENT_H

