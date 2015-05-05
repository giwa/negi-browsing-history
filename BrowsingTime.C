#include "BrowsingTime.H"
#include "BTGlobal.H"

BrowsingTime::BrowsingTime(){
}

BrowsingTime::~BrowsingTime(){
}

//mode1:specify nothsing   mode2:specify mac_addr and timestamp  mode3:specify option
//int BrowsingTime::Proc(int mode, string mac_addr, string timestamp, string option){
int BrowsingTime::Proc(string mac_addr){
//	btpgsql = new BTPgsql;
	url = new Url;
//	search_client = new SearchClient;

	if(!pretimestamp.count(mac_addr)){
		pretimestamp.insert(pair<string, string>(mac_addr, "2010-04-22"));
	}
	if(!prepretimestamp.count(mac_addr)){
		prepretimestamp.insert(pair<string, string>(mac_addr, "2010-04-22"));
	}
	if(!preprepretimestamp.count(mac_addr)){
		preprepretimestamp.insert(pair<string, string>(mac_addr, "2010-04-22"));
	}

	//string sql = btsql->SqlLoad("do", mac_addr, prepretimestamp[mac_addr], "");
	string sql;
	sql= "SELECT stream_id, id, timestamp, src_ip, dst_ip, src_port, dst_port, pattern, result, src_mac_addr, dst_mac_addr, epoch_time FROM save_result WHERE (src_mac_addr = '";
	sql += mac_addr;
	sql += "' OR dst_mac_addr = '";
	sql += mac_addr;
	sql += "') ";
	sql += "AND ";
	sql += "timestamp >= '";
	sql += prepretimestamp[mac_addr];
	sql += "' ";
//	sql += "ORDER BY datetime(timestamp) ASC;";
	sql += "ORDER BY stream_id ASC;";


//	sqlite3_stmt *res_;
//	res_ = sqlite_dao->ExecSql(sql);
//	while(SQLITE_ROW == sqlite3_step(res_)){
//		cout << string((char *)sqlite3_column_text(res_, 0)) << "\tyeah\t";
//		cout << string((char *)sqlite3_column_text(res_, 7)) << endl;
//	}
	url->Reconstruct(sql);
	url->Identify();
	url->GetHistory(preprepretimestamp[mac_addr]);
	if(url->GetExitNewHistory()){
		prepretimestamp[mac_addr] = pretimestamp[mac_addr];
		//cout << url->GetTmpTimestamp() << endl;
		pretimestamp[mac_addr] = url->GetTmpTimestamp();
		//cout << pretimestamp[mac_addr] << endl;
		preprepretimestamp[mac_addr] = prepretimestamp[mac_addr];
		master->recom_flag = 1;
	}


/*

	if(mode == 1){
		string sql = btpgsql->SqlLoad("search", "", "", "");
		search_client->Variety(btpgsql->SqlExec(sql));
		map<string, string>::iterator it = search_client->client.begin();
		while(it != search_client->client.end()){
			cout << endl << (*it).first << endl;
			sql = btpgsql->SqlLoad("do", (*it).first, "2010-04-22", "");
//			cout << sql << endl;
			url->Reconstruct(btpgsql->SqlExec(sql));
			url->Identify();
			url->GetHistory("2010-04-22");
			it++;
			cout << endl;
		}
	}else{
		string sql;
		if(mode == 2){
			cout << endl << mac_addr << "\t" << prepretimestamp[mac_addr] << "\t" << pretimestamp[mac_addr] << endl;
			sql = btpgsql->SqlLoad("do", mac_addr, prepretimestamp[mac_addr], "");
			url->Reconstruct(btpgsql->SqlExec(sql));
			url->Identify();
			url->GetHistory(prepretimestamp[mac_addr]);
			if(url->GetExitNewHistory()){
				prepretimestamp[mac_addr] = pretimestamp[mac_addr];
			//	cout << url->GetTmpTimestamp() << endl;
				pretimestamp[mac_addr] = url->GetTmpTimestamp();
			//	cout << pretimestamp[mac_addr] << endl;
			}
			//cout << endl;
		}else if(mode == 3){
			//cout << endl << mac_addr <<"\t"<< timestamp <<endl;
			sql = btpgsql->SqlLoad("do", mac_addr, timestamp, "short");
			url->Reconstruct(btpgsql->SqlExec(sql));
			url->Identify();
			url->GetHistory("2010-04-22");
			//tmptimestamp = prevtmptimestamp;
			//prevtmptimestamp = url->GetTmporaryTimestamp();
			cout << endl;
		}else{
			string str = option;
			if(str == "short"){
				sql = btpgsql->SqlLoad("search", "", "", "short");
				search_client->Variety(btpgsql->SqlExec(sql));
				map<string, string>::iterator it = search_client->client.begin();
				while(it != search_client->client.end()){
					if((*it).first != "68:b5:99:76:4a:60"){
//						cout << "MAC:" << (*it).first << endl;
						sql = btpgsql->SqlLoad("do", (*it).first, "", "short");
						url->Reconstruct(btpgsql->SqlExec(sql));
						url->Identify();
						url->GetHistory("2010-04-22");
					}
					it++;
				}
			}else{
				cout << endl << mac_addr << endl;
				sql = btpgsql->SqlLoad("do", mac_addr, "", "");
				url->Reconstruct(btpgsql->SqlExec(sql));
				url->Identify();
				url->GetHistory("2010-04-22");
				cout << endl;
			}
		}
	}
*/

	//ForAll
//	map<string, string>::iterator it_forall_url = url->forallmap->url.begin();
//	map<string, string>::iterator it_forall_title = url->forallmap->title.begin();
//	map<string, string>::iterator it_forall_src_mac_addr = url->forallmap->src_mac_addr.begin();
//	map<string, string>::iterator it_forall_debug = url->forallmap->debug.begin();
//	map<string, string>::iterator it_forall_browsing_time = url->forallmap->browsing_time.begin();
//	map<string, long>::iterator it_forall_sec = url->forallmap->sec.begin();
//	map<string, long>::iterator it_forall_usec = url->forallmap->usec.begin();
//	while(it_forall_url != url->forallmap->url.end()){
//		cout << (*it_forall_src_mac_addr).second << "\t" << (*it_forall_url).first << "\t" << (*it_forall_url).second << "\t";
////		cout << (*it_forall_debug).second << "\t";
//		if((*it_forall_title).second == ""){
//			cout << "NO TITLE" << "\t";
//		}else{
//			cout << (*it_forall_title).second << "\t";
//		}
//		cout << (*it_forall_browsing_time).second << endl;
//		++it_forall_sec;
//		++it_forall_usec;
//		++it_forall_url;
//		++it_forall_src_mac_addr;
//		++it_forall_title;
//		++it_forall_debug;
//		++it_forall_browsing_time;
//	}

	return 0;
}

/*
int main(void){
	browsingtime->Proc(1, "", "", "");
	return 0;
}
*/
