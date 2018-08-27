// 定义异常
#ifndef _EXCEPT_H
#define _EXCEPT_H
#include <string>
using namespace std;
// 客户机异常类
class ClientException : public exception{
public:
    ClientException(void) : m_msg("客户机异常!"){}
    ClientException(string const& msg) : m_msg("客户机异常:"){
        m_msg += msg;
        m_msg +="!";
    }
    ~ClientException(void) throw(){}
    char const* what()const throw(){
        return m_msg.c_str();
    }
private:
    string m_msg;   // 异常信息
};
// 备份异常类
class BackupException : public ClientException{
public:
    BackupException(void) : ClientException("备份异常"){}
    BackupException(string const& msg) : ClientException(msg){}
};
// 网络异常类
class SocketException : public ClientException{
public:
    SocketException(void) : ClientException("网络异常"){}
    SocketException(string const& msg) : ClientException(msg){}
};
// 读取异常类
class ReadException : public ClientException{
public:
    ReadException(void) : ClientException("读取异常"){}
    ReadException(string const& msg) : ClientException(msg){}
};
// 发送异常类
class SendException : public ClientException{
public:
    SendException(void) : ClientException("发送异常"){}
    SendException(string const& msg) : ClientException(msg){}
};
// 保存异常类
class SaveException : public ClientException{
public:
    SaveException(void) : ClientException("保存异常"){}
    SaveException(string const& msg) : ClientException(msg){}
};
#endif // _EXCEPT_H

