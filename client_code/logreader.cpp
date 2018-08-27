// 实现日志读取器类
#include <sys/stat.h>
#include <ctime>
#include <cstring>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream> 
using namespace std; 
#include "logreader.h"
// 构造函数
LogReader::LogReader(string const& logFile, string const& loginsFile) :
　　m_logFile(logFile), m_loginsFile(loginsFile){}
// 读取日志
list<MLogRec>& LogReader::readLog() throw (ClientException){
    cout << "读取日志开始..." << endl;
    // 备份日志文件
    backup();
    // 读取未匹配的登入文件
    readLoginsFile();
    // 读取备份文件
    readBackupFile();
    // 匹配
    match();
    // 保存登入文件
    saveLoginsFile();
    cout << "读取日志完成。" << endl;
    return m_logs;
}
// 备份文件
void LogReader::backup() throw (BackupException){
    cout << "备份文件开始..." << endl;
    // 按照固定格式生成备份文件名
    time_t now  = time(NULL);
    tm* local = localtime(&now);
    ostringstream oss;
    oss << m_logFile << '.' << setfill('0')
        << setw(4) << local->tm_year + 1900
        << setw(2) << local->tm_mon + 1
        << setw(2) << local->tm_mday
        << setw(2) << local->tm_hour
        << setw(2) << local->tm_min
        << setw(2) << local->tm_sec;
    m_backupFile = oss.str();

    cout << "备份文件名：" << m_backupFile << endl;

    // 备份文件
    string cmd = string("cp ") + m_logFile + " " + m_backupFile;

    cout << "复制文件的命令：" << cmd << endl;

    int status = system(cmd.c_str());
    if(status==-1){
        throw BackupException("备份文件错误");
    }

    // 清空当前日志文件
    int fd = open(m_logFile.c_str(), O_CREAT|O_WRONLY|O_TRUNC);
    if(fd==-1)
        throw BackupException("清空日志文件错误");
    close(fd);
    cout << "备份文件完成。" << endl;
}
// 读取未匹配的登入日志文件
void LogReader::readLoginsFile() throw (ReadException){
    cout << "读取登入日志文件开始..." << endl;
    ifstream ifs(m_loginsFile.c_str(), ios::binary);
    if(ifs){
        LogRec log;
        while(ifs.read((char*)&log, sizeof(log)))
            m_logins.push_back(log);
        if(!ifs.eof())
            throw ReadException("读取登入文件错误");
        ifs.close();
        unlink(m_loginsFile.c_str());
    }

    cout << "读取登入文件记录：" << m_logins.size() << endl;

    cout << "读取登入日志文件完成。" << endl;
}
// 读取备份文件
void LogReader::readBackupFile() throw (ReadException){
    cout << "读取备份文件开始..." << endl;
    // 打开备份文件
    ifstream ifs(m_backupFile.c_str(),ios::binary);
    if(!ifs)
        throw ReadException("备份文件无法打开");
    // 计算记录条数
    struct stat st;
    if(stat(m_backupFile.c_str(), &st) == -1)
        throw ReadException("无法获取备份文件大小");
    int records = st.st_size / 372;   // 每条记录372字节
    // 逐条读取记录
    for(int I = 0; I < records; i++){
        // 登录名
        ifs.seekg(i*372, ios::beg);
        char logname[32];
        ifs.read(logname,sizeof(logname));
        // 登录进程ID
        ifs.seekg(36,ios::cur);
        pid_t pid;
        ifs.read((char*)&pid, sizeof(pid));
        pid = ntohl(pid); // 网络序转换成主机序
        // 登录类型
        short type;
        ifs.read((char*)&type, sizeof(type));
        type = ntohs(type);
        // 登录时间
        ifs.seekg(6, ios::cur);
        long logtime;
        ifs.read((char*)&logtime, sizeof(logtime));
        logtime = ntohl(logtime);
        // ip地址的长度
        ifs.seekg(28, ios::cur);
        short len;
        ifs.read((char*)&len, sizeof(len));
        len = ntohs(len);
        // ip地址
        char logip[len+1];
        ifs.read(logip, len);
        logip[len]='\0';

        cout << logname << ',' << pid << ',' << type << ','
             << logtime << ',' << len << ',' << logip << endl;

        //以.开头的用户名不属于有效用户名
        if(logname[0]!='.'){
            LogRec log;
            strcpy(log.logname, logname);
            strcpy(log.logip, logip);
            log.pid = pid;
            log.logtime = logtime;
            if(type==7) // 登入记录
                m_logins.push_back(log);
            else if(type == 8)  // 登出记录
                m_logouts.push_back(log);
        }
    }

    cout << "登入记录：" << m_logins.size() << endl;
    cout << "登出记录：" << m_logouts.size() << endl;

    cout << "读取备份文件完成。" << endl;
}
// 匹配
void LogReader::match(){
    cout << "匹配登入登出开始..." << endl;
    // 对登出记录集中的每一条记录进行遍历...
    for(list<LogRec>::iterator oit = m_logouts.begin();
            oit != m_logouts.end(); oit++){
        // 在登入记录集中进行匹配
        for(list<LogRec>::iterator iit = m_logins.begin();
                iit != m_logins.end(); iit++){
            if(!strcmp(oit->logname, iit->logname)&&
               !strcmp(oit->logip, iit->logip)&&
               oit->pid == iit->pid){// 若匹配
                MLogRec log;
                strcpy(log.logname, oit->logname);
                strcpy(log.logip, oit->logip);
                log.pid = oit->pid;
                log.logintime = iit->logtime;
                log.logouttime = oit->logtime;
                log.durations = log.logouttime - log.logintime;
                m_logs.push_back(log);
                // 删除匹配成功的登入记录
                m_logins.erase(iit);
                break;
            }
        }
    }

    cout << "匹配日志记录:" << m_logs.size() << endl;

    cout << "匹配登入登出完成。" << endl;
}
// 保存登入日志文件
void LogReader::saveLoginsFile() throw (SaveException){
    cout << "保存登入日志文件开始..." << endl;
    if(!m_logins.empty()){
        ofstream ofs(m_loginsFile.c_str(), ios::binary);
        if(!ofs)
            throw SaveException("登入文件无法打开");
        while(!m_logins.empty()){
            ofs.write((char const*)&m_logins.front(), sizeof(LogRec));
            m_logins.pop_front();
        }
        ofs.close();
    }
    cout << "保存登入日志文件完成。" << endl;
}

