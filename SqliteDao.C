#include "Include.H"
#include "Global.H"
#include "Util.H"

#include "SqliteDao.H"

SqliteDao::SqliteDao(){
	return;
}

// Connect to a Sqlite DB
int SqliteDao::Connect(const string& dbname){
	rc2_ = sqlite3_open(dbname.c_str(), &conn2_);
	if(rc2_){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(conn2_));
		exit(0);
	}
	return 1;
}

// Connect to a in memory Sqlite DB
int SqliteDao::ConnectMemory(){
	rc_ = sqlite3_open(":memory:", &conn_);
	if(rc_){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(conn_));
		exit(0);
	}
	return 1;
}
// Execute SQL
//	e.g
//	statement = sqlite->Execsql(sql);
//	while(sqlite3_step(statement) == SQLITE_ROW){
//		int id = sqlite3_column_int(statement, 0);
//		const unsigned char * name = sqlite3_column_text(statement, 1);
//		...
//	}
//	release sqlite3_stmt object
//	sqlite3_finalize(statement);
sqlite3_stmt* SqliteDao::ExecSql(const string &sql){

	//Compile SQL
	sqlite3_prepare_v2(conn2_, sql.c_str(), -1, &res2_, NULL);
	// Excute all SQL 
//	sqlite3_step(res_);
	return res2_;
}

sqlite3_stmt* SqliteDao::ExecSqlMemory(const string &sql){

	//Compile SQL
	sqlite3_prepare_v2(conn_, sql.c_str(), -1, &res_, NULL);
	// Excute all SQL 
//	sqlite3_step(res_);
	return res_;
}

//Execute write only sql
void SqliteDao::ExecBatchSql(const string &sql, int limit){
	sqlite3_stmt *statement;
	int status=0;
	// Compile SQL
	sqlite3_prepare_v2(conn2_, sql.c_str(), -1, &statement, NULL);
	// Excute all SQL 
	int loop=0;
	while (1){
		status = sqlite3_step(statement);
		if(status == SQLITE_ERROR){
			fprintf(stderr, "SQL gets an error.: %s\n", sqlite3_errmsg(conn2_));
			break;
		}else if(status == SQLITE_DONE){
			//SQL are executed without errors
			break;
		}else if(status == SQLITE_BUSY){
			cout << "sqlite is busy" << endl;
			cout << sqlite3_errmsg(conn2_) << endl;
		}else if(status == SQLITE_ROW){
			cout << "sql returns row. this Operator is supposed to be used for read only operation" << endl;
		}else if(status == SQLITE_MISUSE){
			cout << "sql is used in wrong way" << endl;
			cout << sqlite3_errmsg(conn2_) << endl;
			sleep(2);
		}else{
			cout << "sql returns unkown error" << endl;
			cout << sqlite3_errmsg(conn2_) << endl;
		}
		if (loop++>limit){
			cout << "sqlite execution loop reached max." << endl;
			break;
		}
	}
	sqlite3_finalize(statement);
}

void SqliteDao::ExecBatchSqlMemory(const string &sql, int limit){
	sqlite3_stmt *statement;
	int status=0;
	// Compile SQL
	sqlite3_prepare_v2(conn_, sql.c_str(), -1, &statement, NULL);
	// Excute all SQL 
	int loop=0;
	while (1){
		status = sqlite3_step(statement);
		if(status == SQLITE_ERROR){
			fprintf(stderr, "SQL gets an error.: %s\n", sqlite3_errmsg(conn_));
			break;
		}else if(status == SQLITE_DONE){
			//SQL are executed without errors
			break;
		}else if(status == SQLITE_BUSY){
			cout << "sqlite is busy" << endl;
			cout << sqlite3_errmsg(conn_) << endl;
		}else if(status == SQLITE_ROW){
			cout << "sql returns row. this Operator is supposed to be used for read only operation" << endl;
		}else if(status == SQLITE_MISUSE){
			cout << "sql is used in wrong way" << endl;
			cout << sqlite3_errmsg(conn_) << endl;
			sleep(2);
		}else{
			cout << "sql returns unkown error" << endl;
			cout << sqlite3_errmsg(conn_) << endl;
		}
		if (loop++>limit){
			cout << "sqlite execution loop reached max." << endl;
			break;
		}
	}
	sqlite3_finalize(statement);
}

// Get SQL from a file and create table.
void SqliteDao::CreateTableFromFileMemory(const string &file_path){
	ifstream is;
	is.open(file_path.c_str());

	if(!is){
		cout << "Config: Can't open " << file_path << "."<< endl;
		exit(1);
	}

	string sqls;
	for (string line; getline(is, line);){
		sqls += line;
	}

	//Parse each sql
	string delimiter = ";";

	size_t pos = 0;
	string sql;
	while ((pos = sqls.find(delimiter)) != string::npos) {
		sql = sqls.substr(0, pos);
		sqls.erase(0, pos + delimiter.length());
		ExecBatchSqlMemory(sql, 2);
	}
}
// Get SQL from a file and create table.
void SqliteDao::CreateTableFromFile(const string &file_path){
	ifstream is;
	is.open(file_path.c_str());
	
	string dbnamestring = config->get("dbname");
	int len = dbnamestring.length();
	char* dbname = new char[len+1];
	memcpy(dbname, dbnamestring.c_str(), len+1);

	if(!is){
		cout << "Config: Can't open " << file_path << "."<< endl;
		exit(1);
	}

	string sqls;
	for (string line; getline(is, line);){
		sqls += line;
	}

	//Parse each sql
	string delimiter = ";";

	size_t pos = 0;
	string sql;
	string double_quoates = "\"";
	//size_t qpos = 0;
	//size_t qqpos = 0;
	while ((pos = sqls.find(delimiter)) != string::npos) {
		sql = sqls.substr(0, pos);
		sqls.erase(0, pos + delimiter.length());
		/*	
		qpos = sql.find(double_quoates, 0)+1;
		qqpos = sql.find(double_quoates, qpos);
		cout << qpos << "\t" << qqpos << endl;
		sqlite3_stmt* table_exit;
		cout << "aaaaaaa+++" << sql.substr(qpos, qqpos-qpos) << "+++aaaaaaaa"<< endl;
		string tablesql;
		tablesql = "select count(*) from sqlite_master where type='table' and name='";
		tablesql += sql.substr(qpos, qqpos-qpos);
		tablesql += "'";
		tablesql += delimiter; 
		table_exit = ExecSql(tablesql);		
		cout << sqlite3_column_int(table_exit, 0) << endl;
		if(sqlite3_column_int(table_exit, 0) == 0){
			ExecBatchSql(sql, 2);
		}
		sqlite3_finalize(table_exit);
		*/
		ExecBatchSql(sql, 2);
	}
}

void SqliteDao::EscapeSingleQuote(string &target){
	find_and_replace(target, "'", "''");
}
