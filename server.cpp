#include"server.h"
#include<vector>
#include<string>
#include"dbo.h"
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"sqlite3.lib")

using namespace std;

//vector<User*> Class_Members;

Server::Server(const int port, const int maxnum) :
	SocketServer(port, maxnum) {
	;
}

Server::~Server()
{
	;
}



//创建端口、等待连接、发送身份
void Server::accept()
{
	dbo db = dbo();
	//dbo::OpenDB();
	Socket* s = this->Accept();
	unsigned asktimes = 1;
	string name = s->ReceiveLine();
	string pswd = s->ReceiveLine();
	//char type = 't';
	//db.add_client(name.c_str(), pswd.c_str(), type);
	unsigned type = db.checktype(name.c_str(), pswd.c_str());
	if (type == 0) {
		s->SendLine("0");
	}
	else {
		s->SendLine(to_string(type-48));
		
	}
	
	//sqlite3_close(db);
	//unsigned the_type =
	//	db.checktype(name.c_str(), pswd.c_str());
	//s->SendLine(to_string(the_type));
	//SelectData();
	//CheckType(name.c_str(), pswd.c_str());
	//CheckType(name.c_str(),pswd.c_str());
	//s->SendLine(CheckType(name.c_str(), pswd.c_str()));
	
	//unsigned ret;
	//_beginthreadex(0, 0, this->Answer, (void*)s, 0, &ret);
}
/*
unsigned __stdcall Server::Answer(void* x)
{
	return 0;
}*/
