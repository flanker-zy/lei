#include<iostream>
#include"dbo.h"
#include <cstring>
#include <cstdlib>
#include <string>

dbo::dbo(const char* path)
{
	int res = sqlite3_open(path, &this->db);
	if (res != SQLITE_OK)
	{
		std::cout << "fail";
	}
	
}

dbo::~dbo()
{
    sqlite3_close(this->db);
}

unsigned dbo::add_client(const char* username, const char* pswd, const char* type)
{
    // exclude existed username
    if (this->exist(username)) return 1;

    char* sql = new char[200];
    memset(sql, 0, sizeof(sql));
    char* str_type = new char[20];
   // /_itoa(type, str_type, 10);

    // INSERT INTO ClientInfo VALUES (<username>, <pswd>, <type>)
    sql = strcat(sql, "INSERT INTO user VALUES (");
    sql = strcat(strcat(strcat(sql, "'"), username), "',");
    sql = strcat(strcat(strcat(sql, "'"), pswd), "',");
    sql = strcat(strcat(strcat(sql, "'"), type), "')");
    std::cout << sql << std::endl;
    int result = sqlite3_exec(this->db, sql, NULL, NULL, NULL);

    delete[] sql;
    //delete[] str_type;
    if (result != SQLITE_OK) {
        return 1;
    }
    else {
        return 0;
    }
}

unsigned dbo::del_client(const char* username)
{
    if (!this->exist(username)) return 1;// doesn't exist

    char* sql = new char[200];
    memset(sql, 0, sizeof(sql));

    // DELETE FROM ClientInfo WHERE username = <username>
    sql = strcat(sql, "DELETE FROM user WHERE username = ");
    sql = strcat(strcat(strcat(sql, "'"), username), "'");

    int result = sqlite3_exec(this->db, sql, NULL, NULL, NULL);

    delete[] sql;
    if (result != SQLITE_OK) {
        return 1;
    }
    else {
        return 0;
    }
}

unsigned dbo::change_username(const char* username, const char* new_username)
{
    // doesn't exist
    if (!this->exist(username)) return 1;
    // exclude existed username
    if (this->exist(new_username)) return 2;

    char* sql = new char[200];
    memset(sql, 0, sizeof(sql));

    // UPDATE ClientInfo SET username = <new_username> where username = <username>
    sql = strcat(sql, "UPDATE user SET username = ");
    sql = strcat(strcat(strcat(sql, "'"), new_username), "'");
    const char* mid = " WHERE username = ";
    sql = strcat(sql, mid);
    sql = strcat(strcat(strcat(sql, "'"), username), "'");

    int result = sqlite3_exec(this->db, sql, NULL, NULL, NULL);

    delete[] sql;
    if (result != SQLITE_OK) {
        return 3;
    }
    else {
        return 0;
    }
}

unsigned dbo::change_pswd(const char* username, const char* new_pswd)
{
    // doesn't exist
    if (!this->exist(username)) return 1;

    char* sql = new char[200];
    memset(sql, 0, sizeof(sql));

    // UPDATE ClientInfo SET pswd = <new_pswd> where username = <username>
    sql = strcat(sql, "UPDATE user SET pswd = ");
    sql = strcat(strcat(strcat(sql, "'"), new_pswd), "'");
    const char* mid = " WHERE username = ";
    sql = strcat(sql, mid);
    sql = strcat(strcat(strcat(sql, "'"), username), "'");

    int result = sqlite3_exec(this->db, sql, NULL, NULL, NULL);

    delete[] sql;
    if (result != SQLITE_OK) {
        return 1;
    }
    else {
        return 0;
    }
}

bool dbo::exist(const char* username)
{
    char* sql = new char[200];
    memset(sql, 0, sizeof(sql));

    // SELECT type FROM ClientInfo WHERE username = <username>
    sql = strcat(sql, "SELECT type FROM user WHERE username = ");
    sql = strcat(strcat(strcat(sql, "'"), username), "'");

    int rows;
    char** azresult;
    int result = sqlite3_get_table(this->db, sql,
        &azresult, &rows, NULL, NULL);

    sqlite3_free_table(azresult);
    if (result != SQLITE_OK) {
        printf("Failed to give existence");
    }

    if (rows) return true;
    return false;
}

unsigned dbo::checktype(const char* username, const char* pswd) const
{
    char* sql = new char[200];
    memset(sql, 0, sizeof(sql));

    // SELECT type FROM ClientInfo WHERE username = <username> and pswd = <pswd>
    sql = strcat(sql, "SELECT type FROM user WHERE username = ");
    sql = strcat(strcat(strcat(sql, "'"), username), "'");
    sql = strcat(sql, " AND pswd = ");
    sql = strcat(strcat(strcat(sql, "'"), pswd), "'");
    std::cout << sql<<std::endl;
    char** azresult;
    int rows;
    int result = sqlite3_get_table(this->db, sql, &azresult,
        &rows, NULL, NULL);

    delete[] sql;
    if (result != SQLITE_OK) {
        printf("Failed to give check");
    }
    if (rows >= 1) {
        //for (int i = 0; i < 30; i++)
         //   std::cout << azresult[i];
        //    for (int j = 0; j < ; j++)
        //       std::cout << azresult[i][j];
       // return 1;
        return azresult[1][0] ;
        //return 123123;
    }
    else return 0;
    sqlite3_free_table(azresult);
	
}
static int SelectCallback(void* data, int col_count, char** col_values, char** col_names) {
    for (int i = 0; i < col_count; ++i) {
        if (col_values[i] == NULL) {
            continue;
        }

        std::cout << col_names[i] << " = " << col_values[i] << std::endl;
    }

    const char* seperator = reinterpret_cast<const char*>(data);
    std::cout << seperator << std::endl;

    return 0;
}
void dbo::SelectData(const char* table)
{
    sqlite3* db = NULL;
    std::string kDatabaseName = "C:\\Users\\48684\\source\\repos\\leiclass_sever\\leiclass_sever\\datebase\\lun.db";
    int rc = sqlite3_open(kDatabaseName.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cout << "Open " << kDatabaseName << " failed! Error msg: " << sqlite3_errmsg(db) << std::endl;
    }
    
    char* sql = new char[200];
    memset(sql, 0, sizeof(sql));
    sql = strcat(sql, "select * from ");
    sql = strcat(strcat(strcat(sql, "'"), table), "'");
    //const char* kSelectSql = "SELECT * FROM 'user';" ;
    const char* kSeperator = "================================";
    char* error_msg = NULL;

    rc = sqlite3_exec(db, sql, SelectCallback, (void*)kSeperator, &error_msg);
    if (rc == SQLITE_OK) {
        std::cout << "Select successfully!" << std::endl;
    }
    else {
        std::cout << "Select failed! Error msg: " << error_msg << std::endl;
        sqlite3_free(error_msg);
    }
    delete[] sql;

    sqlite3_close(db);
}



unsigned dbo::add_user(const char* id, const char* username, const char* pswd, const char* identity)
{
    //if (this->exist(username)) return 1;

    char* sql = new char[200];
    memset(sql, 0, sizeof(sql));
    char* str_type = new char[20];
    // /_itoa(type, str_type, 10);

     // INSERT INTO ClientInfo VALUES (<id>,<username>, <pswd>, <type>)
    sql = strcat(sql, "INSERT INTO user VALUES (");
    sql = strcat(strcat(strcat(sql, "'"), id), "',");
    sql = strcat(strcat(strcat(sql, "'"), username), "',");
    sql = strcat(strcat(strcat(sql, "'"), pswd), "',");
    sql = strcat(strcat(strcat(sql, "'"), identity), "')");
    std::cout << sql << std::endl;
    int result = sqlite3_exec(this->db, sql, NULL, NULL, NULL);

    delete[] sql;
    //delete[] str_type;
    if (result != SQLITE_OK) {
        return 1;
    }
    else {
        return 0;
    }
}

unsigned dbo::del_user(const char* username)
{
    //if (!this->exist(username)) return 1;// doesn't exist

    char* sql = new char[200];
    memset(sql, 0, sizeof(sql));

    // DELETE FROM ClientInfo WHERE username = <username>
    sql = strcat(sql, "DELETE FROM user WHERE username = ");
    sql = strcat(strcat(strcat(sql, "'"), username), "'");

    int result = sqlite3_exec(this->db, sql, NULL, NULL, NULL);

    delete[] sql;
    if (result != SQLITE_OK) {
        return 1;
    }
    else {
        return 0;
    }
}







