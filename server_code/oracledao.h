//声明Oracle数据访问对象类
#ifndef _ORACLEDAO_H
#define _ORACLEDAO_H
using namespace std;
#include "logdao.h"
// Oracle数据访问对象类
class OracleDao : public LogDao{
public:
    // 构造函数
    OracleDao(string const& username, string const& passwd)
	  throw (DBException);
    // 析构函数
    virtual ~OracleDao(void);
    // 插入
    virtual void insert(MLogRec const& log) throw (DBException);
};
#endif // _ORACLEDAO_H

