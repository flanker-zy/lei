#include"db.h"

static void OpenDB() {
	sqlite3* db = NULL;

	// The database is opened for reading and writing, and is created if it does not already exist. 
	// 如果数据库存在直接打开，如果不存在则创建之后再打开。打开方式为可读可写。
	int rc = sqlite3_open("test.db", &db);
	if (rc != SQLITE_OK) {
		int error_code = sqlite3_errcode(db);
		const char* error_msg = sqlite3_errmsg(db);

		std::cout << "Open failed!" << std::endl;
		std::cout << "Error code: " << error_code << std::endl;
		std::cout << "Error message: " << error_msg << std::endl;
		return;
	}

	std::cout << "Open successfully!" << std::endl;

	sqlite3_close(db);
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

static void SelectData() {
	sqlite3* db = NULL;

	int rc = sqlite3_open("test.db", &db);
	if (rc != SQLITE_OK) {
		std::cout << "Open " << "test.db" << " failed! Error msg: " << sqlite3_errmsg(db) << std::endl;
	}

	const char* kSelectSql = "SELECT * FROM student;";
	const char* kSeperator = "================================";
	char* error_msg = NULL;

	rc = sqlite3_exec(db, kSelectSql, SelectCallback, (void*)kSeperator, &error_msg);
	if (rc == SQLITE_OK) {
		std::cout << "Select successfully!" << std::endl;
	}
	else {
		std::cout << "Select failed! Error msg: " << error_msg << std::endl;
		sqlite3_free(error_msg);
	}

	sqlite3_close(db);
}

 int CheckType(const char* username,const char* pswd) {
	sqlite3* db = NULL;

	int rc = sqlite3_open("test.db", &db);
	if (rc != SQLITE_OK) {
		std::cout << "Open " << "test.db" << " failed! Error msg: " << sqlite3_errmsg(db) << std::endl;
	}

	char* sql = new char[200];
	memset(sql, 0, sizeof(sql));

	// SELECT type FROM ClientInfo WHERE username = <username> and pswd = <pswd>
	sql = strcat(sql, "SELECT type FROM ClientInfo WHERE username = ");
	sql = strcat(strcat(strcat(sql, "'"), username), "'");
	sql = strcat(sql, " AND pswd = ");
	sql = strcat(strcat(strcat(sql, "'"), pswd), "'");

	char** azresult;
	int rows = 0;
	//int result = sqlite3_get_table(db, sql, &azresult,
	//	&rows, NULL, NULL);
	int result = sqlite3_exec(db, sql, SelectCallback, 0, 0);
	delete[] sql;
	if (result != SQLITE_OK) {
		printf("Failed to give check");
	}
	if (rows >= 1) {
		return 1;
	}
	else return 0;
	sqlite3_free_table(azresult);
}