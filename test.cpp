#include<iostream>
#include"dbo.h"
#include <cstring>
#include<cstring>
//const char DBPATH[20] = ".\\datebase\\lei.db";

using namespace std;

int main()
{
	dbo db = dbo();
	int a;
	//db.change_username("wang", "zhao");
	//db.change_pswd("zhao", "111111");
	//db.SelectData();
	//cout<<db.add_client("uoiuoiuoi", "123456", "1");
	//cout<<db.del_client("uoiuoiuoi");
	//std::cout<<db.checktype("pan", "123456");
	//db.SelectData("paper");
	//db.add_user("9", "ff", "009", "2");
	//db.del_user("ff");
	//db.SelectData("user");
	
	while (1)
	{
		cout << "please chose one function" << endl;
		cout << "1.add user" << endl;
		cout << "2.del user" << endl;
		cout << "3.just select user" << endl;
		cout << "4.quit" << endl;
		cin >> a;
		if (a == 1)
		{
			cout << "please input data" << endl;
			
			string id ;
			string  username;
			string  pswd;
			string  identity;
			cout << "id:";
			cin >> id;
			cout << "username:";
			cin >> username;
			cout << "pswd:";
			cin >> pswd;
			cout << "identity:";
			cin >> identity;
			cout << endl;
			db.add_user(id.c_str(), username.c_str(), pswd.c_str(), identity.c_str());
			db.SelectData("user");
		}
		if (a == 2)
		{
			cout << "please input username" << endl;
			string username;
			cout << "username:";
			cin >> username;
			db.del_user(username.c_str());
			db.SelectData("user");
		}
		if (a == 3)
		{
			db.SelectData("user");
		}
		if (a == 4)
		{
			cout << "bye" << endl;
			break;
		}
		
	}
}