#include "Socket.h"
#include <iostream>
using namespace std;
int Socket::nofSockets_ = 0;

void Socket::Start()
{
    if (!nofSockets_) {
        WSADATA info;
        if (WSAStartup(MAKEWORD(2, 2), &info)) {
            throw "Could not start WSA";
        }
        else {
            cout << "启动环境成功\n";
        }
    }
    ++nofSockets_;
}

void Socket::End()
{
    WSACleanup();
}

Socket::Socket():s_(0)
{
    Start();
    s_ = socket(AF_INET, SOCK_STREAM, 0);

    if (s_ == INVALID_SOCKET) {
        throw "INVALID_SOCKET";
    }

    refCounter_ = new int(1);
}

Socket::Socket(SOCKET s):s_(s)
{
    Start();
    refCounter_ = new int(1);
}

Socket::~Socket()
{
    if (!--(*refCounter_)) {
        closesocket(s_);
        delete refCounter_;
    }

    --nofSockets_;
    if (!nofSockets_) End();
}

void Socket::SendLine(std::string s)
{
    s += "*MK*";
    send(s_, s.c_str(), s.length(),0);
}

string Socket::ReceiveLine() {
    
    std::string ret;
    while (1) {
        char r;
        switch (recv(s_, &r, 1, 0)) {
        case 0: // not connected anymore;
            // ... but last line sent
            // might not end in \n,
            // so return ret anyway.
            return ret;
        case -1:
            return "";
            //      if (errno == EAGAIN) {
            //        return ret;
            //      } else {
            //      // not connected anymore
            //      return "";
            //      }
        }
        ret += r;
        if (ret.length() >= 4 && ret.substr(ret.length() - 4) == "*MK*") {
            return ret.substr(0, ret.length() - 4);
        }
    }
}

SocketServer::SocketServer(int port, int connections, TypeSocket type)
{
    sockaddr_in sa;

    memset(&sa, 0, sizeof(sa));

    sa.sin_family = PF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.S_un.S_addr = INADDR_ANY;
    s_ = socket(AF_INET, SOCK_STREAM, 0);
    if (s_ == INVALID_SOCKET) {
        throw "INVALID_SOCKET";
    }

    if (type == NonBlockingSocket) {
        u_long arg = 1;
        ioctlsocket(s_, FIONBIO, &arg);
    }

    /* bind the socket to the internet address */
    if (bind(s_, (sockaddr*)&sa, sizeof(sockaddr_in)) == SOCKET_ERROR) {
        closesocket(s_);
        throw "INVALID_SOCKET";
    }
    else {
        cout << "创建端口成功\n";
    }
    listen(s_, connections);
}

Socket* SocketServer::Accept()
{
    sockaddr_in clientAddr = {};
    int nAddrLen = sizeof(sockaddr_in);
    SOCKET new_sock = accept(s_, (sockaddr*) & clientAddr, &nAddrLen);
    if (new_sock == INVALID_SOCKET) {
        int rc = WSAGetLastError();
        if (rc == WSAEWOULDBLOCK) {
            return 0; // non-blocking call, no request pending
        }
        else {
            throw "Invalid Socket";
        }
    }
    else {
        cout << "接收到客户端\n";
    }
    Socket* r = new Socket(new_sock);
    return r;
}
