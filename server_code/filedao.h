//声明文件数据访问对象类
#ifndef _FILEDAO_H
#define _FILEDAO_H
#include <fstream>
using namespace std;
#include "logdao.h"
// 文件数据访问对象类
class FileDao : public LogDao{
public:
    // 构造函数
    FileDao(string const& path) throw (DBException);
    // 析构函数
    virtual ~FileDao(void);
    // 插入
    virtual void insert(MLogRec const& log) throw ();
private:
    ofstream m_ofs;
};
#endif // _LOGDAO_H
