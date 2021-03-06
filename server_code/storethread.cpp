﻿// 实现存储线程类
#include <iostream>
using namespace std;
#include "storethread.h"
#include "logqueue.h"
// 构造函数
StoreThread::StoreThread(LogDao& dao) : m_dao(dao){}
// 线程处理
void StoreThread::run(void){
    MLogRec log;
    for(;;){
        // 每弹出一条数据
        g_logQueue >> log;
        //插入到数据库
        try{
            m_dao.insert(log);
        }
        catch(DBException& ex){
            cout << ex.what() << endl;
        }
    }
}

