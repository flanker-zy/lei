
#ifndef	 _db_
#define  _db_
#include<iostream>
#include"sqlite/sqlite3.h"
#pragma comment(lib,"sqlite3.lib")
const char DBPATH[100] = "C:\\Users\\48684\\source\\repos\\leiclass_sever\\leiclass_sever\\datebase\\lun.db";
//const char DBPATH[20] = ".\\datebase\\lei.db";

class dbo {
private:
	sqlite3* db;
    bool exist(const char* username);
public:
	dbo(const char* path = DBPATH);
	~dbo();
    
	//bool exist(const char* username);
    unsigned add_client(const char* username,
        const char* pswd,
        const char* type);
    unsigned del_client(const char* username);
    unsigned change_username(const char* username,
        const char* new_username);
    unsigned change_pswd(const char* username,
        const char* new_pswd);
    unsigned checktype(const char* username, const char* pswd) const;
    void SelectData(const char* table);
    unsigned add_user(const char* id, const char* username, const char* pswd, const char* identity);
    
    unsigned del_user(const char* username);
};
//static void OpenDB();
//static int SelectCallback();
//static int CheckType(const char* username, const char* pswd);

#endif