// 实现服务器套接字类
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cstring>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
using namespace std;
#include "serversocket.h"
#include "clientthread.h"
// 构造函数
ServerSocket::ServerSocket(short port, string const& ip /*=""*/)
    throw (ServerException){
    cout << "初始化服务器开始..." << endl;
    // 创建套接字
    if((m_sockfd = socket(PF_INET, SOCK_STREAM,0)) == -1){
        throw SocketException(strerror(errno));
    }
    // 设置套接字
    int on = -1;
    if(setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &on,sizeof(on)) == -1){
        close(m_sockfd);
        throw SocketException(strerror(errno));
    }
    // 绑定套接字
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = ip.empty() ? INADDR_ANY : inet_addr(ip.c_str());
    if(bind(m_sockfd,(sockaddr*)&addr, sizeof(addr)) == -1){
        close(m_sockfd);
        throw SocketException(strerror(errno));
    }
    // 侦听套接字
    if(listen(m_sockfd, 1024) == -1){
        close(m_sockfd);
        throw SocketException(strerror(errno));
    }
    cout << "初始化服务器完成。" << endl;
}
// 等待接收客户机连接
void ServerSocket::acceptClient()throw (SocketException){
    // 循环
    for(;;){
        cout << "等待客户机连接..." << endl;
        sockaddr_in addrcli;
        socklen_t addrlen = sizeof(addrcli);
        // 每接受一个客户机连接请求...
        int connfd = accept(m_sockfd, (sockaddr*)&addrcli, &addrlen);
        if(connfd == -1){
            close(m_sockfd);
            throw SocketException(strerror(errno));
        }
        // 创建一个客户线程为其服务
        (new ClientThread(connfd))->start();
    }
}

