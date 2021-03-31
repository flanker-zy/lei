#pragma once
#include"Socket.h"
#include <process.h>
class Server : public SocketServer {
public:
    //构建服务器
    Server(const int port, const int maxnum);
    ~Server();
    Server(const Server&) = delete;
    Server& operator = (const Server&) = delete;
    //等待客户端连接
    void accept();
    //static unsigned __stdcall Answer(void* x);
    //static dboperator db;
};