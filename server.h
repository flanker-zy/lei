#pragma once
#include"Socket.h"
#include <process.h>
class Server : public SocketServer {
public:
    //����������
    Server(const int port, const int maxnum);
    ~Server();
    Server(const Server&) = delete;
    Server& operator = (const Server&) = delete;
    //�ȴ��ͻ�������
    void accept();
    //static unsigned __stdcall Answer(void* x);
    //static dboperator db;
};