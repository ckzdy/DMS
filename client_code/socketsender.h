//声明网络发送器类
#ifndef _SOCKETSENDER_H
#define _SOCKETSENDER_H
using namespace std;
#include "logsender.h"
// 日志发送器接口
class SocketSender : public LogSender{
public:
    // 构造函数
    SocketSender(string const& failFile, short port, string const& ip = "127.0.0.1");
    // 发送日志
    void sendLog(list<MLogRec>& logs) throw (ClientException);
private:
    // 读取发送失败文件
    void readFailFile(list<MLogRec>& logs) throw (ReadException);
    // 连接服务器
    void connectServer() throw (SocketException);
    // 发送数据
    void sendData(list<MLogRec>& logs) throw (SendException);
    // 保存发送失败文件
    void saveFailFile(list<MLogRec>& logs) throw (SaveException);

    string m_failFile;  // 发送失败文件
    short m_port;       // 服务器端口号
    string m_ip;        // 服务器ip
    int m_sockfd;       // 套接字描述符
};
#endif //_SENDERSENDER_H

