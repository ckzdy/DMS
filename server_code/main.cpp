// 定义进程入口函数
#include <iostream>
using namespace std;
#include "filedao.h"
#include "oracledao.h"
#include "server.h"
int main(void){
    try{
        FileDao dao("./dms.db");
    	//OracleDao dao("system","open123");      
        Server server(dao, 7788, "127.0.0.1");
        server.dataMine();
    }
    catch(exception& ex){
        cout << ex.what() << endl;
        return -1;
    }
    return 0;
}

