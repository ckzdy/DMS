// 声明日志读取器类
#ifndef _LOGREADER_H
#define _LOGREADER_H
#include <list>
#include "data.h"
#include "except.h"
// 日志读取器类
class LogReader{
public:
    // 构造函数
    LogReader(string const& logFile, string const& loginsFile);
    // 读取日志
    list<MLogRec>& readLog() throw (ClientException);
private:
    // 备份文件
    void backup() throw (BackupException);
    // 读取登入日志文件
    void readLoginsFile() throw (ReadException);
    // 读取备份文件
    void readBackupFile() throw (ReadException);
    // 匹配
    void match();
    // 保存登入日志文件
    void saveLoginsFile() throw (SaveException);

    string m_logFile;       // 登录文件
    string m_loginsFile;     // 登入文件
    string m_backupFile;    // 备份文件
    list<LogRec> m_logins;  // 登入日志记录集
    list<LogRec> m_logouts; // 登出日志记录集
    list<MLogRec> m_logs;   // 匹配日志记录集
};
#endif // _LOGREADER_H

