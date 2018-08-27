// 实现客户机类
using namespace std;
#include "client.h"
// 构造函数
Client::Client(LogReader& reader, LogSender& sender) :
　　m_reader(reader), m_sender(sender){};
// 数据采集
void Client::dataMine() throw (ClientException){
    cout << "数据采集开始..." << endl;
    m_sender.sendLog(m_reader.readLog());
    cout << "数据采集完成。" << endl;
}

