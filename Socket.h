#pragma once
#include<WinSock2.h>
#include<Windows.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")
enum TypeSocket { BlockingSocket, NonBlockingSocket };
class Socket
{
public:
	Socket();
	Socket(SOCKET s);
	~Socket();
	void SendLine(std::string);
	std::string ReceiveLine();
protected:
	friend class SocketServer;
	SOCKET s_;//套接字
	int* refCounter_;
private:
	//启动环境
	static void Start();
	//结束环境
	static void End();
	//是否启动过环境
	static int  nofSockets_;
};

class SocketServer :public Socket {
public:
	//创建端口
	SocketServer(int port, int connections, TypeSocket type = BlockingSocket);//创建服务器
	//等待连接
	Socket* Accept();
};