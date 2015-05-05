#include "Url.H"
#include "BTGlobal.H"

Url::Url(){
//	idmap = new IdMap;
	timestampmap = new TimestampMap;
	clientmap = new ClientMap;
	forallmap = new ForAllMap;
	filter = new Filter;
	local = new Local;
	exit_new_history = 0;
}

int Url::GetHistory(string prepretimestamp){
//	cout << "CAL TIMEDEF" << endl;
//	GoogleRedirectFilter();
//	cout << "EXTENSION FILTER" << endl;
//	filter->RefFilter();
//	filter->RefFilterAdv();


	filter->ContentTypeFilter();//Content-type = text/html
	filter->ExtensionFilter();//trash the packet including specific extension
	filter->URLFilter();//URL including specific string
//	filter->ResponseExistenceFilter();
	filter->HTTPStatusFilter();
	filter->TitleFilter();
	filter->TitleExitFilter();//satoshi_added

//	filter->WhiteList();

//	cout << "ERASE" << endl;
//	filter->Erase();
//	filter->TimeDiffFilter();

//	filter->ErrorFilter();

//	UrlShow();

	filter->Erase();
	filter->EraseGoogle();

	UrlInsert(prepretimestamp);
//	UrlShow();

//	local->Identify();
//	local->ReconstructByRef();
//	local->ReconstructByRef();
//	local->ReconstructByCookie();
//	local->ReconstructByCookie();
//
//	filter->AloneFilter();
//	filter->Erase();
//
//	local->Show();

	return 0;
}

int Url::UrlInsert(string prepretimestamp){
	multimap<string, string>::iterator it_timestamp = clientmap->timestamp.begin();
	multimap<string, string>::iterator it_src_ip = clientmap->src_ip.begin();
	multimap<string, string>::iterator it_dst_ip = clientmap->dst_ip.begin();
	multimap<string, string>::iterator it_src_port = clientmap->src_port.begin();
	multimap<string, string>::iterator it_dst_port = clientmap->dst_port.begin();
	multimap<string, string>::iterator it_url = clientmap->url.begin();
	multimap<string, string>::iterator it_ref = clientmap->ref.begin();
	multimap<string, string>::iterator it_cookie = clientmap->cookie.begin();
	multimap<string, string>::iterator it_user_agent = clientmap->user_agent.begin();
	multimap<string, string>::iterator it_host = clientmap->host.begin();
	multimap<string, double>::iterator it_secusec = clientmap->secusec.begin();
	multimap<string, long>::iterator it_sec = clientmap->sec.begin();
	multimap<string, long>::iterator it_usec = clientmap->usec.begin();
	multimap<string, double>::iterator it_timestamp_def = clientmap->timestamp_def.begin();
	multimap<string, int>::iterator it_title_flag = clientmap->title_flag.begin();
	multimap<string, int>::iterator it_heading_flag = clientmap->heading_flag.begin();
	multimap<string, int>::iterator it_erase_flag = clientmap->erase_flag.begin();
	multimap<string, string>::iterator it_title = clientmap->title.begin();
	multimap<string, string>::iterator it_content_type = clientmap->content_type.begin();
	multimap<string, int>::iterator it_local_id = clientmap->local_id.begin();
	multimap<string, string>::iterator it_debug = clientmap->debug.begin();

	multimap<string, string> timestamp_url;
	multimap<string, string>::iterator it_timestamp_url;
	multimap<string, string> timestamp_src_mac_addr;
	multimap<string, string>::iterator it_timestamp_src_mac_addr;
	multimap<string, int> timestamp_erase_flag;
	multimap<string, int>::iterator it_timestamp_erase_flag;
	multimap<string, int> timestamp_title_flag;
	multimap<string, int>::iterator it_timestamp_title_flag;
	multimap<string, string> timestamp_cookie;
	multimap<string, string>::iterator it_timestamp_cookie;
	multimap<string, string> timestamp_ref;
	multimap<string, string>::iterator it_timestamp_ref;
	multimap<string, string> timestamp_title;
	multimap<string, string>::iterator it_timestamp_title;
	multimap<string, string> timestamp_user_agent;
	multimap<string, string>::iterator it_timestamp_user_agent;
	multimap<string, string> timestamp_src_ip;
	multimap<string, string>::iterator it_timestamp_src_ip;
	multimap<string, string> timestamp_dst_ip;
	multimap<string, string>::iterator it_timestamp_dst_ip;
	multimap<string, string> timestamp_content_type;
	multimap<string, string>::iterator it_timestamp_content_type;
	multimap<string, int> timestamp_local_id;
	multimap<string, int>::iterator it_timestamp_local_id;
	multimap<string, double> timestamp_secusec;
	multimap<string, double>::iterator it_timestamp_secusec;
	multimap<string, long> timestamp_sec;
	multimap<string, long>::iterator it_timestamp_sec;
	multimap<string, long> timestamp_usec;
	multimap<string, long>::iterator it_timestamp_usec;
	multimap<string, string> timestamp_browsing_time;
	multimap<string, string>::iterator it_timestamp_browsing_time;
	multimap<string, string> timestamp_debug;
	multimap<string, string>::iterator it_timestamp_debug;

	int timestamp_error_flag = 0;
	long buf, buf2;
	long prebuf, prebuf2;

	while(it_url != clientmap->url.end()){
		timestamp_url.insert(pair<string, string>((*it_timestamp).second, (*it_url).second));
		timestamp_src_mac_addr.insert(pair<string, string>((*it_timestamp).second, (*it_url).first));
		timestamp_erase_flag.insert(pair<string, int>((*it_timestamp).second, (*it_erase_flag).second));
		timestamp_title_flag.insert(pair<string, int>((*it_timestamp).second, (*it_title_flag).second));
		timestamp_title.insert(pair<string, string>((*it_timestamp).second, (*it_title).second));
		timestamp_ref.insert(pair<string, string>((*it_timestamp).second, (*it_ref).second));
		timestamp_cookie.insert(pair<string, string>((*it_timestamp).second, (*it_cookie).second));
		timestamp_user_agent.insert(pair<string, string>((*it_timestamp).second, (*it_user_agent).second));
		timestamp_src_ip.insert(pair<string, string>((*it_timestamp).second, (*it_src_ip).second));
		timestamp_dst_ip.insert(pair<string, string>((*it_timestamp).second, (*it_dst_ip).second));
		timestamp_content_type.insert(pair<string, string>((*it_timestamp).second, (*it_content_type).second));
		timestamp_local_id.insert(pair<string, int>((*it_timestamp).second, (*it_local_id).second));
		timestamp_secusec.insert(pair<string, double>((*it_timestamp).second, (*it_secusec).second));
		timestamp_sec.insert(pair<string, long>((*it_timestamp).second, (*it_sec).second));
		timestamp_usec.insert(pair<string, long>((*it_timestamp).second, (*it_usec).second));
		timestamp_debug.insert(pair<string, string>((*it_timestamp).second, (*it_debug).second));

//		cout << "URL" << (*it_timestamp).first << "\t" << (*it_url).second << endl;
		forallmap->url.insert(pair<string, string>((*it_timestamp).second, (*it_url).second));
		forallmap->title.insert(pair<string, string>((*it_timestamp).second, (*it_title).second));
		forallmap->src_mac_addr.insert(pair<string, string>((*it_timestamp).second, (*it_timestamp).first));
		forallmap->debug.insert(pair<string, string>((*it_timestamp).second, (*it_debug).second));
		forallmap->sec.insert(pair<string, long>((*it_timestamp).second, (*it_sec).second));
		forallmap->usec.insert(pair<string, long>((*it_timestamp).second, (*it_usec).second));
		forallmap->src_ip.insert(pair<string, string>((*it_timestamp).second, (*it_src_ip).second));
		forallmap->dst_ip.insert(pair<string, string>((*it_timestamp).second, (*it_dst_ip).second));

		//for avoid minus bug satoshi_WIDE
//		long prebuf, prebuf2;
		prebuf = buf;
		prebuf2 = buf2;

//		long buf, buf2;
		buf = (*it_sec).second;
		buf2 = (*it_usec).second;


		++it_sec;
		++it_usec;
///*
		if(it_sec != clientmap->sec.end()){
			if( (buf < (*it_sec).second) || ((buf == (*it_sec).second) && (buf2 < (*it_usec).second)) ){
			//	cout << "owarijanaiyo\t" << (*it_timestamp).second << "\t" << (*it_url).second << endl;//satoshi_debug
				forallmap->browsing_time.insert(pair<string, string>((*it_timestamp).second, CalBrowsingTime(buf, buf2, (*it_sec).second, (*it_usec).second)));
				timestamp_browsing_time.insert(pair<string, string>((*it_timestamp).second, CalBrowsingTime(buf, buf2, (*it_sec).second, (*it_usec).second)));
			}else{
				forallmap->browsing_time.insert(pair<string, string>((*it_timestamp).second, "none"));
				timestamp_browsing_time.insert(pair<string, string>((*it_timestamp).second, "none"));
				timestamp_error_flag = 1;
			}
		}else{
			if(timestamp_error_flag == 1){
//				cout << "owaridayo\t" << (*it_timestamp).second << "\t" << (*it_url).second << endl;//satoshi_debug
				forallmap->browsing_time.insert(pair<string, string>((*it_timestamp).second,  CalBrowsingTime(buf, buf2, prebuf, prebuf2)));
				timestamp_browsing_time.insert(pair<string, string>((*it_timestamp).second, CalBrowsingTime(buf, buf2, prebuf, prebuf2)));
				timestamp_error_flag = 0;
			}else{
				forallmap->browsing_time.insert(pair<string, string>((*it_timestamp).second, "none"));
				timestamp_browsing_time.insert(pair<string, string>((*it_timestamp).second, "none"));
			}
		}
//*/
/*
		if(it_sec != clientmap->sec.end()){
		//	cout << "owarijanaiyo\t" << (*it_timestamp).second << "\t" << (*it_url).second << endl;//satoshi_debug
			forallmap->browsing_time.insert(pair<string, string>((*it_timestamp).second, CalBrowsingTime(buf, buf2, (*it_sec).second, (*it_usec).second)));
			timestamp_browsing_time.insert(pair<string, string>((*it_timestamp).second, CalBrowsingTime(buf, buf2, (*it_sec).second, (*it_usec).second)));
		}else{
		//	cout << "owaridayo\t" << (*it_timestamp).second << "\t" << (*it_url).second << endl;//satoshi_debug
			forallmap->browsing_time.insert(pair<string, string>((*it_timestamp).second, "none"));
			timestamp_browsing_time.insert(pair<string, string>((*it_timestamp).second, "none"));
		}
*/


		++it_url;
		++it_timestamp;
		++it_title;
		++it_ref;
		++it_cookie;
		++it_user_agent;
		++it_src_ip;
		++it_dst_ip;
		++it_erase_flag;
		++it_title_flag;
		++it_content_type;
		++it_local_id;
		++it_debug;
		++it_secusec;

	}

	it_timestamp = clientmap->timestamp.begin();
	it_title = clientmap->title.begin();
	it_ref = clientmap->ref.begin();
	it_cookie = clientmap->cookie.begin();
	it_user_agent = clientmap->user_agent.begin();
	it_src_ip = clientmap->src_ip.begin();
	it_dst_ip = clientmap->dst_ip.begin();
	it_url = clientmap->url.begin();
	it_erase_flag = clientmap->erase_flag.begin();
	it_title_flag = clientmap->title_flag.begin();
	it_content_type = clientmap->content_type.begin();
	it_local_id = clientmap->local_id.begin();
	it_debug = clientmap->debug.begin();
	it_secusec = clientmap->secusec.begin();
	it_sec = clientmap->sec.begin();
	it_usec = clientmap->usec.begin();

	it_timestamp_url = timestamp_url.begin();
	it_timestamp_src_mac_addr = timestamp_src_mac_addr.begin();
	it_timestamp_title = timestamp_title.begin();
	it_timestamp_ref = timestamp_ref.begin();
	it_timestamp_cookie = timestamp_cookie.begin();
	it_timestamp_user_agent = timestamp_user_agent.begin();
	it_timestamp_src_ip = timestamp_src_ip.begin();
	it_timestamp_dst_ip = timestamp_dst_ip.begin();
	it_timestamp_erase_flag = timestamp_erase_flag.begin();
	it_timestamp_title_flag = timestamp_title_flag.begin();
	it_timestamp_content_type = timestamp_content_type.begin();
	it_timestamp_local_id = timestamp_local_id.begin();
	it_timestamp_secusec = timestamp_secusec.begin();
	it_timestamp_sec = timestamp_sec.begin();
	it_timestamp_usec = timestamp_usec.begin();
	it_timestamp_browsing_time = timestamp_browsing_time.begin();
	it_timestamp_debug = timestamp_debug.begin();

	string str = "";
	
	//kokorahen loop no sotonidashitemo iinodeha?
	if(it_timestamp_url != timestamp_url.end()){
	
	string sql="";
	sql = "SELECT timestamp, src_mac_addr,src_ip, url, browsing_time FROM save_history WHERE (src_ip = '";
	sql += (*it_timestamp_src_ip).second;
	sql += "') ";
	sql += "AND ";
	//sql += "substr(cast(timestamp as text), 1, 10) >= '";
	sql += "timestamp >= '";
	sql += prepretimestamp;
	sql += "' ";
	sql += "ORDER BY datetime(timestamp) ASC";

	sqlite3_stmt *compare_res_;
	compare_res_ = sqlite_dao->ExecSqlMemory(sql);

	while(it_timestamp_url != timestamp_url.end()){
		int exit_history_flag = 0;
		
		if(it_timestamp_url == timestamp_url.begin()){
//			cout << (*it_timestamp_src_ip).second << endl;
		}
//		cout << (*it_timestamp_url).second << "\t" << (*it_timestamp_user_agent).second << endl;
//		cout << (*it_timestamp_url).second << endl;
//		cout << (*it_timestamp_local_id).second << "\t" << (*it_timestamp_url).second << "\t" << (*it_timestamp_cookie).second << endl;
//		cout << (*it_timestamp_local_id).second << "\t" << (*it_timestamp_url).second << "\t" << (*it_timestamp_cookie).second << endl;
//		local->CookieParse((*it_timestamp_cookie).second);
//		cout << "USERAGENT:" << "\t" << (*it_timestamp_user_agent).second << endl;
//		cout << "COOKIE:" << "\t" << (*it_timestamp_cookie).second << endl;
//		cout << "REFERER:" << "\t" << (*it_timestamp_ref).second << endl;
//		cout << (*it_timestamp_title_flag).first << "\t" << (*it_timestamp_url).second << endl;
//		cout << (*it_timestamp_url).second << "\t" << (*it_timestamp_content_type).second << endl;
//		cout << (*it_timestamp_url).second << "\t" << (*it_timestamp_title).second << endl;
//		cout << (*it_timestamp_url).second << "\t" << (*it_timestamp_ref).second << endl;
//		cout << (*it_timestamp_url).second << endl;
//		cout << (*it_timestamp_erase_flag).second << "\t" << (*it_timestamp_url).first << "\t" << (*it_timestamp_url).second << "\t";

//		cout << (*it_timestamp_src_mac_addr).second << "\t";

//		stringstream ss, ss2;
//		ss.str("");
//		ss2.str("");
//		ss.clear(stringstream::goodbit);
//		ss2.clear(stringstream::goodbit);
//		ss << (*it_timestamp_sec).second << "." << (*it_timestamp_usec).second;
		
//		long buf, buf2;
//		buf = (*it_timestamp_sec).second;
//		buf2 = (*it_timestamp_usec).second;
//		++it_timestamp_sec;
//		++it_timestamp_usec;
////		ss2 << (*it_timestamp_sec).second << "." << (*it_timestamp_usec).second;
////		cout << ss.str() << "\t" << ss2.str() << endl;
//		cout << (*it_timestamp_url).first << "\t" << CalBrowsingTime(buf, buf2, (*it_timestamp_sec).second, (*it_timestamp_usec).second) << "\t" << (*it_timestamp_url).second << endl;

//		if(str != (*it_timestamp_url).second){


//			cout << (*it_timestamp_ref).second << "\t";
//			cout << (*it_timestamp_url).second << endl;
//			cout << (*it_timestamp_src_mac_addr).second << "\t";
//			cout << (*it_timestamp_url).first << "\t";
//			cout << (*it_timestamp_debug).second << "\t";
//			cout << (*it_timestamp_url).second << "\t";
//			cout << (*it_timestamp_erase_flag).second << "\t";
//			cout << (*it_timestamp_title_flag).second << "\t";
//			cout << (*it_timestamp_title).second << "\t";
//			cout << (*it_timestamp_title).second << "\t";

//			cout << (*it_timestamp_url).first << "\t" << (*it_timestamp_url).second << "\t";
//			if((*it_timestamp_title).second == ""){
//				cout << "NO TITLE" << "\t";
//			}else{
//				cout << (*it_timestamp_title).second << "\t";
//			}
//			cout << (*it_timestamp_browsing_time).second << "\t";
//			cout << endl;
//			cout << (*it_timestamp_browsing_time).second << endl;
//			cout << (*it_timestamp_debug).second << endl;
//			cout << "COOK\t" << (*it_timestamp_cookie).second << endl;
//			cout << "REF\t" << (*it_timestamp_ref).second << endl;

			stringstream dss;
			double tmp_browsing_time = 0;
			if((*it_timestamp_browsing_time).second != "none"){
				dss << (*it_timestamp_browsing_time).second;
				dss >> tmp_browsing_time;
			}
			while(sqlite3_step(compare_res_) == SQLITE_ROW){
				if( (*it_timestamp_url).second==string((char *)sqlite3_column_text(compare_res_, 3)) && (*it_timestamp_browsing_time).second==string((char *)sqlite3_column_text(compare_res_, 4)) && (*it_timestamp_url).first==string((char *)sqlite3_column_text(compare_res_, 0))){
					exit_history_flag = 1;
					//cout << "sudenisonzaisshiteruyo----------------" << endl;//satoshi_debug
					break;
				}
			}

			if(exit_history_flag == 0 ){
				string temp_title =  (*it_timestamp_title).second;
				sqlite_dao->EscapeSingleQuote(temp_title);

				ostringstream oss;
				oss.str("");

				oss << "insert into save_history(timestamp, src_mac_addr, src_ip, dst_ip,  url, title, browsing_time) values "\
				<< "('" << (*it_timestamp_url).first << "','" << (*it_timestamp_src_mac_addr).second << "','" << (*it_timestamp_src_ip).second << "','" << (*it_timestamp_dst_ip).second<< "','" << (*it_timestamp_url).second << "','" << temp_title << "','" << (*it_timestamp_browsing_time).second << "');";
				string query = oss.str();

				sqlite_dao->ExecBatchSqlMemory(query);
				sqlite_dao->ExecBatchSql(query);

				cout << (*it_timestamp_url).first
					<< "\t" << (*it_timestamp_src_mac_addr).second
					//<< "\t" << (*it_timestamp_src_ip).second
					//<< "\t" << (*it_timestamp_dst_ip).second
					<< "\t" << (*it_timestamp_url).second
					<< "\t" << (*it_timestamp_title).second
					<< "\t" << (*it_timestamp_browsing_time).second
					<< endl;

				SetTmpTimestamp((*it_timestamp_url).first);
				//exit_history_flag = 0;
			}
//		}

		str = (*it_timestamp_url).second;

//		cout << "REFERER" << "\t" << (*it_timestamp_ref).second << endl;
//		cout << "USER-AGENT" << "\t" << (*it_timestamp_user_agent).second << endl;
//		cout << "COOKIE" << "\t" << (*it_timestamp_cookie).second << endl;

//		long buf, buf2;
//		buf = (*it_timestamp_sec).second;
//		buf2 = (*it_timestamp_usec).second;
//
//		++it_timestamp_sec;
//		++it_timestamp_usec;
//
//		if(it_timestamp_sec != timestamp_sec.end()){
//			forallmap->browsing_time.insert(pair<string, string>((*it_timestamp_url).first, CalBrowsingTime(buf, buf2, (*it_timestamp_sec).second, (*it_timestamp_usec).second)));
//		}else{
//			forallmap->browsing_time.insert(pair<string, string>((*it_timestamp_url).first, "none"));
//		}

		++it_timestamp_url;
		++it_timestamp_src_mac_addr;
		++it_timestamp_title;
		++it_timestamp_ref;
		++it_timestamp_cookie;
		++it_timestamp_user_agent;
		++it_timestamp_src_ip;
		++it_timestamp_dst_ip;
		++it_timestamp_erase_flag;
		++it_timestamp_title_flag;
		++it_timestamp_content_type;
		++it_timestamp_local_id;
		++it_timestamp_sec;
		++it_timestamp_usec;
		++it_timestamp_browsing_time;
		++it_timestamp_debug;
	}
	sqlite3_finalize(compare_res_);
	}
	return 0;
}





int Url::UrlShow(){
	multimap<string, string>::iterator it_timestamp = clientmap->timestamp.begin();
	multimap<string, string>::iterator it_src_ip = clientmap->src_ip.begin();
	multimap<string, string>::iterator it_dst_ip = clientmap->dst_ip.begin();
	multimap<string, string>::iterator it_src_port = clientmap->src_port.begin();
	multimap<string, string>::iterator it_dst_port = clientmap->dst_port.begin();
	multimap<string, string>::iterator it_url = clientmap->url.begin();
	multimap<string, string>::iterator it_ref = clientmap->ref.begin();
	multimap<string, string>::iterator it_cookie = clientmap->cookie.begin();
	multimap<string, string>::iterator it_user_agent = clientmap->user_agent.begin();
	multimap<string, string>::iterator it_host = clientmap->host.begin();
	multimap<string, double>::iterator it_secusec = clientmap->secusec.begin();
	multimap<string, long>::iterator it_sec = clientmap->sec.begin();
	multimap<string, long>::iterator it_usec = clientmap->usec.begin();
	multimap<string, double>::iterator it_timestamp_def = clientmap->timestamp_def.begin();
	multimap<string, int>::iterator it_title_flag = clientmap->title_flag.begin();
	multimap<string, int>::iterator it_heading_flag = clientmap->heading_flag.begin();
	multimap<string, int>::iterator it_erase_flag = clientmap->erase_flag.begin();
	multimap<string, string>::iterator it_title = clientmap->title.begin();
	multimap<string, string>::iterator it_content_type = clientmap->content_type.begin();
	multimap<string, int>::iterator it_local_id = clientmap->local_id.begin();
	multimap<string, string>::iterator it_debug = clientmap->debug.begin();

	multimap<string, string> timestamp_url;
	multimap<string, string>::iterator it_timestamp_url;
	multimap<string, string> timestamp_src_mac_addr;
	multimap<string, string>::iterator it_timestamp_src_mac_addr;
	multimap<string, int> timestamp_erase_flag;
	multimap<string, int>::iterator it_timestamp_erase_flag;
	multimap<string, int> timestamp_title_flag;
	multimap<string, int>::iterator it_timestamp_title_flag;
	multimap<string, string> timestamp_cookie;
	multimap<string, string>::iterator it_timestamp_cookie;
	multimap<string, string> timestamp_ref;
	multimap<string, string>::iterator it_timestamp_ref;
	multimap<string, string> timestamp_title;
	multimap<string, string>::iterator it_timestamp_title;
	multimap<string, string> timestamp_user_agent;
	multimap<string, string>::iterator it_timestamp_user_agent;
	multimap<string, string> timestamp_src_ip;
	multimap<string, string>::iterator it_timestamp_src_ip;
	multimap<string, string> timestamp_content_type;
	multimap<string, string>::iterator it_timestamp_content_type;
	multimap<string, int> timestamp_local_id;
	multimap<string, int>::iterator it_timestamp_local_id;
	multimap<string, double> timestamp_secusec;
	multimap<string, double>::iterator it_timestamp_secusec;
	multimap<string, long> timestamp_sec;
	multimap<string, long>::iterator it_timestamp_sec;
	multimap<string, long> timestamp_usec;
	multimap<string, long>::iterator it_timestamp_usec;
	multimap<string, string> timestamp_browsing_time;
	multimap<string, string>::iterator it_timestamp_browsing_time;
	multimap<string, string> timestamp_debug;
	multimap<string, string>::iterator it_timestamp_debug;

	while(it_url != clientmap->url.end()){
		timestamp_url.insert(pair<string, string>((*it_timestamp).second, (*it_url).second));
		timestamp_src_mac_addr.insert(pair<string, string>((*it_timestamp).second, (*it_url).first));
		timestamp_erase_flag.insert(pair<string, int>((*it_timestamp).second, (*it_erase_flag).second));
		timestamp_title_flag.insert(pair<string, int>((*it_timestamp).second, (*it_title_flag).second));
		timestamp_title.insert(pair<string, string>((*it_timestamp).second, (*it_title).second));
		timestamp_ref.insert(pair<string, string>((*it_timestamp).second, (*it_ref).second));
		timestamp_cookie.insert(pair<string, string>((*it_timestamp).second, (*it_cookie).second));
		timestamp_user_agent.insert(pair<string, string>((*it_timestamp).second, (*it_user_agent).second));
		timestamp_src_ip.insert(pair<string, string>((*it_timestamp).second, (*it_src_ip).second));
		timestamp_content_type.insert(pair<string, string>((*it_timestamp).second, (*it_content_type).second));
		timestamp_local_id.insert(pair<string, int>((*it_timestamp).second, (*it_local_id).second));
		timestamp_secusec.insert(pair<string, double>((*it_timestamp).second, (*it_secusec).second));
		timestamp_sec.insert(pair<string, long>((*it_timestamp).second, (*it_sec).second));
		timestamp_usec.insert(pair<string, long>((*it_timestamp).second, (*it_usec).second));
		timestamp_debug.insert(pair<string, string>((*it_timestamp).second, (*it_debug).second));

//		cout << "URL" << (*it_timestamp).first << "\t" << (*it_url).second << endl;
		forallmap->url.insert(pair<string, string>((*it_timestamp).second, (*it_url).second));
		forallmap->title.insert(pair<string, string>((*it_timestamp).second, (*it_title).second));
		forallmap->src_mac_addr.insert(pair<string, string>((*it_timestamp).second, (*it_timestamp).first));
		forallmap->debug.insert(pair<string, string>((*it_timestamp).second, (*it_debug).second));
		forallmap->sec.insert(pair<string, long>((*it_timestamp).second, (*it_sec).second));
		forallmap->usec.insert(pair<string, long>((*it_timestamp).second, (*it_usec).second));

		long buf, buf2;
		buf = (*it_sec).second;
		buf2 = (*it_usec).second;

		++it_sec;
		++it_usec;

		if(it_sec != clientmap->sec.end()){
			forallmap->browsing_time.insert(pair<string, string>((*it_timestamp).second, CalBrowsingTime(buf, buf2, (*it_sec).second, (*it_usec).second)));
			timestamp_browsing_time.insert(pair<string, string>((*it_timestamp).second, CalBrowsingTime(buf, buf2, (*it_sec).second, (*it_usec).second)));
		}else{
			forallmap->browsing_time.insert(pair<string, string>((*it_timestamp).second, "none"));
			timestamp_browsing_time.insert(pair<string, string>((*it_timestamp).second, "none"));
		}

		++it_url;
		++it_timestamp;
		++it_title;
		++it_ref;
		++it_cookie;
		++it_user_agent;
		++it_src_ip;
		++it_erase_flag;
		++it_title_flag;
		++it_content_type;
		++it_local_id;
		++it_debug;
		++it_secusec;

	}

	it_timestamp = clientmap->timestamp.begin();
	it_title = clientmap->title.begin();
	it_ref = clientmap->ref.begin();
	it_cookie = clientmap->cookie.begin();
	it_user_agent = clientmap->user_agent.begin();
	it_src_ip = clientmap->src_ip.begin();
	it_url = clientmap->url.begin();
	it_erase_flag = clientmap->erase_flag.begin();
	it_title_flag = clientmap->title_flag.begin();
	it_content_type = clientmap->content_type.begin();
	it_local_id = clientmap->local_id.begin();
	it_debug = clientmap->debug.begin();
	it_secusec = clientmap->secusec.begin();
	it_sec = clientmap->sec.begin();
	it_usec = clientmap->usec.begin();

	it_timestamp_url = timestamp_url.begin();
	it_timestamp_src_mac_addr = timestamp_src_mac_addr.begin();
	it_timestamp_title = timestamp_title.begin();
	it_timestamp_ref = timestamp_ref.begin();
	it_timestamp_cookie = timestamp_cookie.begin();
	it_timestamp_user_agent = timestamp_user_agent.begin();
	it_timestamp_src_ip = timestamp_src_ip.begin();
	it_timestamp_erase_flag = timestamp_erase_flag.begin();
	it_timestamp_title_flag = timestamp_title_flag.begin();
	it_timestamp_content_type = timestamp_content_type.begin();
	it_timestamp_local_id = timestamp_local_id.begin();
	it_timestamp_secusec = timestamp_secusec.begin();
	it_timestamp_sec = timestamp_sec.begin();
	it_timestamp_usec = timestamp_usec.begin();
	it_timestamp_browsing_time = timestamp_browsing_time.begin();
	it_timestamp_debug = timestamp_debug.begin();

	string str = "";

	while(it_timestamp_url != timestamp_url.end()){
		if(it_timestamp_url == timestamp_url.begin()){
//			cout << (*it_timestamp_src_ip).second << endl;
		}
//		cout << (*it_timestamp_url).second << "\t" << (*it_timestamp_user_agent).second << endl;
//		cout << (*it_timestamp_url).second << endl;
//		cout << (*it_timestamp_local_id).second << "\t" << (*it_timestamp_url).second << "\t" << (*it_timestamp_cookie).second << endl;
//		cout << (*it_timestamp_local_id).second << "\t" << (*it_timestamp_url).second << "\t" << (*it_timestamp_cookie).second << endl;
//		local->CookieParse((*it_timestamp_cookie).second);
//		cout << "USERAGENT:" << "\t" << (*it_timestamp_user_agent).second << endl;
//		cout << "COOKIE:" << "\t" << (*it_timestamp_cookie).second << endl;
//		cout << "REFERER:" << "\t" << (*it_timestamp_ref).second << endl;
//		cout << (*it_timestamp_title_flag).first << "\t" << (*it_timestamp_url).second << endl;
//		cout << (*it_timestamp_url).second << "\t" << (*it_timestamp_content_type).second << endl;
//		cout << (*it_timestamp_url).second << "\t" << (*it_timestamp_title).second << endl;
//		cout << (*it_timestamp_url).second << "\t" << (*it_timestamp_ref).second << endl;
//		cout << (*it_timestamp_url).second << endl;
//		cout << (*it_timestamp_erase_flag).second << "\t" << (*it_timestamp_url).first << "\t" << (*it_timestamp_url).second << "\t";

//		cout << (*it_timestamp_src_mac_addr).second << "\t";

//		stringstream ss, ss2;
//		ss.str("");
//		ss2.str("");
//		ss.clear(stringstream::goodbit);
//		ss2.clear(stringstream::goodbit);
//		ss << (*it_timestamp_sec).second << "." << (*it_timestamp_usec).second;
		
//		long buf, buf2;
//		buf = (*it_timestamp_sec).second;
//		buf2 = (*it_timestamp_usec).second;
//		++it_timestamp_sec;
//		++it_timestamp_usec;
////		ss2 << (*it_timestamp_sec).second << "." << (*it_timestamp_usec).second;
////		cout << ss.str() << "\t" << ss2.str() << endl;
//		cout << (*it_timestamp_url).first << "\t" << CalBrowsingTime(buf, buf2, (*it_timestamp_sec).second, (*it_timestamp_usec).second) << "\t" << (*it_timestamp_url).second << endl;

//		if(str != (*it_timestamp_url).second){


//			cout << (*it_timestamp_ref).second << "\t";
//			cout << (*it_timestamp_url).second << endl;
			cout << (*it_timestamp_src_mac_addr).second << "\t";
			cout << (*it_timestamp_url).first << "\t";
//			cout << (*it_timestamp_debug).second << "\t";
			cout << (*it_timestamp_url).second << "\t";
//			cout << (*it_timestamp_erase_flag).second << "\t";
//			cout << (*it_timestamp_title_flag).second << "\t";
//			cout << (*it_timestamp_title).second << "\t";
//			cout << (*it_timestamp_title).second << "\t";

			cout << (*it_timestamp_url).first << "\t" << (*it_timestamp_url).second << "\t";
			if((*it_timestamp_title).second == ""){
				cout << "NO TITLE" << "\t";
			}else{
				cout << (*it_timestamp_title).second << "\t";
			}
			cout << (*it_timestamp_browsing_time).second << "\t";
			cout << endl;
//			cout << (*it_timestamp_browsing_time).second << endl;
//			cout << (*it_timestamp_debug).second << endl;
//			cout << "COOK\t" << (*it_timestamp_cookie).second << endl;
//			cout << "REF\t" << (*it_timestamp_ref).second << endl;

//		}

		str = (*it_timestamp_url).second;

//		cout << "REFERER" << "\t" << (*it_timestamp_ref).second << endl;
//		cout << "USER-AGENT" << "\t" << (*it_timestamp_user_agent).second << endl;
//		cout << "COOKIE" << "\t" << (*it_timestamp_cookie).second << endl;

//		long buf, buf2;
//		buf = (*it_timestamp_sec).second;
//		buf2 = (*it_timestamp_usec).second;
//
//		++it_timestamp_sec;
//		++it_timestamp_usec;
//
//		if(it_timestamp_sec != timestamp_sec.end()){
//			forallmap->browsing_time.insert(pair<string, string>((*it_timestamp_url).first, CalBrowsingTime(buf, buf2, (*it_timestamp_sec).second, (*it_timestamp_usec).second)));
//		}else{
//			forallmap->browsing_time.insert(pair<string, string>((*it_timestamp_url).first, "none"));
//		}

		++it_timestamp_url;
		++it_timestamp_src_mac_addr;
		++it_timestamp_title;
		++it_timestamp_ref;
		++it_timestamp_cookie;
		++it_timestamp_user_agent;
		++it_timestamp_src_ip;
		++it_timestamp_erase_flag;
		++it_timestamp_title_flag;
		++it_timestamp_content_type;
		++it_timestamp_local_id;
		++it_timestamp_sec;
		++it_timestamp_usec;
		++it_timestamp_browsing_time;
		++it_timestamp_debug;
	}

	return 0;
}


int Url::Reconstruct(const string sql){
	ClearVector();
//	ClearIdMap();
	ClearTimestampMap();

/*
	for(result::const_iterator it = res->begin(); it != res->end(); it++){
		stream_id.push_back(it[0].as( string() ));
		result_id.push_back(it[1].as( string() ));
		timestamp.push_back(it[2].as( string() ));
		src_ip.push_back(it[3].as( string() ));
		dst_ip.push_back(it[4].as( string() ));
		src_port.push_back(it[5].as( string() ));
		dst_port.push_back(it[6].as( string() ));
		src_mac_addr.push_back(it[10].as( string() ));
		dst_mac_addr.push_back(it[11].as( string() ));
		pattern.push_back(it[7].as( string() ));
		result_string.push_back(it[8].as( string() ));
		unix_time.push_back(it[9].as( string() ));
	}
*/
	sqlite3_stmt *res_;
	res_ = sqlite_dao->ExecSqlMemory(sql);
//	int r;
	while(SQLITE_ROW == sqlite3_step(res_)){
		stream_id.push_back(string((char *)sqlite3_column_text(res_, 0)));
		result_id.push_back(string((char *)sqlite3_column_text(res_, 1)));
		timestamp.push_back(string((char *)sqlite3_column_text(res_, 2)));
		src_ip.push_back(string((char *)sqlite3_column_text(res_, 3)));
		dst_ip.push_back(string((char *)sqlite3_column_text(res_, 4)));
		src_port.push_back(string((char *)sqlite3_column_text(res_, 5)));
		dst_port.push_back(string((char *)sqlite3_column_text(res_, 6)));
		src_mac_addr.push_back(string((char *)sqlite3_column_text(res_, 9)));
		dst_mac_addr.push_back(string((char *)sqlite3_column_text(res_, 10)));
		pattern.push_back(string((char *)sqlite3_column_text(res_, 7)));
		result_string.push_back(string((char *)sqlite3_column_text(res_, 8)));
		unix_time.push_back(string((char *)sqlite3_column_text(res_, 11)));
	}
	/*
	if(SQLITE_DONE!=r){
		cout << "error" << endl;
	}
*/
	sqlite3_finalize(res_);

	it_stream_id = stream_id.begin();
	it_result_id = result_id.begin();
	it_timestamp = timestamp.begin();
	it_src_ip = src_ip.begin();
	it_dst_ip = dst_ip.begin();
	it_src_port = src_port.begin();
	it_dst_port = dst_port.begin();
	it_src_mac_addr = src_mac_addr.begin();
	it_dst_mac_addr = dst_mac_addr.begin();
	it_pattern = pattern.begin();
	it_result = result_string.begin();
	it_prefilter_log = prefilter_log.begin();
	it_unix_time = unix_time.begin();

	int title_flag;
	int heading_flag;
	wait_num = 0;
	while(it_timestamp != timestamp.end()){
		if(wait_num == 0){
			wait_num = MatchNumberInStream(it_timestamp);
			ClearGET();
			ClearHost();
			ClearRef();
			ClearTitle();
			ClearContentType();
			ClearCookie();
			ClearUserAgent();
			title_flag = 0;
			heading_flag = 0;
		}
		if(wait_num == 1){
			if((*it_pattern) == "GET"){
				get_str = GetGET(*it_result);
//				cout << get_str << endl;
			}
			if((*it_pattern) == "Host:"){
				host_str = GetHost(*it_result);
//				cout << host_str << endl;
			}
			if((*it_pattern) == "Referer:"){
				ref_str = GetRef(*it_result);
			}
			if((*it_pattern) == "Cookie:"){
				cookie_str = GetCookie(*it_result);
			}
			if((*it_pattern) == "User-Agent:"){
				user_agent_str = GetUserAgent(*it_result);
//				cout << user_agent_str << endl;
			}
			if((*it_pattern) == "<title" || (*it_pattern) == "<TITLE"){
				title_str = GetTitle(*it_result);
				if(title_str == "error!"){
					title_flag = 0;
				}else{
					title_flag = 1;
				}
			}
			if((*it_pattern) == "Content-Type:"){
				content_type_str = GetContentType(*it_result);
			}
			if((*it_pattern) == "<h1" || (*it_pattern) == "<h2" || (*it_pattern) == "<h3"){
				heading_flag = 1;
			}
			timestampmap->result_id[(*it_timestamp)] = (*it_result_id);
			timestampmap->timestamp[(*it_timestamp)] = (*it_timestamp);
			timestampmap->src_ip[(*it_timestamp)] = (*it_src_ip);
			timestampmap->dst_ip[(*it_timestamp)] = (*it_dst_ip);
			timestampmap->src_port[(*it_timestamp)] = (*it_src_port);
			timestampmap->dst_port[(*it_timestamp)] = (*it_dst_port);
			timestampmap->src_mac_addr[(*it_timestamp)] = (*it_src_mac_addr);
			timestampmap->dst_mac_addr[(*it_timestamp)] = (*it_dst_mac_addr);
			timestampmap->host[(*it_timestamp)] = host_str;
			timestampmap->url[(*it_timestamp)] = GetURL();
			timestampmap->title[(*it_timestamp)] = title_str;
			timestampmap->content_type[(*it_timestamp)] = content_type_str;
			if(title_flag == 0){
				timestampmap->title_flag[(*it_timestamp)] = 0;
			}else{
//				cout << id << endl;
				timestampmap->title_flag[(*it_timestamp)] = 1;
			}
			if(heading_flag == 0){
				timestampmap->heading_flag[(*it_timestamp)] = 0;
			}else{
				timestampmap->heading_flag[(*it_timestamp)] = 1;
			}
			timestampmap->ref[(*it_timestamp)] = ref_str;
			timestampmap->cookie[(*it_timestamp)] = cookie_str;
			timestampmap->secusec[(*it_timestamp)] = GetSecUSec(*it_unix_time);
			timestampmap->sec[(*it_timestamp)] = GetSec(*it_unix_time);
			timestampmap->usec[(*it_timestamp)] = GetUSec(*it_unix_time);
//			timestampmap->usec[(*it_timestamp)] = GetUSec(*it_timestamp);
			timestampmap->cookie[(*it_timestamp)] = cookie_str;
			timestampmap->user_agent[(*it_timestamp)] = user_agent_str;
			timestampmap->unique_id[(*it_timestamp)] = "";
			url_title[timestampmap->url[(*it_timestamp)]] = timestampmap->title[(*it_timestamp)];
			wait_num--;
		}else{
			if((*it_pattern) == "GET"){
				get_str = GetGET(*it_result);
//				cout << get_str << endl;
			}
			if((*it_pattern) == "Host:"){
				host_str = GetHost(*it_result);
			}
			if((*it_pattern) == "Referer:"){
				ref_str = GetRef(*it_result);
			}
			if((*it_pattern) == "Cookie:"){
				cookie_str = GetCookie(*it_result);
			}
			if((*it_pattern) == "User-Agent:"){
				user_agent_str = GetUserAgent(*it_result);
//				cout << user_agent_str << endl;
			}
			if((*it_pattern) == "<title" || (*it_pattern) == "<TITLE"){
				title_str = GetTitle(*it_result);
				if(title_str == "error!"){
					title_flag = 0;
				}else{
					title_flag = 1;
				}
			}
			if((*it_pattern) == "Content-Type:"){
				content_type_str = GetContentType(*it_result);
			}
			if((*it_pattern) == "<h1" || (*it_pattern) == "<h2" || (*it_pattern) == "<h3"){
				heading_flag = 1;
			}
			wait_num--;
		}
		
		++it_stream_id;
		++it_result_id;
		++it_timestamp;
		++it_src_ip;
		++it_dst_ip;
		++it_src_port;
		++it_dst_port;
		++it_src_mac_addr;
		++it_dst_mac_addr;
		++it_pattern;
		++it_result;
		++it_prefilter_log;
		++it_unix_time;
	}

	return 0;
}

int Url::Identify(){
	string client_str;
	string server_str;
	map<string, string>::iterator it = timestampmap->unique_id.begin();

	multimap<string, string> timestamp_id;
	multimap<string, string>::iterator it_timestamp_id;
	multimap<string, string>::iterator it_tmp;

	int title_insert_flag;
	int content_type_insert_flag;
	int heading_insert_flag;
	int search_num = 100;

	it = timestampmap->unique_id.begin();

	ClearClientMap();

	while(it != timestampmap->unique_id.end()){
		string id = (*it).first;
		timestamp_id.insert(pair<string, string>(timestampmap->timestamp[id], id));
		++it;
	}

//	cout << "IDENTIFY" << endl;

	it_timestamp_id = timestamp_id.begin();
	while(it_timestamp_id != timestamp_id.end()){
		string id = (*it_timestamp_id).second;

		string src_mac_addr = timestampmap->src_mac_addr[id];
//		cout << src_mac_addr << endl;

		if(timestampmap->dst_port[id] == "80"){
			if(timestampmap->url[id] != ""){
				clientmap->timestamp.insert(pair<string, string>(src_mac_addr, timestampmap->timestamp[id]));
				clientmap->src_ip.insert(pair<string, string>(src_mac_addr, timestampmap->src_ip[id]));
				clientmap->dst_ip.insert(pair<string, string>(src_mac_addr, timestampmap->dst_ip[id]));
				clientmap->src_port.insert(pair<string, string>(src_mac_addr, timestampmap->src_port[id]));
				clientmap->dst_port.insert(pair<string, string>(src_mac_addr, timestampmap->dst_port[id]));
				clientmap->url.insert(pair<string, string>(src_mac_addr, timestampmap->url[id]));
				clientmap->ref.insert(pair<string, string>(src_mac_addr, timestampmap->ref[id]));
				clientmap->cookie.insert(pair<string, string>(src_mac_addr, timestampmap->cookie[id]));
				clientmap->user_agent.insert(pair<string, string>(src_mac_addr, timestampmap->user_agent[id]));
				clientmap->host.insert(pair<string, string>(src_mac_addr, timestampmap->host[id]));
				clientmap->secusec.insert(pair<string, double>(src_mac_addr, timestampmap->secusec[id]));
				clientmap->sec.insert(pair<string, long>(src_mac_addr, timestampmap->sec[id]));
				clientmap->usec.insert(pair<string, long>(src_mac_addr, timestampmap->usec[id]));
				clientmap->erase_flag.insert(pair<string, int>(src_mac_addr, 0));
				clientmap->local_id.insert(pair<string, int>(src_mac_addr, 0));
				clientmap->debug.insert(pair<string, string>(src_mac_addr, ""));
				client_str = timestampmap->src_ip[id] + timestampmap->dst_ip[id] + timestampmap->src_port[id] + timestampmap->dst_port[id];
				int i = 0;
				server_str = "";
				title_insert_flag = 0;
				content_type_insert_flag = 0;
				heading_insert_flag = 0;
				it_tmp = it_timestamp_id;
//				it_tmp = it;
//				cout << "NEW URL" << endl;
//				cout << id << "\t" << idmap->url[id] << endl;
//				cout << client_str << endl;
				while(1){
//					cout << "SEARCH" << endl;
					++it_timestamp_id;
//					++it;
					if(it_timestamp_id == timestamp_id.end()){
//					if(it == idmap->unique_id.end()){
						if(title_insert_flag == 0){
							clientmap->title_flag.insert(pair<string, int>(src_mac_addr, 0));
							clientmap->title.insert(pair<string, string>(src_mac_addr, ""));
						}
						if(content_type_insert_flag == 0){
							clientmap->content_type.insert(pair<string, string>(src_mac_addr, ""));
						}
						if(heading_insert_flag == 0){
							clientmap->heading_flag.insert(pair<string, int>(src_mac_addr, 0));
						}
						break;
					}
					id = (*it_timestamp_id).second;
//					id = (*it).first;

//					string tmp_str = idmap->src_ip[id] + idmap->dst_ip[id] + idmap->src_port[id] + idmap->dst_port[id];
					if(client_str == timestampmap->src_ip[id] + timestampmap->dst_ip[id] + timestampmap->src_port[id] + timestampmap->dst_port[id]){
						if(title_insert_flag == 0){
							clientmap->title_flag.insert(pair<string, int>(src_mac_addr, 0));
							clientmap->title.insert(pair<string, string>(src_mac_addr, ""));
						}
						if(content_type_insert_flag == 0){
							clientmap->content_type.insert(pair<string, string>(src_mac_addr, ""));
						}
						if(heading_insert_flag == 0){
							clientmap->heading_flag.insert(pair<string, int>(src_mac_addr, 0));
						}
						break;
					}

					if(timestampmap->src_port[id] == "80"){
						server_str = timestampmap->dst_ip[id] + timestampmap->src_ip[id] + timestampmap->dst_port[id] + timestampmap->src_port[id];
//						cout << id << endl;
//						cout << server_str << "\t" << idmap->title_flag[id] << "\t" << title_insert_flag << endl;
						if(client_str == server_str && timestampmap->title_flag[id] == 1 && title_insert_flag == 0){
//							cout << idmap->dst_ip[id] << "\t" << idmap->src_ip[id] << "\t" << idmap->dst_port[id] << "\t" << idmap->src_port[id] << endl;
//							cout << idmap->title[id] << endl;
							clientmap->title_flag.insert(pair<string, int>(src_mac_addr, 1));
							clientmap->title.insert(pair<string, string>(src_mac_addr, timestampmap->title[id]));
							clientmap->heading_flag.insert(pair<string, int>(src_mac_addr, timestampmap->heading_flag[id]));
							title_insert_flag = 1;
							heading_insert_flag = 1;
						}
						if(client_str == server_str && content_type_insert_flag == 0){
							clientmap->content_type.insert(pair<string, string>(src_mac_addr, timestampmap->content_type[id]));
							content_type_insert_flag = 1;
						}
//						if(client_str == server_str && heading_insert_flag == 0){
//							clientmap->heading_flag.insert(pair<string, int>(src_mac_addr, 1));
//							heading_insert_flag = 1;
//						}
					}
					i++;
					if(i == search_num){
						if(title_insert_flag == 0){
							clientmap->title_flag.insert(pair<string, int>(src_mac_addr, 0));
							clientmap->title.insert(pair<string, string>(src_mac_addr, ""));
						}
						if(content_type_insert_flag == 0){
							clientmap->content_type.insert(pair<string, string>(src_mac_addr, ""));
						}
						if(heading_insert_flag == 0){
							clientmap->heading_flag.insert(pair<string, int>(src_mac_addr, 0));
						}
						break;
					}
				}
//				it = it_tmp;
				it_timestamp_id = it_tmp;
			}
//			it = it_tmp;
		}

//		++it;
		++it_timestamp_id;
	}

//	multimap<string, int>::iterator itt = url->clientmap->heading_flag.begin();
//	while(itt != url->clientmap->heading_flag.end()){
//		cout << (*itt).first << endl;
//		itt++;
//	}

	return 0;
}

string Url::CalBrowsingTime(long sec, long usec, long next_sec, long next_usec){
//string Url::CalBrowsingTime(string prev_time, string time){
	string tmp;
	stringstream ss, ss2, ss_check;
	ss.str("");
	ss.clear(stringstream::goodbit);
//	long prev_sec, prev_usec, sec, usec;
	long browsing_sec, browsing_usec;

//	int flag = 0;

//	for(unsigned int i = 0; i < prev_time.size(); i++){
//		tmp = prev_time[i];
//		if(tmp != "."){
//			ss << prev_time[i];
//			flag = 1;
//		}else{
//			if(flag == 0){
//				ss >> prev_sec;
//				ss.str("");
//				ss.clear(stringstream::goodbit);
//			}
//		}
//	}

	ss_check << usec;
	if(ss_check.str().size() != 6){
		ss << setw(6) << right << setfill('0') << usec;
//		ss << setw(6) << left << setfill('0') << usec;
		ss >> usec;
	}

	ss_check.str("");
	ss_check.clear(stringstream::goodbit);
	ss_check << next_usec;
	if(ss_check.str().size() != 6){
		ss2 << setw(6) << right << setfill('0') << next_usec;
//		ss2 << setw(6) << left << setfill('0') << next_usec;
		ss2 >> next_usec;
	}

//	ss2 << setw(6) << left << setfill('0') << ss.str();
//	ss2 >> prev_usec;
//	ss.str("");
//	ss.clear(stringstream::goodbit);
//	ss2.str("");
//	ss2.clear(stringstream::goodbit);
//	flag = 0;

//	for(unsigned int i = 0; i < time.size(); i++){
//		tmp = time[i];
//		if(tmp != "."){
//			ss << time[i];
//			flag = 1;
//		}else{
//			if(flag == 0){
//				ss >> sec;
//				ss.str("");
//				ss.clear(stringstream::goodbit);
//			}
//		}
//	}
//	ss2 << setw(6) << left << setfill('0') << ss.str();
//	ss2 >> usec;
//	ss.str("");
//	ss.clear(stringstream::goodbit);
//	ss2.str("");
//	ss2.clear(stringstream::goodbit);

	browsing_sec = next_sec - sec;
	if(next_usec > usec){
		browsing_usec = next_usec - usec;
	}else{
		browsing_sec--;
		browsing_usec = next_usec - usec + 1000000;
	}

//	browsing_sec = sec - prev_sec;
//	if(usec > prev_usec){
//		browsing_usec = usec - prev_usec;
//	}else{
//		browsing_sec--;
//		browsing_usec = usec - prev_usec;
//	}

	ss.str("");
	ss.clear(stringstream::goodbit);
	ss << browsing_sec << "." << browsing_usec;

	return ss.str();

}

int Url::MatchNumberInStream(vector<string>::iterator it){
//	stringstream ss;
//	vector<string>::iterator it_begin = stream_id.begin();
	string key_timestamp, comp_timestamp;
	int num = 1;
//	ss << (*it);
//	ss >> id;
	key_timestamp = (*it);
	while(it != timestamp.end()){
		++it;
		if(it == timestamp.end()){
			break;
		}
		comp_timestamp = (*it);
//		ss.str("");
//		ss.clear(stringstream::goodbit);
//		ss << (*it);
//		ss >> comp_id;
		if(key_timestamp == comp_timestamp){
			num++;
		}else{
			break;
		}
	}

	return num;
}


string Url::GetGET(string str){
	string get = "";
	string tmp = "";
	if(get_str != ""){
		get = "";
	}else{
		for(unsigned int i = 1; i < str.size() - 1; i++){
			tmp = str[i];
			if(tmp == " "){
				break;
			}
			get += str[i];
		}
	}

	return get;
}

string Url::GetRefHost(string str){
	string ref_host = "";
	string tmp = "";
	for(unsigned int i = 0; i < str.size(); i++){
		tmp = str[i];
		if(tmp == "/"){
			tmp = str[i+1];
			if(tmp != "/"){
				break;
			}else{
				ref_host += str[i];
				i = i + 1;
			}
		}
		ref_host += str[i];
	}

	return ref_host;
}

string Url::GetHost(string str){
	string host = "";
	string tmp = "";
	if(host_str != ""){
		host = "";
	}else{
		for(unsigned int i = 1; i < str.size() - 1; i++){
			tmp = str[i];
			if(tmp == "\r" || tmp == "\n"){
				break;
			}else if(tmp == "\\"){
				tmp = str[i+1];
				if(tmp == "0"){
					break;
				}
			}
			host += str[i];
		}
	}

	return host;
}

string Url::GetRef(string str){
	string ref;
	string tmp = "";
	tmp = str[5];
	if(tmp != "s"){
		tmp = "";
		for(unsigned int i = 8; i < str.size() - 1; i++){
			tmp = str[i];
			if(tmp == "\r" || tmp == "\n" || tmp == "\\"){
				break;
			}
			ref += str[i];
		}
	}else{
		tmp = "";
		for(unsigned int i = 1; i < str.size() - 1; i++){
//		for(unsigned int i = 9; i < str.size() - 1; i++){
			tmp = str[i];
			if(tmp == "\r" || tmp == "\n" || tmp == "\\"){
				break;
			}
			ref += str[i];
		}
	}

	return ref;
}

string Url::GetCookie(string str){
	string cookie;
	string tmp = "";
	string buf = "";
	for(unsigned int i = 1; i < str.size() - 1; i++){
		tmp = str[i];
		if(tmp == "\r" || tmp == "\n" || tmp == "\\"){
			cookie += buf;
			break;
		}
		if(tmp == ";"){
			buf += str[i];
			cookie += buf;
			buf = "";
		}else{
			buf += str[i];
		}
	}

	return cookie;
}

string Url::GetUserAgent(string str){
	string user_agent;
	string tmp = "";
	for(unsigned int i = 1; i < str.size() - 1; i++){
		tmp = str[i];
		if(tmp == "\r" || tmp == "\n" || tmp == "\\"){
			break;
		}
		user_agent += str[i];
	}

	return user_agent;
}

string Url::GetContentType(string str){
	string content_type;
	string tmp = "";
	for(unsigned int i = 1; i < str.size() - 1; i++){
		tmp = str[i];
		if(tmp == ";" || tmp == "\r" || tmp == "\n" || tmp == "\\"){
			break;
		}
		content_type += str[i];
	}
	
	return content_type;
}

string Url::GetURL(){
	string url;
	if(host_str != "" && get_str != ""){
		url = host_str + get_str;
	}else{
		url = "";
	}
	
	return url;
}

string Url::GetTitle(string str){
	string title;
	string tmp = "";
	int break_flag = 0;
	for(unsigned int i = 1; i < str.size(); i++){
		tmp = str[i];
		if(tmp == "<"){
			break_flag = 1;
			break;
		}
		title += str[i];
	}

	if(break_flag == 0){
		title = "error!";
	}

	return title;
}

double Url::GetSecUSec(string unix_time){
//long double Url::GetSecUSec(string unix_time){
	long double secusec;
	stringstream ss;
	ss.str("");
	ss.clear(stringstream::goodbit);
//	ss << unix_time;
	string buf = "";
	for(unsigned int i = 8; i < unix_time.size(); i++){
		buf = unix_time[i];
		ss << unix_time[i];
	}
	ss >> secusec;

	return secusec;
}

long Url::GetSec(string unix_time){
	long sec;
	stringstream ss;
	ss.str("");
	ss.clear(stringstream::goodbit);
	string buf = "";
	for(unsigned int i = 0; i < unix_time.size(); i++){
		buf = unix_time[i];
		if(buf == "."){
			break;
		}
		ss << unix_time[i];
	}
	ss >> sec;

	return sec;
}

long Url::GetUSec(string unix_time){
	long usec;
	stringstream ss;
	ss.str("");
	ss.clear(stringstream::goodbit);
	string buf = "";
	for(unsigned int i = 0; i < unix_time.size(); i++){
		buf = unix_time[i];
		if(buf == "."){
			for(unsigned int j = i + 1; j < unix_time.size(); j++){
				ss << unix_time[j];
			}
			if(ss.str().size() != 6){
				for(unsigned int j = ss.str().size(); j < 6; j++){
					ss << "0";
				}
			}
			ss >> usec;
			break;
		}
	}

	return usec;
}

string Url::GetURLQuery(string str){
//	string url = clientmap->url[src_mac_addr];
	string query = "";
	vector<string> se;
	vector<string>::iterator it;
	se.push_back("www.google.co.jp/search?");
	se.push_back("search.yahoo.co.jp/search");
	se.push_back("www.bing.com/search");

	string buf = "";
	string nbuf = "";
	string fin = "";

	it = se.begin();
	while(it != se.end()){
		string::size_type index = str.find(*it);
		if(index != string::npos){
			for(unsigned int i = 0; i < str.size() - 1; i++){
				buf = str[i];
				nbuf = str[i+1];
				if((buf == "?" || buf == "&") && (nbuf == "q" || nbuf == "p")){
					for(unsigned int j = i; j < str.size() - 1; j++){
						fin = str[j+3];
						if(fin == "&"){
							break;
						}
						query += str[j+3];
					}
					break;
				}
			}
			break;
		}
		++it;
	}

	return query;
}

string Url::GetRefQuery(string str){
//	string url = dstmacmap->url[src_mac_addr];
	string query = "";
	vector<string> se;
	vector<string>::iterator it;
	se.push_back("www.google.co.jp/url?");

	string buf = "";
	string nbuf = "";
	string fin = "";

	it = se.begin();
	while(it != se.end()){
		string::size_type index = str.find(*it);
		if(index != string::npos){
			for(unsigned int i = 0; i < str.size() - 1; i++){
				buf = str[i];
				nbuf = str[i+1];
				if((buf == "?" || buf == "&") && nbuf == "q"){
					for(unsigned int j = i; j < str.size() - 1; j++){
						fin = str[j+3];
						if(fin == "&"){
							break;
						}
						query += str[j+3];
					}
					break;
				}
			}
			break;
		}
		++it;
	}

	return query;
}

int Url::CheckSE(string url, string host){
	int match;
	if(host == "www.google.co.jp" || host == "search.yahoo.co.jp" || host == "www.bing.com"){
		string::size_type index = url.find("search?");
		if(index != string::npos){
			match = 1;
		}else{
			match = 0;
		}
	}else{
		match = 0;
	}

	if(url == "https://www.google.co.jp/"){
		match = 1;
	}

	return match;
}

int Url::CheckGoogle(string url, string host){
	int match;

	if(host == "www.google.co.jp"){
		string::size_type index = url.find("www.google.co.jp/url?");
		if(index != string::npos){
			match = 1;
		}else{
			match = 0;
		}
	}else{
		match = 0;
	}

	return match;
}

string Url::ExtractURLForGoogle(string str){
	string url = "";
	string tmp[5];
	string buf = "";
	stringstream ss;
	ss.str("");
	ss.clear(stringstream::goodbit);
	int fin = 0;
	int flag = 0;

//	cout << "STR:" << str << endl;

	for(unsigned int i = 0; i < str.size() - 4; i++){
		tmp[0] = str[i];
		tmp[1] = str[i+1];
		tmp[2] = str[i+2];
		tmp[3] = str[i+3];
		tmp[4] = str[i+4];
		if(tmp[0] == "&" && tmp[1] == "u" && tmp[2] == "r" && tmp[3] == "l" && tmp[4] == "=" ){
			tmp[1] = str[i+9];
			if(tmp[1] == ":"){
				flag = 1;
				break;
			}
			tmp[0] = "";
			buf = "";
			for(unsigned int j = i + 18; j < str.size(); j++){
				tmp[0] = str[j];
				if(tmp[0] == "&" || tmp[0] == "\n" || tmp[0] == "\r"){
					fin = 1;
					break;
				}else{
					buf += tmp[0];
				}
			}
			if(fin == 1){
				break;
			}
		}
	}

	for(unsigned int i = 0; i < buf.size(); i++){
		tmp[0] = buf[i];
		tmp[1] = buf[i+1];
		tmp[2] = buf[i+2];
		if(tmp[0] == "2" && tmp[1] == "5"){
			i = i+1;
		}else if(tmp[0] == "%" && tmp[1] == "2" && tmp[2] == "F"){
			i = i+2;
			url += "/";
		}else{
			url += buf[i];
		}
	}

	if(flag == 1){
		url = "";
	}

	return url;
}

void Url::ClearGET(){
	get_str = "";
}

void Url::ClearHost(){
	host_str = "";
}

void Url::ClearRef(){
	ref_str = "";
}

void Url::ClearCookie(){
	cookie_str = "";
}
void Url::ClearUserAgent(){
	user_agent_str = "";
}
void Url::ClearTitle(){
	title_str = "";
}

void Url::ClearContentType(){
	content_type_str = "";
}

void Url::ClearVector(){
	stream_id.clear();
	result_id.clear();
	timestamp.clear();
	src_ip.clear();
	dst_ip.clear();
	src_port.clear();
	dst_port.clear();
	src_mac_addr.clear();
	dst_mac_addr.clear();
	pattern.clear();
	result_string.clear();
	prefilter_log.clear();
	unix_time.clear();
}

void Url::ClearTimestampMap(){
	timestampmap->result_id.clear();
	timestampmap->timestamp.clear();
	timestampmap->src_ip.clear();
	timestampmap->dst_ip.clear();
	timestampmap->src_port.clear();
	timestampmap->dst_port.clear();
	timestampmap->src_mac_addr.clear();
	timestampmap->dst_mac_addr.clear();
	timestampmap->url.clear();
	timestampmap->title.clear();
	timestampmap->ref.clear();
	timestampmap->cookie.clear();
	timestampmap->user_agent.clear();
	timestampmap->host.clear();
	timestampmap->secusec.clear();
	timestampmap->sec.clear();
	timestampmap->usec.clear();
	timestampmap->unique_id.clear();
	timestampmap->title_flag.clear();
	timestampmap->content_type.clear();
	timestampmap->heading_flag.clear();
}

//void Url::ClearIdMap(){
//	idmap->result_id.clear();
//	idmap->timestamp.clear();
//	idmap->src_ip.clear();
//	idmap->dst_ip.clear();
//	idmap->src_port.clear();
//	idmap->dst_port.clear();
////	idmap->src_mac_addr.clear();
////	idmap->dst_mac_addr.clear();
//	idmap->url.clear();
//	idmap->title.clear();
//	idmap->ref.clear();
//	idmap->cookie.clear();
//	idmap->host.clear();
//	idmap->secusec.clear();
//	idmap->sec.clear();
//	idmap->usec.clear();
//	idmap->unique_id.clear();
//	idmap->title_flag.clear();
//	idmap->content_type.clear();
//	idmap->heading_flag.clear();
//}

void Url::ClearClientMap(){
	clientmap->timestamp.clear();
	clientmap->src_ip.clear();
	clientmap->dst_ip.clear();
	clientmap->src_port.clear();
	clientmap->dst_port.clear();
//	clientmap->src_mac_addr.clear();
	clientmap->url.clear();
	clientmap->title.clear();
	clientmap->ref.clear();
	clientmap->cookie.clear();
	clientmap->user_agent.clear();
	clientmap->host.clear();
	clientmap->secusec.clear();
	clientmap->sec.clear();
	clientmap->usec.clear();
	clientmap->timestamp_def.clear();
	clientmap->title_flag.clear();
	clientmap->content_type.clear();
	clientmap->heading_flag.clear();
	clientmap->erase_flag.clear();

	clientmap->local_id.clear();
	clientmap->debug.clear();
}

void Url::SetTmpTimestamp(string timestamp){
	tmptimestamp = timestamp;
	exit_new_history = 1;
}
