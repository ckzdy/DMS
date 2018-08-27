// 定义进程入口函数
#include "logreader.h"
#include "consolesender.h"
#include "socketsender.h"
#include "client.h"
int main(void){
    try{
        LogReader reader("./wtmpx", "./logins.dat");
        //ConsoleSender sender;
        SocketSender sender("./fail.dat",7788,"127.0.0.1");
        Client client(reader, sender);
        client.dataMine();
    }
    catch(exception& ex){
        cout << ex.what() << endl;
        return -1;
    }
    return 0;
}

