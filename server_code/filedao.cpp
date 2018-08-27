//实现文件数据访问对象类
#include <iostream>
using namespace std;
#include "filedao.h"
// 构造函数
FileDao::FileDao(string const& path) throw (DBException){
    cout << "建立数据库连接开始..." << endl;
    m_ofs.open(path.c_str(), ios::app);
    if(!m_ofs)
        throw DBException("数据库文件无法打开");
    cout << "建立数据库连接完成。" << endl;
}
// 析构函数
FileDao::~FileDao(void){
    cout << "关闭数据库连接开始..." << endl;    
    m_ofs.close();
    cout << "关闭数据库连接完成。" << endl;
}
// 插入
void FileDao::insert(MLogRec const& log) throw (){
    cout << "插入数据开始..." << endl;
    m_ofs << log << endl;
    cout << "插入数据完成。" << endl;
}

