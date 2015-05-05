#include "BTPgsql.H"

BTPgsql::BTPgsql(){
}


int BTPgsql::Connect(const string filename){
	ifstream is;
	is.open(filename.c_str());
	if(!is){
		cout << "Pgsql: cannnot open " << filename << "." << endl;
		exit(1);
	}
	while(!is.eof()){
		string index;
		string value;

		is >> index >> value;

		pgsql_map[index] = value;

	}

/*
	con = PQsetdbLogin(pgsql_map["dbhost"].c_str(), NULL, NULL, NULL, pgsql_map["dbname"].c_str(), pgsql_map["dbuser"].c_str(), pgsql_map["dbpass"].c_str());
	if(PQstatus(con) == CONNECTION_BAD){
		cout << "DB CONNECTION FOR " << pgsql_map["dbname"] << " IS NG" << endl;
		exit(1);
	}
*/
	return 0;

}
/*
PGresult* BTPgsql::SqlExec(const string sql){
	PGresult *res;
	res = PQexec(con, sql.c_str());

//	int n = PQntuples(res);
//	if(n == 0){
//		cout << "NO DATA" << endl;
//		exit(1);
//	}

	return res;
}
*/
/*
result* BTPgsql::SqlExec(const string sql){
	result *res;
	connection *con = pgsql->GetConn();
	work T(*con);
	res = new result(T.exec(sql));
	T.commit();
	
	if(){
		cout << "NO DATA" << endl;
	}
	

	return res;
}
*/

string BTPgsql::SqlLoad(string action, string mac_addr, string time, string option){
	string sql;
	if(option == ""){
		if(action == "search"){
			sql = "SELECT src_mac_addr, dst_mac_addr, pattern, result FROM save_result WHERE pattern like \'%GET%\' ";
//			sql = "SELECT src_mac_addr, dst_mac_addr, pattern, result FROM save_result WHERE pattern like \'%GET%\' ORDER BY stream_id ASC";

//			sql += "AND timestamp >= cast('2013-11-05' as timestamp) AND timestamp < cast('2013-11-11' as timestamp) ";

			sql += "ORDER BY timestamp ASC";
		}else if(action == "do"){
			sql = "SELECT stream_id, id, timestamp, src_ip, dst_ip, src_port, dst_port, pattern, result, extract(epoch from timestamp), src_mac_addr, dst_mac_addr FROM save_result WHERE (src_mac_addr ilike '%";
			sql += mac_addr;
			sql += "%' OR dst_mac_addr ilike '%";
			sql += mac_addr;
			sql += "%') ";
			if(time != ""){
				sql += "AND ";
				sql += "substr(cast(timestamp as text), 1, 10) >= '";
				sql += time;
				sql += "' ";

//				sql += "AND ";
//				sql += "substr(cast(timestamp as text), 1, 10) <= '";
//				sql += "2015-01-22";
//				sql += "' ";
			}

//			sql += "AND timestamp >= cast('2013-11-05' as timestamp) AND timestamp < cast('2013-11-11' as timestamp) ";

			sql += "ORDER BY timestamp ASC";
	//		sql += "ORDER BY stream_id ASC";
		}
	}else if(option == "short"){
		if(action == "search"){
			//SqlExec("DROP TABLE short_result");
			//SqlExec("CREATE TABLE short_result as SELECT * FROM save_result WHERE timestamp >= cast(now() - interval '30 minutes' as timestamp)");
			sql = "SELECT src_mac_addr, dst_mac_addr, pattern, result FROM short_result WHERE pattern like \'%GET%\' ";
			sql += "AND timestamp >= cast(now() - interval '30 minutes' as timestamp) ";
			sql += "ORDER BY timestamp ASC";
		}else if(action == "do"){
			sql = "SELECT stream_id, id, timestamp, src_ip, dst_ip, src_port, dst_port, pattern, result, extract(epoch from timestamp), src_mac_addr, dst_mac_addr FROM save_result WHERE (src_mac_addr ilike '%";
			sql += mac_addr;
			sql += "%' OR dst_mac_addr ilike '%";
			sql += mac_addr;
			sql += "%') ";
			sql += "AND ";
			sql += "timestamp >= cast(cast('";
			sql += time;
			sql += "'as timestamp) - interval '30 minutes' as timestamp) ";
			sql += "ORDER BY extract(epoch from timestamp)";
		}
	}

	return sql;
}

/*
int BTPgsql::Insert(PGconn *con, string src_mac_addr, string timestamp, string url, string title){
	PGresult *res;
	string sql = "INSERT INTO url (id, mac_addr, timestamp, url, title) VALUES (nextval('url_id_seq'), '";
	sql += src_mac_addr;
	sql += "', '";
	sql += timestamp;
	sql += "', '";
	sql += url;
	sql += "', E'";
	sql += title;
	sql += "')";
	res = PQexec(con, sql.c_str());
	if(PQresultStatus(res) != PGRES_TUPLES_OK){
		cout << PQerrorMessage(con) << endl;
		return -1;
	}
	PQclear(res);

	return 0;

}
*/
