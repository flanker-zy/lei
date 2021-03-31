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
	SOCKET s_;//�׽���
	int* refCounter_;
private:
	//��������
	static void Start();
	//��������
	static void End();
	//�Ƿ�����������
	static int  nofSockets_;
};

class SocketServer :public Socket {
public:
	//�����˿�
	SocketServer(int port, int connections, TypeSocket type = BlockingSocket);//����������
	//�ȴ�����
	Socket* Accept();
};