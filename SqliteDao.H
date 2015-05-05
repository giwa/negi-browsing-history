#pragma once

#include <sqlite3.h>


class SqliteDao
{
	private:
		sqlite3 *conn_;
		sqlite3_stmt *res_;
		int rc_;
		
		int rc2_;
		sqlite3 *conn2_;
		sqlite3_stmt *res2_;

	public:
		SqliteDao();
		int Connect(const string& dbname);
		sqlite3_stmt* ExecSql(const string &sql);
		void ExecBatchSql(const string &sql, int limit=2);
		void CreateTableFromFile(const string& file_path);

		int ConnectMemory();
		sqlite3_stmt* ExecSqlMemory(const string &sql);
		void ExecBatchSqlMemory(const string &sql, int limit=2);
		void CreateTableFromFileMemory(const string& file_path);

		void EscapeSingleQuote(string &target);
		sqlite3* GetConnMemory(){return conn_;}

		sqlite3* GetConn(){return conn2_;}

};
