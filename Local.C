#include "Local.H"
#include "BTGlobal.H"

Local::Local(){
}

int Local::Show(){
	multimap<string, string>::iterator it_timestamp = url->clientmap->timestamp.begin();
	multimap<string, string>::iterator it_src_ip = url->clientmap->src_ip.begin();
	multimap<string, string>::iterator it_dst_ip = url->clientmap->dst_ip.begin();
	multimap<string, string>::iterator it_src_port = url->clientmap->src_port.begin();
	multimap<string, string>::iterator it_dst_port = url->clientmap->dst_port.begin();
	multimap<string, string>::iterator it_url = url->clientmap->url.begin();
	multimap<string, string>::iterator it_ref = url->clientmap->ref.begin();
	multimap<string, string>::iterator it_cookie = url->clientmap->cookie.begin();
	multimap<string, string>::iterator it_user_agent = url->clientmap->user_agent.begin();
	multimap<string, string>::iterator it_host = url->clientmap->host.begin();
	multimap<string, double>::iterator it_secusec = url->clientmap->secusec.begin();
	multimap<string, long>::iterator it_sec = url->clientmap->sec.begin();
	multimap<string, long>::iterator it_usec = url->clientmap->usec.begin();
	multimap<string, double>::iterator it_timestamp_def = url->clientmap->timestamp_def.begin();
	multimap<string, int>::iterator it_title_flag = url->clientmap->title_flag.begin();
	multimap<string, string>::iterator it_title = url->clientmap->title.begin();
	multimap<string, string>::iterator it_content_type = url->clientmap->content_type.begin();
	multimap<string, int>::iterator it_erase_flag = url->clientmap->erase_flag.begin();
	multimap<string, int>::iterator it_heading_flag = url->clientmap->heading_flag.begin();
	multimap<string, int>::iterator it_local_id = url->clientmap->local_id.begin();

	multimap<string, string> timestamp_url;
	multimap<string, string>::iterator it_timestamp_url;
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

	int max_id = 1;

	while(it_url != url->clientmap->url.end()){
		timestamp_url.insert(pair<string, string>((*it_timestamp).second, (*it_url).second));
		timestamp_erase_flag.insert(pair<string, int>((*it_timestamp).second, (*it_erase_flag).second));
		timestamp_title_flag.insert(pair<string, int>((*it_timestamp).second, (*it_title_flag).second));
		timestamp_title.insert(pair<string, string>((*it_timestamp).second, (*it_title).second));
		timestamp_ref.insert(pair<string, string>((*it_timestamp).second, (*it_ref).second));
		timestamp_cookie.insert(pair<string, string>((*it_timestamp).second, (*it_cookie).second));
		timestamp_user_agent.insert(pair<string, string>((*it_timestamp).second, (*it_user_agent).second));
		timestamp_src_ip.insert(pair<string, string>((*it_timestamp).second, (*it_src_ip).second));
		timestamp_content_type.insert(pair<string, string>((*it_timestamp).second, (*it_content_type).second));
		timestamp_local_id.insert(pair<string, int>((*it_timestamp).second, (*it_local_id).second));

		stringstream ss;
		ss.str("");
		ss.clear(stringstream::goodbit);
		ss << (*it_local_id).second;
		int comp = 0;
		ss >> comp;
		if(max_id < comp){
			max_id = comp;
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
	}

	cout << "MAX" << max_id << endl;
	for(int i = 1; i <= max_id; i++){
		it_timestamp_url = timestamp_url.begin();
		it_timestamp_title = timestamp_title.begin();
		it_timestamp_ref = timestamp_ref.begin();
		it_timestamp_cookie = timestamp_cookie.begin();
		it_timestamp_user_agent = timestamp_user_agent.begin();
		it_timestamp_src_ip = timestamp_src_ip.begin();
		it_timestamp_erase_flag = timestamp_erase_flag.begin();
		it_timestamp_title_flag = timestamp_title_flag.begin();
		it_timestamp_content_type = timestamp_content_type.begin();
		it_timestamp_local_id = timestamp_local_id.begin();

		while(it_timestamp_url != timestamp_url.end()){
//			stringstream ss;
//			ss.str("");
//			ss.clear(stringstream::goodbit);
//			ss << i;
			if(i == (*it_timestamp_local_id).second){
//			if(ss.str() == (*it_timestamp_local_id).second){
				cout << (*it_timestamp_local_id).second << "\t" << (*it_timestamp_local_id).first << "\t" << (*it_timestamp_url).second << endl;
				cout << (*it_timestamp_cookie).second << endl;
				cout << (*it_timestamp_ref).second << endl;
			}
			it_timestamp_url++;
			it_timestamp_local_id++;
			it_timestamp_cookie++;
			it_timestamp_ref++;
			
		}
	}

	return 0;
}

int Local::Identify(){
	multimap<string, string>::iterator it_timestamp = url->clientmap->timestamp.begin();
	multimap<string, string>::iterator it_src_ip = url->clientmap->src_ip.begin();
	multimap<string, string>::iterator it_dst_ip = url->clientmap->dst_ip.begin();
	multimap<string, string>::iterator it_src_port = url->clientmap->src_port.begin();
	multimap<string, string>::iterator it_dst_port = url->clientmap->dst_port.begin();
	multimap<string, string>::iterator it_url = url->clientmap->url.begin();
	multimap<string, string>::iterator it_ref = url->clientmap->ref.begin();
	multimap<string, string>::iterator it_cookie = url->clientmap->cookie.begin();
	multimap<string, string>::iterator it_user_agent = url->clientmap->user_agent.begin();
	multimap<string, string>::iterator it_host = url->clientmap->host.begin();
	multimap<string, double>::iterator it_secusec = url->clientmap->secusec.begin();
	multimap<string, long>::iterator it_sec = url->clientmap->sec.begin();
	multimap<string, long>::iterator it_usec = url->clientmap->usec.begin();
	multimap<string, double>::iterator it_timestamp_def = url->clientmap->timestamp_def.begin();
	multimap<string, int>::iterator it_title_flag = url->clientmap->title_flag.begin();
	multimap<string, string>::iterator it_title = url->clientmap->title.begin();
	multimap<string, string>::iterator it_content_type = url->clientmap->content_type.begin();
	multimap<string, int>::iterator it_erase_flag = url->clientmap->erase_flag.begin();
	multimap<string, int>::iterator it_heading_flag = url->clientmap->heading_flag.begin();
	multimap<string, int>::iterator it_local_id = url->clientmap->local_id.begin();

	int user_id = 1;
	int search_num = 10;
	int tmp_id;

	if(url->clientmap->url.size() == 1){
		(*it_local_id).second = user_id;
	}else{
		while(it_url != url->clientmap->url.end()){
			string url_str;
			stringstream ss;
			ss.str("");
			ss.clear(stringstream::goodbit);
	
//			user-agent
//			if(user_agent_map[(*it_user_agent).second] == ""){
//				ss << user_id;
//				user_agent_map[(*it_user_agent).second] = ss.str();
//				(*it_local_id).second = user_agent_map[(*it_user_agent).second];
//				user_id++;
//			}else{
//				(*it_local_id).second = user_agent_map[(*it_user_agent).second];
//			}

			if((*it_local_id).second == 0){
				(*it_local_id).second = user_id;
				user_id++;
			}
	
			url_str = (*it_url).second;
			tmp_id = (*it_local_id).second;
			int i = 0;
			multimap<string, string>::iterator tmp_it_ref = it_ref;
			multimap<string, int>::iterator tmp_it_local_id = it_local_id;
			while(1){
//			for(int i = 0; i < search_num; i++){
				if(i == search_num){
					break;
				}
				it_ref++;
				it_local_id++;
				if(it_ref == url->clientmap->ref.end()){
					break;
				}
				if((*it_ref).second == url_str){
//					(*it_local_id).second = tmp_id;
				}
				i++;
			}

			it_ref = tmp_it_ref;
			it_local_id = tmp_it_local_id;
			it_timestamp++;
			it_src_ip++;
			it_dst_ip++;
			it_src_port++;
			it_dst_port++;
			it_url++;
			it_ref++;
			it_local_id++;
			it_cookie++;
			it_user_agent++;
			it_host++;
			it_secusec++;
			it_sec++;
			it_usec++;
			if(url->clientmap->timestamp_def.size() != 0){
				it_timestamp_def++;
			}
			it_title_flag++;
			it_title++;
			it_content_type++;
			it_erase_flag++;
			it_heading_flag++;
		}
	}

	return 0;
}

int Local::ReconstructByRef(){
	multimap<string, int>::iterator it_local_id = url->clientmap->local_id.end();
	multimap<string, string>::iterator it_cookie = url->clientmap->cookie.end();
	multimap<string, string>::iterator it_url = url->clientmap->url.end();
	multimap<string, string>::iterator it_ref = url->clientmap->ref.end();

	map<string, int>::iterator it_cookie_local_id;
	map<string, int> cookie_local_id;
	map<string, string> parsed_map;
	map<string, string> tar_parsed_map;
	map<string, string>::iterator it;
//	multimap<int, int>::iterator it_id2id;
//	multimap<int, int> id2id;
	map<int, int>::iterator it_id2id;
	map<int, int> id2id;

	multimap<string, int>::iterator it_local_id_tmp;
	multimap<string, string>::iterator it_cookie_tmp;
	multimap<string, string>::iterator it_url_tmp;

	while(it_ref != url->clientmap->ref.begin()){
		it_ref--;
		it_url--;
		it_local_id--;
		it_cookie--;

		string url_str = (*it_url).second;
		string ref_str = (*it_ref).second;
		string cookie_str = (*it_cookie).second;
		int local_id_num = (*it_local_id).second;

		it_local_id_tmp = it_local_id;
		it_url_tmp = it_url;
		it_cookie_tmp = it_cookie;
		int flag = 0;
		while(it_url != url->clientmap->url.begin()){
			it_cookie--;
			it_url--;
			it_local_id--;
			if(ref_str == (*it_url).second){
				map<string, string> map1, map2;
				map<string, string>::iterator it_map1, it_map2;

				map1 = filter->GetCookieVarietyValue(cookie_str);
				map2 = filter->GetCookieVarietyValue((*it_cookie).second);

				it_map1 = map1.begin();
				while(it_map1 != map1.end()){
					if(map2[(*it_map1).first] != ""){
						if(map2[(*it_map1).first] != (*it_map1).second){
							flag = 1;
							break;
						}
					}
					it_map1++;
				}
				if(flag == 1){
					flag = 0;
					break;
				}

//				if((*it_url).second == "www.yahoo.co.jp/"){
//					break;
//				}
				if(id2id[local_id_num] == 0){
					id2id[local_id_num] = (*it_local_id).second;
//					cout << local_id_num << "\t" << (*it_local_id).second << endl;
//					id2id.insert(pair<int, int>(local_id_num, (*it_local_id).second));
				}
				break;
			}
		}

		it_local_id = it_local_id_tmp;
		it_url = it_url_tmp;
		it_cookie = it_cookie_tmp;
//		it_cookie_tmp = it_cookie;

	}

	it_id2id = id2id.end();
	while(it_id2id != id2id.begin()){
		--it_id2id;
		int num = (*it_id2id).first;
		while(1){
			if(id2id[num] != 0 && num != id2id[num]){
				num = id2id[num];
			}else{
				id2id[(*it_id2id).first] = num;
				break;
			}
		}
	}

	it_local_id = url->clientmap->local_id.end();
	while(it_local_id != url->clientmap->local_id.begin()){
		it_local_id--;
		if(id2id[(*it_local_id).second] != 0){
			(*it_local_id).second = id2id[(*it_local_id).second];
		}
	}

//	int id_buf;
//	int max_id = 1;
//	it_id2id = id2id.end();
//	while(it_id2id != id2id.begin()){
//		if(it_id2id == id2id.end()){
//			it_id2id--;
//			id_buf = (*it_id2id).first;
//			stringstream ss;
//			ss.str("");
//			ss.clear(stringstream::goodbit);
//			ss << (*it_id2id).second;
//			int comp_id;
//			ss >> comp_id;
//			if(max_id < comp_id){
//				max_id = comp_id;
//			}
//		}else{
//			it_id2id--;
//			if(id_buf == (*it_id2id).first){
//				stringstream ss;
//				ss.str("");
//				ss.clear(stringstream::goodbit);
//				ss << (*it_id2id).second;
//				int comp_id;
//				ss >> comp_id;
//				if(max_id < comp_id){
//					max_id = comp_id;
//				}
//			}else{
//				it_id2id++;
//				it_local_id = url->clientmap->local_id.begin();
//				while(it_local_id != url->clientmap->local_id.end()){
//					if((*it_local_id).second == (*it_id2id).first){
////						stringstream ss;
////						ss.str("");
////						ss.clear(stringstream::goodbit);
////						ss << max_id;
////						(*it_local_id).second = ss.str();
//						(*it_local_id).second = max_id;
//					}
//					it_local_id++;
//				}
//				it_id2id--;
//				id_buf = (*it_id2id).first;
//				max_id = 1;
//				stringstream ss;
//				ss.str("");
//				ss.clear(stringstream::goodbit);
//				ss << (*it_id2id).second;
//				int comp_id;
//				ss >> comp_id;
//				if(max_id < comp_id){
//					max_id = comp_id;
//				}
//			}
//			if(it_id2id == id2id.begin()){
//				it_local_id = url->clientmap->local_id.begin();
//				while(it_local_id != url->clientmap->local_id.end()){
//					if((*it_local_id).second == (*it_id2id).first){
////						stringstream ss;
////						ss.str("");
////						ss.clear(stringstream::goodbit);
////						ss << max_id;
////						(*it_local_id).second = ss.str();
//						(*it_local_id).second = max_id;
//					}
//					it_local_id++;
//				}
//			}
//		}
//	}


	return 0;
}

int Local::ReconstructByCookie(){
	multimap<string, int>::iterator it_local_id = url->clientmap->local_id.begin();
	multimap<string, string>::iterator it_cookie = url->clientmap->cookie.begin();
	multimap<string, string>::iterator it_url = url->clientmap->url.begin();

	map<string, int>::iterator it_cookie_local_id;
	map<string, int> cookie_local_id;
	map<string, string> parsed_map;
	map<string, string>::iterator it;
	multimap<int, int>::iterator it_id2id;
	multimap<int, int> id2id;

	while(it_cookie != url->clientmap->cookie.end()){
		parsed_map = CookieParseURLLevel((*it_cookie).second);
		it = parsed_map.begin();
		while(it != parsed_map.end()){
			if(cookie_local_id[(*it).first] == 0 || cookie_local_id[(*it).first] == (*it_local_id).second){
				cookie_local_id[(*it).first] = (*it_local_id).second;
			}else{
//				cout << "URL\t" << (*it_url).second << endl;
//				cout << "COO\t" << (*it).first << endl;
				id2id.insert(pair<int, int>((*it_local_id).second, cookie_local_id[(*it).first]));
			}
			it++;
		}

//		cout << "\t" << (*it_cookie).second << endl;
		parsed_map = CookieParse((*it_cookie).second);
//		parsed_map = CookieParseURLLevel((*it_cookie).second);
		it = parsed_map.begin();
		while(it != parsed_map.end()){
//			cout << (*it).first << endl;
//			string::size_type index = ((*it).first).find("id");
//			string::size_type index2 = ((*it).first).find("Id");
//			string::size_type index3 = ((*it).first).find("ID");
//			if(((*it).first).size() > 15 && (index != string::npos || index2 != string::npos || index3 != string::npos)){
//			cout << (*it_url).second << endl;
//			cout << (*it).first << "\t" << cookie_local_id[(*it).first] << endl;

//			if(((*it).first).size() > 15){
			if(GetCookieValueNum((*it).first) > 20){
				if(cookie_local_id[(*it).first] == 0 || cookie_local_id[(*it).first] == (*it_local_id).second){
					cookie_local_id[(*it).first] = (*it_local_id).second;
				}else{
//					cout << "URL\t" << (*it_url).second << endl;
//					cout << "COO\t" << (*it).first << endl;
					id2id.insert(pair<int, int>((*it_local_id).second, cookie_local_id[(*it).first]));
				}
			}
			it++;
		}

		it_local_id++;
		it_cookie++;
		it_url++;
	}

	int id_buf;
	int max_id = 1;
	it_id2id = id2id.end();
	while(it_id2id != id2id.begin()){
		if(it_id2id == id2id.end()){
			it_id2id--;
			id_buf = (*it_id2id).first;
			stringstream ss;
			ss.str("");
			ss.clear(stringstream::goodbit);
			ss << (*it_id2id).second;
			int comp_id;
			ss >> comp_id;
			if(max_id < comp_id){
				max_id = comp_id;
			}
		}else{
			it_id2id--;
			if(id_buf == (*it_id2id).first){
				stringstream ss;
				ss.str("");
				ss.clear(stringstream::goodbit);
				ss << (*it_id2id).second;
				int comp_id;
				ss >> comp_id;
				if(max_id < comp_id){
					max_id = comp_id;
				}
			}else{
				it_id2id++;
				it_local_id = url->clientmap->local_id.begin();
				while(it_local_id != url->clientmap->local_id.end()){
					if((*it_local_id).second == (*it_id2id).first){
//						stringstream ss;
//						ss.str("");
//						ss.clear(stringstream::goodbit);
//						ss << max_id;
//						(*it_local_id).second = ss.str();
						(*it_local_id).second = max_id;
					}
					it_local_id++;
				}
				it_id2id--;
				id_buf = (*it_id2id).first;
				max_id = 1;
				stringstream ss;
				ss.str("");
				ss.clear(stringstream::goodbit);
				ss << (*it_id2id).second;
				int comp_id;
				ss >> comp_id;
				if(max_id < comp_id){
					max_id = comp_id;
				}
			}
			if(it_id2id == id2id.begin()){
				it_local_id = url->clientmap->local_id.begin();
				while(it_local_id != url->clientmap->local_id.end()){
					if((*it_local_id).second == (*it_id2id).first){
//						stringstream ss;
//						ss.str("");
//						ss.clear(stringstream::goodbit);
//						ss << max_id;
//						(*it_local_id).second = ss.str();
						(*it_local_id).second = max_id;
					}
					it_local_id++;
				}
			}
		}
	}


	return 0;
}

map<string, string> Local::CookieParse(string cookie){
	map<string, string> map;

	string str = cookie;
	string buf = "";
	string tmp = "";

	vector<string> vec;
	vector<string>::iterator it;

	for(unsigned int i = 0; i < str.size(); i++){
		tmp = str[i];
		if(tmp == "@"){
			tmp = str[i+1];
			if(tmp == "%"){
				if(buf != ""){
					vec.push_back(buf);
					buf = "";
				}
				i++;
			}else{
				tmp = str[i];
				buf += tmp;
			}
		}else{
			buf += tmp;
		}
	}
	if(buf != ""){
		vec.push_back(buf);
	}

	it = vec.begin();
	str = "";
	buf = "";
	while(it != vec.end()){
		str += *it;
		str += "; ";
		it++;
	}


	if(vec.size() == 0){
		str = cookie;
	}

	for(unsigned int i = 0; i < str.size(); i++){
		tmp = str[i];
		if(tmp == ";"){
			tmp = str[i+1];
			if(tmp == " "){
				if(buf != ""){
					map[buf] = "";
//					cout << buf << endl;
					buf = "";
				}
				i++;
			}
		}else{
			buf += tmp;
		}
	}
	if(buf != ""){
		map[buf] = "";
	}

	return map;
}

map<string, string> Local::CookieParseURLLevel(string cookie){
	map<string, string>::iterator it;
	map<string, string> map;

	string str = cookie;
	string buf = "";
	string tmp = "";
	for(unsigned int i = 0; i < str.size(); i++){
		tmp = str[i];
		if(tmp == "@"){
			tmp = str[i+1];
			if(tmp == "%"){
				if(buf != ""){
					map[buf] = "";
					buf = "";
				}
				i++;
			}else{
				buf += str[i];
			}
		}else{
			buf += tmp;
		}
	}
	if(buf != ""){
		map[buf] = "";
	}

	it = map.begin();
	while(it != map.end()){
//		cout << "COOKIE" << (*it).first << endl;
		it++;
	}
//	cout << endl;

	return map;
}

int Local::GetCookieValueNum(string cookie){
	string str = cookie;
	string buf = "";
	string tmp = "";
	int flag = 0;
	for(unsigned int i = 0; i < str.size(); i++){
		tmp = str[i];
		if(flag == 1){
			buf += tmp;
		}
		if(tmp == "="){
			buf = "";
			flag = 1;
		}
	}

	int num = buf.size();

	return num;
}
