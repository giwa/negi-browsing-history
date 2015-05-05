#pragma once
#include "Include.H"
#include "Global.H"

class BTPgsql{
	private:
		map<string, string> pgsql_map;

	public:
		BTPgsql();
		int Connect(const string filename);
//		result* SqlExec(const string sql);
//		int Insert(PGconn *con, string src_mac_addr, string timestamp, string url, string title);
		string SqlLoad(string action, string mac_addr, string timestamp, string option);

//		connection *con;

};
