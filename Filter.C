#include "Filter.H"
#include "BTGlobal.H"

Filter::Filter(){
}

int Filter::Erase(){
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
	multimap<string, string>::iterator it_debug = url->clientmap->debug.begin();


	string str;

	vector<string> vec = LoadFocusHost();
	vector<string>::iterator it = vec.begin();

	while(it_timestamp != url->clientmap->timestamp.end()){
		if(url->CheckGoogle((*it_url).second, (*it_host).second)){
			(*it_erase_flag).second = 0;
		}
		if((*it_erase_flag).second == 1){
			url->clientmap->timestamp.erase(it_timestamp++);
			url->clientmap->src_ip.erase(it_src_ip++);
			url->clientmap->dst_ip.erase(it_dst_ip++);
			url->clientmap->src_port.erase(it_src_port++);
			url->clientmap->dst_port.erase(it_dst_port++);
			str = (*it_cookie).second;
			if(it_cookie != url->clientmap->cookie.begin() && (*it_cookie).second != ""){
				it = vec.begin();
				for(unsigned int i = 0; i < vec.size(); i++){
					string::size_type index = ((*it_host).second.find(*it));
					if(index != string::npos && (*it_cookie).second != ""){
						vector<string> pre_vec;
						vector<string> now_vec;
						vector<string>::iterator it_pre_vec;
						vector<string>::iterator it_now_vec;
						map<string, string> pre_map;
						map<string, string> now_map;
						map<string, string>::iterator it_pre_map;
						map<string, string>::iterator it_now_map;
						now_vec = GetCookieVariety((*it_cookie).second);
						it_cookie--;
//						cout << (*it_cookie).second << endl;
						pre_vec = GetCookieVariety((*it_cookie).second);
						it_cookie++;

						int match = 0;
						int flag = 0;
						it_pre_vec = pre_vec.begin();
						while(it_pre_vec != pre_vec.end()){
							it_now_vec = now_vec.begin();
							while(it_now_vec != now_vec.end()){
//								cout << (*it_pre_vec) << "\t" << (*it_now_vec) << endl;
								if((*it_pre_vec) == (*it_now_vec)){
									match = 1;
								}
								it_now_vec++;
							}
							it_pre_vec++;
						}
						if(match == 1){
							now_map = local->CookieParse((*it_cookie).second);
							it_cookie--;
							pre_map = local->CookieParse((*it_cookie).second);
							it_cookie++;
							it_pre_map = pre_map.begin();
							while(it_pre_map != pre_map.end()){
								it_now_map = now_map.begin();
								while(it_now_map != now_map.end()){
//									cout << (*it_pre_map).first << "\t" << (*it_now_map).first << endl;
									if((*it_pre_map).first == (*it_now_map).first){
										flag = 1;
									}
									it_now_map++;
								}
								it_pre_map++;
							}
						}

						if(match == 0 || flag == 1){
							it_url--;
							index = ((*it_ref).second).find((*it_url).second);
							if(index != string::npos){
								it_cookie--;
								(*it_cookie).second += "@%";
								(*it_cookie).second += str;
								it_cookie++;
//								it_url--;
//								it_url++;
								it_url++;
							}else{
								it_url++;
							}
						}
						break;
					}
					++it;
				}
			}
			url->clientmap->cookie.erase(it_cookie++);
			url->clientmap->url.erase(it_url++);
			url->clientmap->ref.erase(it_ref++);
			url->clientmap->user_agent.erase(it_user_agent++);
			url->clientmap->host.erase(it_host++);
			url->clientmap->secusec.erase(it_secusec++);
			url->clientmap->sec.erase(it_sec++);
			url->clientmap->usec.erase(it_usec++);
			if(url->clientmap->timestamp_def.size() != 0){
				url->clientmap->timestamp_def.erase(it_timestamp_def++);
			}
			url->clientmap->title_flag.erase(it_title_flag++);
			url->clientmap->title.erase(it_title++);
			url->clientmap->content_type.erase(it_content_type++);
			url->clientmap->erase_flag.erase(it_erase_flag++);
			url->clientmap->heading_flag.erase(it_heading_flag++);
			url->clientmap->local_id.erase(it_local_id++);
			url->clientmap->debug.erase(it_debug++);
		}else{
			it_timestamp++;
			it_src_ip++;
			it_dst_ip++;
			it_src_port++;
			it_dst_port++;
			it_url++;
			it_ref++;
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
			it_local_id++;
			it_debug++;
		}
	}

	return 0;

}

int Filter::EraseGoogle(){
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
	multimap<string, string>::iterator it_debug = url->clientmap->debug.begin();

	int search_num = 100;

	while(it_timestamp != url->clientmap->timestamp.end()){
		if(url->CheckGoogle((*it_url).second, (*it_host).second)){
			string url_str = url->ExtractURLForGoogle((*it_url).second);
//					cout << "URL" << url_str << endl;
//					cout << (*it_url).second << endl;
			string cookie = (*it_cookie).second;
			multimap<string, string>::iterator tmp_it_url = it_url;
			multimap<string, string>::iterator tmp_it_cookie = it_cookie;
			int i = 0;
			while(1){
				++it_url;
				++it_cookie;
				if(it_url == url->clientmap->url.end()){
					break;
				}
//				cout << (*it_url).second << "\t" << url_str << endl;
				string::size_type index = ((*it_url).second).find(url_str);
				if(index != string::npos){
//				if(url_str == (*it_url).second){
//					cout << "MATCH:" << url_str << endl;
					(*it_cookie).second += "@%";
//					(*it_cookie).second += "; ";
					(*it_cookie).second += cookie;
				}
				if(i == search_num){
					break;
				}
				i++;
			}
			it_url = tmp_it_url;
			it_cookie = tmp_it_cookie;
			url->clientmap->timestamp.erase(it_timestamp++);
			url->clientmap->src_ip.erase(it_src_ip++);
			url->clientmap->dst_ip.erase(it_dst_ip++);
			url->clientmap->src_port.erase(it_src_port++);
			url->clientmap->dst_port.erase(it_dst_port++);
			url->clientmap->cookie.erase(it_cookie++);
			url->clientmap->url.erase(it_url++);
			url->clientmap->ref.erase(it_ref++);
			url->clientmap->user_agent.erase(it_user_agent++);
			url->clientmap->host.erase(it_host++);
			url->clientmap->secusec.erase(it_secusec++);
			url->clientmap->sec.erase(it_sec++);
			url->clientmap->usec.erase(it_usec++);
			if(url->clientmap->timestamp_def.size() != 0){
				url->clientmap->timestamp_def.erase(it_timestamp_def++);
			}
			url->clientmap->title_flag.erase(it_title_flag++);
			url->clientmap->title.erase(it_title++);
			url->clientmap->content_type.erase(it_content_type++);
			url->clientmap->erase_flag.erase(it_erase_flag++);
			url->clientmap->heading_flag.erase(it_heading_flag++);
			url->clientmap->local_id.erase(it_local_id++);
			url->clientmap->debug.erase(it_debug++);
		}else{
			it_timestamp++;
			it_src_ip++;
			it_dst_ip++;
			it_src_port++;
			it_dst_port++;
			it_url++;
			it_ref++;
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
			it_local_id++;
			it_debug++;
		}
	}

	return 0;

}

int Filter::AloneFilter(){
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

	map<int, int> mapmap;

	while(it_local_id != url->clientmap->local_id.end()){
		mapmap[(*it_local_id).second] += 1;
		++it_local_id;
	}

	it_local_id = url->clientmap->local_id.begin();
	while(it_local_id != url->clientmap->local_id.end()){
		if(mapmap[(*it_local_id).second] == 1){
			(*it_erase_flag).second = 1;

		}
			it_timestamp++;
			it_src_ip++;
			it_dst_ip++;
			it_src_port++;
			it_dst_port++;
			it_url++;
			it_ref++;
			it_cookie++;
			it_user_agent++;
			it_host++;
			it_secusec++;
			it_sec++;
			it_usec++;
//			it_timestamp_def++;
			it_title_flag++;
			it_title++;
			it_content_type++;
			it_erase_flag++;
			it_heading_flag++;
			it_local_id++;
	}

	return 0;

}

int Filter::WhiteList(){
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
	multimap<string, string>::iterator it_debug = url->clientmap->debug.begin();

	vector<string> whitelist;
	vector<string>::iterator it;

	whitelist.push_back("www.youtube.com/watch?");
	whitelist.push_back("www.iogous.com");

	if(url->clientmap->timestamp.size() > 1){
		while(it_timestamp != url->clientmap->timestamp.end()){
			it = whitelist.begin();
			while(it != whitelist.end()){
				string::size_type index = (*it_url).second.find(*it);
				if(index != string::npos){
					(*it_erase_flag).second = 0;
					(*it_debug).second += "WHITE_LIST";
					break;
				}
				it++;
			}
			it_url++;
			it_timestamp++;
			it_erase_flag++;
			it_debug++;
		}
	}

	return 0;
}

int Filter::ExtensionFilter(){
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
	multimap<string, string>::iterator it_debug = url->clientmap->debug.begin();

	vector<string> extension;
	vector<string>::iterator it;

	extension.push_back(".jpg");
	extension.push_back(".png");
	extension.push_back(".ico");
	extension.push_back(".inc");
	extension.push_back(".gif");
	extension.push_back(".js");
	extension.push_back(".css");
	extension.push_back(".xml");
	extension.push_back(".aspx");
	extension.push_back(".xsl");
	extension.push_back(".shtml");

//	int flag;

	if(url->clientmap->timestamp.size() > 1){
		while(it_timestamp != url->clientmap->timestamp.end()){
//			flag = 0;
			it = extension.begin();
			while(it != extension.end()){
				string::size_type index = (*it_url).second.find(*it);
				if(index != string::npos){
					if((*it_url).second.substr(index) == *it){
						removed_url.push_back((*it_url).second);
						(*it_erase_flag).second = 1;
						(*it_debug).second += "EXTENSION";
						break;
					}
				}
				it++;
			}
//			if(flag != 1){
				it_timestamp++;
				it_src_ip++;
				it_dst_ip++;
				it_src_port++;
				it_dst_port++;
				it_url++;
				it_ref++;
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
				it_heading_flag++;
				it_erase_flag++;
				it_debug++;
//			}
		}
	}

	return 0;

}

int Filter::ResponseExistenceFilter(){
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
	multimap<string, string>::iterator it_debug = url->clientmap->debug.begin();

//	if(url->clientmap->timestamp.size() > 1){
		while(it_timestamp != url->clientmap->timestamp.end()){
//			cout << (*it_url).second << endl;
//			cout << (*it_erase_flag).second << endl;
//			cout << (*it_title_flag).second << endl;
			if((*it_title_flag).second != 1 && !url->CheckSE((*it_url).second, (*it_host).second)){
//				cout << (*it_url).second << "\t" << (*it_title_flag).second << "\t" << url->CheckSE((*it_url).second, (*it_host).second) << endl;
//				cout << "e" << endl;
				removed_url.push_back((*it_url).second);
				(*it_erase_flag).second = 1;
				(*it_debug).second += "RESPONSE_EXISTENCE";
//				url->clientmap->timestamp.erase(it_timestamp++);
//				url->clientmap->src_ip.erase(it_src_ip++);
//				url->clientmap->dst_ip.erase(it_dst_ip++);
//				url->clientmap->src_port.erase(it_src_port++);
//				url->clientmap->dst_port.erase(it_dst_port++);
//				url->clientmap->url.erase(it_url++);
//				url->clientmap->ref.erase(it_ref++);
//				url->clientmap->cookie.erase(it_cookie++);
//				url->clientmap->host.erase(it_host++);
//				url->clientmap->secusec.erase(it_secusec++);
//				url->clientmap->sec.erase(it_sec++);
//				url->clientmap->usec.erase(it_usec++);
//				url->clientmap->timestamp_def.erase(it_timestamp_def++);
//				url->clientmap->title_flag.erase(it_title_flag++);
//				url->clientmap->title.erase(it_title++);
//				url->clientmap->content_type.erase(it_content_type++);
			}
//			}else{
//				cout << (*it_url).second << "\t" << (*it_title_flag).second << "\t" << url->CheckSE((*it_url).second, (*it_host).second) << endl;
//				cout << "f" << endl;
				it_timestamp++;
				it_src_ip++;
				it_dst_ip++;
				it_src_port++;
				it_dst_port++;
				it_url++;
				it_ref++;
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
				it_debug++;
//			}
		}
//	}

	return 0;

}

int Filter::ContentTypeFilter(){
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
	multimap<string, string>::iterator it_title = url->clientmap->title.begin();
	multimap<string, int>::iterator it_title_flag = url->clientmap->title_flag.begin();
	multimap<string, string>::iterator it_content_type = url->clientmap->content_type.begin();
	multimap<string, int>::iterator it_erase_flag = url->clientmap->erase_flag.begin();
	multimap<string, int>::iterator it_heading_flag = url->clientmap->heading_flag.begin();
	multimap<string, string>::iterator it_debug = url->clientmap->debug.begin();

//	if(url->clientmap->timestamp.size() > 1){
		while(it_timestamp != url->clientmap->timestamp.end()){
//			cout << (*it_url).second << endl;
//			cout << (*it_content_type).second << endl;
			string::size_type index = (*it_content_type).second.find("text/html");
//			if((*it_content_type).second != "text/html"){
			if(index == string::npos){
				removed_url.push_back((*it_url).second);
				(*it_erase_flag).second = 1;
				(*it_debug).second += "CONTENT_TYPE";
			}else{
			}
			it_timestamp++;
			it_src_ip++;
			it_dst_ip++;
			it_src_port++;
			it_dst_port++;
			it_url++;
			it_ref++;
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
			it_debug++;
		}
//	}

	return 0;

}

int Filter::RefFilterAdv(){
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
	multimap<string, string>::iterator it_title = url->clientmap->title.begin();
	multimap<string, int>::iterator it_title_flag = url->clientmap->title_flag.begin();
	multimap<string, string>::iterator it_content_type = url->clientmap->content_type.begin();
	multimap<string, int>::iterator it_erase_flag = url->clientmap->erase_flag.begin();
	multimap<string, int>::iterator it_heading_flag = url->clientmap->heading_flag.begin();
	multimap<string, string>::iterator it_debug = url->clientmap->debug.begin();

	string url_key;

	map<string ,int> map_ref;
	map<string ,int>::iterator it_map_ref;

	while(it_ref != url->clientmap->ref.end()){
		if((*it_ref).second != ""){
//			cout << (*it_ref).second << endl;
			map_ref[(*it_ref).second] = 1;
		}
		++it_ref;
	}

//	it_ref = url->clientmap->ref.begin();
//	int flag = 0;

	while(it_timestamp != url->clientmap->timestamp.end()){
		if(map_ref[(*it_url).second] != 1){
			(*it_erase_flag).second = 1;
			(*it_debug).second += "REFADV";
//			string str = (*it_host).second;
//			str += "/";
//			it_map_ref = map_ref.begin();
//			while(it_map_ref != map_ref.end()){
//				if((*it_map_ref).first != str){
//					string::size_type index = ((*it_url).second).find((*it_map_ref).first);
//					if(index != string::npos){
//						cout << "hog" << endl;
//						cout << (*it_url).second << "\t" << (*it_map_ref).first << endl;
//						flag = 1;
//						break;
//					}
//				}
//				it_map_ref++;
//			}
//			if(flag == 0){
//				(*it_erase_flag).second = 1;
//				(*it_debug).second += "REFADV";
//			}else{
//				flag = 0;
//			}
		}
		it_timestamp++;
		it_src_ip++;
		it_dst_ip++;
		it_src_port++;
		it_dst_port++;
		it_url++;
		it_ref++;
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
		it_debug++;
	}


	return 0;

}

int Filter::RefFilter(){
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
	multimap<string, string>::iterator it_title = url->clientmap->title.begin();
	multimap<string, int>::iterator it_title_flag = url->clientmap->title_flag.begin();
	multimap<string, string>::iterator it_content_type = url->clientmap->content_type.begin();
	multimap<string, int>::iterator it_erase_flag = url->clientmap->erase_flag.begin();
	multimap<string, int>::iterator it_heading_flag = url->clientmap->heading_flag.begin();
	multimap<string, string>::iterator it_debug = url->clientmap->debug.begin();

	string url_key;

	while(it_timestamp != url->clientmap->timestamp.end()){
		if(it_timestamp == url->clientmap->timestamp.begin()){
			url_key = (*it_url).second;
		}else if(url_key == (*it_ref).second){
			it_ref++;
			if((*it_ref).second != (*it_url).second){
				(*it_erase_flag).second = 1;
				(*it_debug).second += "REF";
			}else{
				url_key = (*it_url).second;
			}
			it_ref--;
		}else{
			url_key = (*it_url).second;
		}
		it_timestamp++;
		it_src_ip++;
		it_dst_ip++;
		it_src_port++;
		it_dst_port++;
		it_url++;
		it_ref++;
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
		it_debug++;
	}


	return 0;

}

//int Filter::RefFilter(){
//	multimap<string, string>::iterator it_timestamp = url->clientmap->timestamp.begin();
//	multimap<string, string>::iterator it_src_ip = url->clientmap->src_ip.begin();
//	multimap<string, string>::iterator it_dst_ip = url->clientmap->dst_ip.begin();
//	multimap<string, string>::iterator it_src_port = url->clientmap->src_port.begin();
//	multimap<string, string>::iterator it_dst_port = url->clientmap->dst_port.begin();
//	multimap<string, string>::iterator it_url = url->clientmap->url.begin();
//	multimap<string, string>::iterator it_ref = url->clientmap->ref.begin();
//	multimap<string, string>::iterator it_cookie = url->clientmap->cookie.begin();
//	multimap<string, string>::iterator it_user_agent = url->clientmap->user_agent.begin();
//	multimap<string, string>::iterator it_host = url->clientmap->host.begin();
//	multimap<string, double>::iterator it_secusec = url->clientmap->secusec.begin();
//	multimap<string, long>::iterator it_sec = url->clientmap->sec.begin();
//	multimap<string, long>::iterator it_usec = url->clientmap->usec.begin();
//	multimap<string, double>::iterator it_timestamp_def = url->clientmap->timestamp_def.begin();
//	multimap<string, string>::iterator it_content_type = url->clientmap->content_type.begin();
//	multimap<string, int>::iterator it_erase_flag = url->clientmap->erase_flag.begin();
//	multimap<string, int>::iterator it_heading_flag = url->clientmap->heading_flag.begin();
//	multimap<string, int>::iterator it_title_flag = url->clientmap->title_flag.begin();
//	multimap<string, string>::iterator it_title = url->clientmap->title.begin();
//
//	vector<string>::iterator it;
//
//	it = removed_url.begin();
//	while(it != removed_url.end()){
////		cout << (*it) << endl;
//		it++;
//	}
//
////	while(it_ref != url->clientmap->ref.end()){
////		cout << (*it_url).second << "\t" << (*it_ref).second << endl;
////		it_ref++;
////		it_url++;
////	}
////	it_ref = url->clientmap->ref.begin();
////	it_url = url->clientmap->url.begin();
////	
////	cout << "hoge" << endl;
//
//	string ref_key = "";
//	string url_key = "";
//	string pre_ref = "";
//	string pre_url = "";
//	string pre_host = "";
//	
//	string pre_src_ip;
//
//	int erase_flag;
//
//	if(url->clientmap->timestamp.size() > 1){
//		while(it_timestamp != url->clientmap->timestamp.end()){
//			erase_flag = 0;
////			cout << "NOW::" << (*it_src_ip).second << "\t" << (*it_url).second << "\t" << (*it_ref).second << endl;
////			cout << "PRE::" << pre_src_ip << "\t" << pre_url << "\t" << pre_ref << "\t" << pre_host << endl;
//			if(it_timestamp == url->clientmap->timestamp.begin()){
//				ref_key = (*it_ref).second;
//				pre_ref = (*it_ref).second;
//				url_key = (*it_url).second;
//				pre_url = (*it_url).second;
//				pre_host = url->GetRefHost((*it_ref).second);
//				pre_src_ip = (*it_src_ip).second;
//				it_timestamp++;
//				it_src_ip++;
//				it_dst_ip++;
//				it_src_port++;
//				it_dst_port++;
//				it_url++;
//				it_ref++;
//				it_cookie++;
//				it_user_agent++;
//				it_host++;
//				it_secusec++;
//				it_sec++;
//				it_usec++;
//				it_timestamp_def++;
//				it_content_type++;
//				it_title++;
//				it_title_flag++;
//				it_erase_flag++;
//				it_heading_flag++;
//			}else{
//				string::size_type index = url_key.find((*it_ref).second);
////				cout << "URL::" << url_key << "\t" << "REF::" << (*it_ref).second << endl;
//				if(index == string::npos){
////					cout << "PREREF::" << pre_ref << "\t" << "NOWREF" << (*it_ref).second << endl;
//					if(pre_ref != (*it_ref).second){
//	//					pre_ref = (*it_ref).second;
//	//					pre_url = (*it_url).second;
//	//					pre_host = url->GetRefHost((*it_ref).second);
//					}else{
//	//					pre_ref = (*it_ref).second;
//	//					pre_url = (*it_url).second;
//	//					pre_host = url->GetRefHost((*it_ref).second);
////						cout << url->CheckSE(pre_ref, pre_host) << endl;
//						if(!url->CheckSE(pre_ref, pre_host) && erase_flag == 0){
////							cout << "a" << endl;
////							it_timestamp--;
////							it_src_ip--;
////							it_dst_ip--;
////							it_src_port--;
////							it_dst_port--;
////							it_url--;
////							it_ref--;
////							it_cookie--;
////							it_host--;
////							it_secusec--;
////							it_sec--;
////							it_usec--;
////							it_timestamp_def--;
////							it_content_type--;
//							it_erase_flag--;
//							removed_url.push_back((*it_url).second);
//							(*it_erase_flag).second = 1;
//							it_erase_flag++;
////							url->clientmap->timestamp.erase(it_timestamp++);
////							url->clientmap->src_ip.erase(it_src_ip++);
////							url->clientmap->dst_ip.erase(it_dst_ip++);
////							url->clientmap->src_port.erase(it_src_port++);
////							url->clientmap->dst_port.erase(it_dst_port++);
////							url->clientmap->url.erase(it_url++);
////							url->clientmap->ref.erase(it_ref++);
////							url->clientmap->cookie.erase(it_cookie++);
////							url->clientmap->host.erase(it_host++);
////							url->clientmap->secusec.erase(it_secusec++);
////							url->clientmap->sec.erase(it_sec++);
////							url->clientmap->usec.erase(it_usec++);
////							url->clientmap->timestamp_def.erase(it_timestamp_def++);
////							url->clientmap->content_type.erase(it_content_type++);
//							erase_flag = 1;
//						}
//					}
//				}else{
//	//				ref_key = (*it_ref).second;
//	//				ref_key = pre_ref;
//	//				pre_ref = (*it_ref).second;
//	//				url_key = (*it_url).second;
//	//				url_key = pre_url;
//	//				pre_url = (*it_url).second;
//	//				pre_host = url->GetRefHost((*it_ref).second);
//				}
//	
//				if(pre_src_ip != (*it_src_ip).second){
//					if(erase_flag == 0){
////							cout << "b" << endl;
////						it_timestamp--;
////						it_src_ip--;
////						it_dst_ip--;
////						it_src_port--;
////						it_dst_port--;
////						it_url--;
////						it_ref--;
////						it_cookie--;
////						it_host--;
////						it_secusec--;
////						it_sec--;
////						it_usec--;
////						it_timestamp_def--;
////						it_content_type--;
//						it_erase_flag--;
//						removed_url.push_back((*it_url).second);
//						(*it_erase_flag).second = 1;
//						it_erase_flag++;
////						url->clientmap->timestamp.erase(it_timestamp++);
////						url->clientmap->src_ip.erase(it_src_ip++);
////						url->clientmap->dst_ip.erase(it_dst_ip++);
////						url->clientmap->src_port.erase(it_src_port++);
////						url->clientmap->dst_port.erase(it_dst_port++);
////						url->clientmap->url.erase(it_url++);
////						url->clientmap->ref.erase(it_ref++);
////						url->clientmap->cookie.erase(it_cookie++);
////						url->clientmap->host.erase(it_host++);
////						url->clientmap->secusec.erase(it_secusec++);
////						url->clientmap->sec.erase(it_sec++);
////						url->clientmap->usec.erase(it_usec++);
////						url->clientmap->timestamp_def.erase(it_timestamp_def++);
////						url->clientmap->content_type.erase(it_content_type++);
//						erase_flag = 1;
//					}
//				}
//	
//				it = removed_url.begin();
//				while(it != removed_url.end()){
//					string tmp;
//					tmp = pre_ref[pre_ref.size() - 1];
//					string::size_type index = (*it).find(pre_ref);
//					if(index != string::npos && pre_ref != "" && tmp != "/"){
//	//				cout << (*it) << "\t" << pre_ref  << endl;
//						if(!url->CheckSE(pre_ref, pre_host) && !url->CheckGoogle(pre_ref, pre_host)){
//							if(erase_flag == 0){
////							cout << "c" << endl;
////								it_timestamp--;
////								it_src_ip--;
////								it_dst_ip--;
////								it_src_port--;
////								it_dst_port--;
////								it_url--;
////								it_ref--;
////								it_cookie--;
////								it_host--;
////								it_secusec--;
////								it_sec--;
////								it_usec--;
////								it_timestamp_def--;
////								it_content_type--;
//								it_erase_flag--;
//								removed_url.push_back((*it_url).second);
//								(*it_erase_flag).second = 1;
//								it_erase_flag++;
////								url->clientmap->timestamp.erase(it_timestamp++);
////								url->clientmap->src_ip.erase(it_src_ip++);
////								url->clientmap->dst_ip.erase(it_dst_ip++);
////								url->clientmap->src_port.erase(it_src_port++);
////								url->clientmap->dst_port.erase(it_dst_port++);
////								url->clientmap->url.erase(it_url++);
////								url->clientmap->ref.erase(it_ref++);
////								url->clientmap->cookie.erase(it_cookie++);
////								url->clientmap->host.erase(it_host++);
////								url->clientmap->secusec.erase(it_secusec++);
////								url->clientmap->sec.erase(it_sec++);
////								url->clientmap->usec.erase(it_usec++);
////								url->clientmap->content_type.erase(it_content_type++);
//								erase_flag = 1;
//							}
//						}
//					}
//					it++;
//				}
//	
//				pre_src_ip = (*it_src_ip).second;
//				pre_url = (*it_url).second;
//				pre_ref = (*it_ref).second;
//				pre_host = url->GetRefHost((*it_ref).second);
//				it_timestamp++;
//				it_src_ip++;
//				it_dst_ip++;
//				it_src_port++;
//				it_dst_port++;
//				it_url++;
//				it_ref++;
//				it_cookie++;
//				it_user_agent++;
//				it_host++;
//				it_secusec++;
//				it_sec++;
//				it_usec++;
//				it_timestamp_def++;
//				it_content_type++;
//				it_title++;
//				it_title_flag++;
//				it_erase_flag++;
//				it_heading_flag++;
//	
//				if(it_timestamp == url->clientmap->timestamp.end()){
////					cout << "d" << endl;
////					it_timestamp--;
////					it_src_ip--;
////					it_dst_ip--;
////					it_src_port--;
////					it_dst_port--;
////					it_url--;
////					it_ref--;
////					it_cookie--;
////					it_host--;
////					it_secusec--;
////					it_sec--;
////					it_usec--;
////					it_timestamp_def--;
////					it_content_type--;
//					it_erase_flag--;
//					removed_url.push_back((*it_url).second);
//					(*it_erase_flag).second = 1;
//					it_erase_flag++;
////					url->clientmap->timestamp.erase(it_timestamp++);
////					url->clientmap->src_ip.erase(it_src_ip++);
////					url->clientmap->dst_ip.erase(it_dst_ip++);
////					url->clientmap->src_port.erase(it_src_port++);
////					url->clientmap->dst_port.erase(it_dst_port++);
////					url->clientmap->url.erase(it_url++);
////					url->clientmap->ref.erase(it_ref++);
////					url->clientmap->cookie.erase(it_cookie++);
////					url->clientmap->host.erase(it_host++);
////					url->clientmap->secusec.erase(it_secusec++);
////					url->clientmap->sec.erase(it_sec++);
////					url->clientmap->usec.erase(it_usec++);
////					url->clientmap->timestamp_def.erase(it_timestamp_def++);
////					url->clientmap->content_type.erase(it_content_type++);
//				}
//	
//				if(erase_flag == 0){
//					url_key = pre_url;
//					ref_key = pre_ref;
////					cout << "KEY UPDATE" << endl;
////					cout << "KEY IS " << url_key << endl;
//				}
//			}
//		}
//	}
//
//	return 0;
//
//}
//
//int Filter::CalTimeDef(){
//	long sec, usec;
//	double secusec;
//	stringstream ss;
//
//	multimap<string, string>::iterator it_timestamp = url->clientmap->timestamp.begin();
//	multimap<string, string>::iterator it_src_ip = url->clientmap->src_ip.begin();
//	multimap<string, string>::iterator it_dst_ip = url->clientmap->dst_ip.begin();
//	multimap<string, string>::iterator it_src_port = url->clientmap->src_port.begin();
//	multimap<string, string>::iterator it_dst_port = url->clientmap->dst_port.begin();
//	multimap<string, string>::iterator it_url = url->clientmap->url.begin();
//	multimap<string, string>::iterator it_ref = url->clientmap->ref.begin();
//	multimap<string, string>::iterator it_cookie = url->clientmap->cookie.begin();
//	multimap<string, string>::iterator it_user_agent = url->clientmap->user_agent.begin();
//	multimap<string, string>::iterator it_host = url->clientmap->host.begin();
//	multimap<string, double>::iterator it_secusec = url->clientmap->secusec.begin();
//	multimap<string, long>::iterator it_sec = url->clientmap->sec.begin();
//	multimap<string, long>::iterator it_usec = url->clientmap->usec.begin();
//	multimap<string, string>::iterator it_content_type = url->clientmap->content_type.begin();
//	multimap<string, int>::iterator it_erase_flag = url->clientmap->erase_flag.begin();
//	multimap<string, int>::iterator it_heading_flag = url->clientmap->heading_flag.begin();
//
//	vector<long> vector_sec;
//	vector<long> vector_usec;
//	vector<long>::iterator it_vector_sec;
//	vector<long>::iterator it_vector_usec;
//
//	string src_ip;
//
//	it_sec = url->clientmap->sec.begin();
//	while(it_sec != url->clientmap->sec.end()){
//		if(it_sec == url->clientmap->sec.begin()){
//			src_ip = (*it_sec).first;
//			++it_sec;
//			++it_usec;
//		}else{
//			if(src_ip != (*it_sec).first){
//				vector_sec.push_back(2147483647);
//				vector_usec.push_back(0);
//			}else{
//				vector_sec.push_back((*it_sec).second);
//				vector_usec.push_back((*it_usec).second);
//			}
//			src_ip = (*it_sec).first;
//			++it_sec;
//			++it_usec;
//		}
//	}
//
//	it_timestamp = url->clientmap->timestamp.begin();
//	it_src_ip = url->clientmap->src_ip.begin();
//	it_dst_ip = url->clientmap->dst_ip.begin();
//	it_src_port = url->clientmap->src_port.begin();
//	it_dst_port = url->clientmap->dst_port.begin();
//	it_url = url->clientmap->url.begin();
//	it_ref = url->clientmap->ref.begin();
//	it_cookie = url->clientmap->cookie.begin();
//	it_user_agent = url->clientmap->user_agent.begin();
//	it_host = url->clientmap->host.begin();
//	it_secusec = url->clientmap->secusec.begin();
//	it_sec = url->clientmap->sec.begin();
//	it_usec = url->clientmap->usec.begin();
//	it_content_type = url->clientmap->content_type.begin();
//
//	it_vector_sec = vector_sec.begin();
//	it_vector_usec = vector_usec.begin();
//
//	cout << vector_sec.size() << endl;
//	cout << vector_usec.size() << endl;
//	cout << url->clientmap->timestamp.size() << endl;
//
//	if(url->clientmap->timestamp.size() > 1){
//		while(it_timestamp != url->clientmap->timestamp.end()){
//				if(((*it_vector_usec) - (*it_usec).second) >= 0){
//					usec = (*it_vector_usec) - (*it_usec).second;
//					if(((*it_vector_sec) - (*it_sec).second) >= 0){
//						sec = (*it_vector_sec) - (*it_sec).second;
//						ss.str("");
//						ss.clear(stringstream::goodbit);
//						ss << sec << "." << usec;
//						ss >> secusec;
//						url->clientmap->timestamp_def.insert(pair<string, double>((*it_src_ip).second, secusec));
//					}else{
//						secusec = -1;
//						url->clientmap->timestamp_def.insert(pair<string, double>((*it_src_ip).second, secusec));
//					}
//				}else{
//					usec = ((*it_vector_usec) - (*it_usec).second) * (-1);
//					if(((*it_vector_sec) - 1 - (*it_sec).second) >= 0){
//						sec = (*it_vector_sec) - 1 - (*it_sec).second;
//						ss.str("");
//						ss.clear(stringstream::goodbit);
//						ss << sec << "." << usec;
//						ss >> secusec;
//						url->clientmap->timestamp_def.insert(pair<string, double>((*it_src_ip).second, secusec));
//					}else{
//						secusec = -1;
//						url->clientmap->timestamp_def.insert(pair<string, double>((*it_src_ip).second, secusec));
//					}
//				}
//	
//			secusec = 0;
//			it_timestamp++;
//			it_src_ip++;
//			it_dst_ip++;
//			it_src_port++;
//			it_dst_port++;
//			it_url++;
//			it_ref++;
//			it_cookie++;
//			it_user_agent++;
//			it_host++;
//			it_secusec++;
//			it_sec++;
//			it_usec++;
//	
//			it_vector_sec++;
//			it_vector_usec++;
//		}
//	}else{
//		url->clientmap->timestamp_def.insert(pair<string, double>((*it_src_ip).second, 0));
//	}
//
//	cout << "hoge" << endl;
//
//	return 0;
//}

int Filter::TimeDiffFilter(){
	double threshold = 0.8;

	long sec, usec, n_sec, n_usec;
	double def;

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
	multimap<string, string>::iterator it_content_type = url->clientmap->content_type.begin();
	multimap<string, int>::iterator it_erase_flag = url->clientmap->erase_flag.begin();
	multimap<string, int>::iterator it_heading_flag = url->clientmap->heading_flag.begin();
	multimap<string, int>::iterator it_title_flag = url->clientmap->title_flag.begin();
	multimap<string, string>::iterator it_title = url->clientmap->title.begin();
	multimap<string, string>::iterator it_debug = url->clientmap->debug.begin();

	while(it_timestamp != url->clientmap->timestamp.end()){
		++it_timestamp;
		if(it_timestamp == url->clientmap->timestamp.end()){
			break;
		}
		--it_timestamp;

		++it_sec;
		++it_usec;
		n_sec = (*it_sec).second;
		n_usec = (*it_usec).second;
		--it_sec;
		--it_usec;
		sec = (*it_sec).second;
		usec = (*it_usec).second;
		stringstream ss;
		ss.str("");
		ss.clear(stringstream::goodbit);

		if(n_usec - usec < 0){
			ss << n_sec - sec - 1 << "." << 1000000 + (n_usec - usec);
//			ss << n_sec - sec - 1 << "." << (-1) * (n_usec - usec);
		}else{
			ss << n_sec - sec << "." << n_usec - usec;
		}
		ss >> def;
//		cout << (*it_url).second << endl;
//		cout << (*it_timestamp).second << "\t" << (*it_sec).second << "\t" << (*it_usec).second << endl;
//		cout << def << endl;
		if(def >= threshold){
		}else{
			it_erase_flag++;
			it_debug++;
			(*it_erase_flag).second = 1;
			(*it_debug).second += "TIMEDIFF";
			it_erase_flag--;
			it_debug--;
		}
		it_timestamp++;
		it_src_ip++;
		it_dst_ip++;
		it_src_port++;
		it_dst_port++;
		it_url++;
		it_ref++;
		it_cookie++;
		it_user_agent++;
		it_host++;
		it_secusec++;
		it_sec++;
		it_usec++;
//		it_timestamp_def++;
		it_content_type++;
		it_title++;
		it_title_flag++;
		it_erase_flag++;
		it_heading_flag++;
		it_debug++;
	}

	return 0;
}

int Filter::ErrorFilter(){//satoshi_added
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
	multimap<string, string>::iterator it_content_type = url->clientmap->content_type.begin();
	multimap<string, int>::iterator it_erase_flag = url->clientmap->erase_flag.begin();
	multimap<string, int>::iterator it_heading_flag = url->clientmap->heading_flag.begin();
	multimap<string, int>::iterator it_title_flag = url->clientmap->title_flag.begin();
	multimap<string, string>::iterator it_title = url->clientmap->title.begin();
	multimap<string, string>::iterator it_debug = url->clientmap->debug.begin();

	long sectmp=0, usectmp=0;
	while(it_timestamp != url->clientmap->timestamp.end()){
		if((*it_sec).second <= sectmp){
			if((*it_usec).second <= usectmp){
				(*it_erase_flag).second = 1;
				(*it_debug).second += "ERROR_JUNBAN";
			}
		}
		sectmp = (*it_sec).second;
		usectmp = (*it_usec).second;

		it_timestamp++;
		it_src_ip++;
		it_dst_ip++;
		it_src_port++;
		it_dst_port++;
		it_url++;
		it_ref++;
		it_cookie++;
		it_user_agent++;
		it_host++;
		it_secusec++;
		it_sec++;
		it_usec++;
		if(url->clientmap->timestamp_def.size() != 0){
			it_timestamp_def++;
		}
		it_content_type++;
		it_title++;
		it_title_flag++;
		it_erase_flag++;
		it_heading_flag++;
		it_debug++;
	}

	return 0;
}

int Filter::TitleExitFilter(){//satoshi_added
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
	multimap<string, string>::iterator it_content_type = url->clientmap->content_type.begin();
	multimap<string, int>::iterator it_erase_flag = url->clientmap->erase_flag.begin();
	multimap<string, int>::iterator it_heading_flag = url->clientmap->heading_flag.begin();
	multimap<string, int>::iterator it_title_flag = url->clientmap->title_flag.begin();
	multimap<string, string>::iterator it_title = url->clientmap->title.begin();
	multimap<string, string>::iterator it_debug = url->clientmap->debug.begin();

	while(it_timestamp != url->clientmap->timestamp.end()){
		if((*it_title).second == "" || (*it_title).second == " " || (*it_title).second == "　" || (*it_title).second == "\t"){
			(*it_erase_flag).second = 1;
			(*it_debug).second += "TITLE_EXIT";
		}
		it_timestamp++;
		it_src_ip++;
		it_dst_ip++;
		it_src_port++;
		it_dst_port++;
		it_url++;
		it_ref++;
		it_cookie++;
		it_user_agent++;
		it_host++;
		it_secusec++;
		it_sec++;
		it_usec++;
		if(url->clientmap->timestamp_def.size() != 0){
			it_timestamp_def++;
		}
		it_content_type++;
		it_title++;
		it_title_flag++;
		it_erase_flag++;
		it_heading_flag++;
		it_debug++;
	}

	return 0;
}


int Filter::TitleFilter(){
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
	multimap<string, string>::iterator it_content_type = url->clientmap->content_type.begin();
	multimap<string, int>::iterator it_erase_flag = url->clientmap->erase_flag.begin();
	multimap<string, int>::iterator it_heading_flag = url->clientmap->heading_flag.begin();
	multimap<string, int>::iterator it_title_flag = url->clientmap->title_flag.begin();
	multimap<string, string>::iterator it_title = url->clientmap->title.begin();
	multimap<string, string>::iterator it_debug = url->clientmap->debug.begin();

	vector<string> blacklist;
	vector<string>::iterator it_blacklist;

	blacklist.push_back("{");
	blacklist.push_back("Advertisement");
	blacklist.push_back("Error");
	blacklist.push_back("Not Found");
	blacklist.push_back("Redirecting");
	blacklist.push_back("uid");
//	blacklist.push_back("Moved");

	while(it_timestamp != url->clientmap->timestamp.end()){
		it_blacklist = blacklist.begin();
		while(it_blacklist != blacklist.end()){
			string::size_type index = ((*it_title).second).find(*it_blacklist);
			if(index != string::npos){
				(*it_erase_flag).second = 1;
				(*it_debug).second += "TITLE";
				break;
			}else{
				it_blacklist++;
			}
		}
		it_timestamp++;
		it_src_ip++;
		it_dst_ip++;
		it_src_port++;
		it_dst_port++;
		it_url++;
		it_ref++;
		it_cookie++;
		it_user_agent++;
		it_host++;
		it_secusec++;
		it_sec++;
		it_usec++;
		if(url->clientmap->timestamp_def.size() != 0){
			it_timestamp_def++;
		}
		it_content_type++;
		it_title++;
		it_title_flag++;
		it_erase_flag++;
		it_heading_flag++;
		it_debug++;
	}

	return 0;
}

int Filter::URLFilter(){
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
	multimap<string, string>::iterator it_content_type = url->clientmap->content_type.begin();
	multimap<string, int>::iterator it_erase_flag = url->clientmap->erase_flag.begin();
	multimap<string, int>::iterator it_heading_flag = url->clientmap->heading_flag.begin();
	multimap<string, int>::iterator it_title_flag = url->clientmap->title_flag.begin();
	multimap<string, string>::iterator it_title = url->clientmap->title.begin();
	multimap<string, string>::iterator it_debug = url->clientmap->debug.begin();

	vector<string> blacklist;
	vector<string>::iterator it_blacklist;

	blacklist.push_back("/ad/");
	blacklist.push_back("/adarea/");
	blacklist.push_back("/adi/");
	blacklist.push_back("/advanced/");
	blacklist.push_back("/advertising");
	blacklist.push_back("/analytics/");
	blacklist.push_back("/api/");
	blacklist.push_back(".aspx?");
	blacklist.push_back("/cache/");
	blacklist.push_back("/common/");
	blacklist.push_back("/complete/");
	blacklist.push_back("/css/");
//	blacklist.push_back("/docs/");
	blacklist.push_back("/dummy");
	blacklist.push_back("/error/");
	blacklist.push_back("/f/");
	blacklist.push_back("/flash/");
	blacklist.push_back("/html.ng/");
	blacklist.push_back("/iframe/");
	blacklist.push_back("/img/");
	blacklist.push_back("/item/");
	blacklist.push_back("/i1/");
	blacklist.push_back("/none");
	blacklist.push_back("/not_exist");
	blacklist.push_back("/notfound");
	blacklist.push_back("/optiframe");
	blacklist.push_back("/photo");
	blacklist.push_back("/plugins/");
	blacklist.push_back("/rank/");
	blacklist.push_back("/reload.");
	blacklist.push_back(".rss?");
	blacklist.push_back("/schedule/");
	blacklist.push_back("/serve/");
	blacklist.push_back("/sidebar/");
	blacklist.push_back("/sso/");
	blacklist.push_back("/static/");
	blacklist.push_back("/thumb/");
	blacklist.push_back("/uw/");
	blacklist.push_back("/widget/");
	blacklist.push_back("/widgets/");
	blacklist.push_back("/w/1.0/");
	blacklist.push_back("/-/");
	blacklist.push_back("/404.");

	blacklist.push_back("youtube.com/embed/");
	blacklist.push_back("ustream.tv/embed/");

	while(it_timestamp != url->clientmap->timestamp.end()){
		it_blacklist = blacklist.begin();
		while(it_blacklist != blacklist.end()){
			string::size_type index = ((*it_url).second).find(*it_blacklist);
			if(index != string::npos){
				(*it_erase_flag).second = 1;
				(*it_debug).second += "URL";
				break;
			}else{
				it_blacklist++;
			}
		}
		it_timestamp++;
		it_src_ip++;
		it_dst_ip++;
		it_src_port++;
		it_dst_port++;
		it_url++;
		it_ref++;
		it_cookie++;
		it_user_agent++;
		it_host++;
		it_secusec++;
		it_sec++;
		it_usec++;
		if(url->clientmap->timestamp_def.size() != 0){
			it_timestamp_def++;
		}
		it_content_type++;
		it_title++;
		it_title_flag++;
		it_erase_flag++;
		it_heading_flag++;
		it_debug++;
	}

	blacklist.clear();
	blacklist.push_back("api.");
	blacklist.push_back("ad.");
	blacklist.push_back("ads.");
	blacklist.push_back("advertising.");
	blacklist.push_back("bwp.cnet.com");
	blacklist.push_back("doubleclick");
	blacklist.push_back("err.");
	blacklist.push_back("iogous");
	blacklist.push_back("static.");
	blacklist.push_back("platform.");
	blacklist.push_back("plugins.");
	blacklist.push_back("share.");
	blacklist.push_back("toolbarqueries.");

	blacklist.push_back("west.sd.keio.ac.jp");
	blacklist.push_back("openinter.net");

	it_timestamp = url->clientmap->timestamp.begin();
	it_src_ip = url->clientmap->src_ip.begin();
	it_dst_ip = url->clientmap->dst_ip.begin();
	it_src_port = url->clientmap->src_port.begin();
	it_dst_port = url->clientmap->dst_port.begin();
	it_url = url->clientmap->url.begin();
	it_ref = url->clientmap->ref.begin();
	it_cookie = url->clientmap->cookie.begin();
	it_user_agent = url->clientmap->user_agent.begin();
	it_host = url->clientmap->host.begin();
	it_secusec = url->clientmap->secusec.begin();
	it_sec = url->clientmap->sec.begin();
	it_usec = url->clientmap->usec.begin();
	it_timestamp_def = url->clientmap->timestamp_def.begin();
	it_content_type = url->clientmap->content_type.begin();
	it_erase_flag = url->clientmap->erase_flag.begin();
	it_heading_flag = url->clientmap->heading_flag.begin();
	it_title_flag = url->clientmap->title_flag.begin();
	it_title = url->clientmap->title.begin();
	it_debug = url->clientmap->debug.begin();

	while(it_timestamp != url->clientmap->timestamp.end()){
		it_blacklist = blacklist.begin();
		while(it_blacklist != blacklist.end()){
			string::size_type index = ((*it_host).second).find(*it_blacklist);
			if(index != string::npos){
				(*it_erase_flag).second = 1;
				(*it_debug).second += "URL";
				break;
			}else{
				it_blacklist++;
			}
		}
		it_timestamp++;
		it_src_ip++;
		it_dst_ip++;
		it_src_port++;
		it_dst_port++;
		it_url++;
		it_ref++;
		it_cookie++;
		it_user_agent++;
		it_host++;
		it_secusec++;
		it_sec++;
		it_usec++;
		if(url->clientmap->timestamp_def.size() != 0){
			it_timestamp_def++;
		}
		it_content_type++;
		it_title++;
		it_title_flag++;
		it_erase_flag++;
		it_heading_flag++;
		it_debug++;
	}

	return 0;
}

int Filter::HTTPStatusFilter(){
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
	multimap<string, string>::iterator it_content_type = url->clientmap->content_type.begin();
	multimap<string, int>::iterator it_erase_flag = url->clientmap->erase_flag.begin();
	multimap<string, int>::iterator it_heading_flag = url->clientmap->heading_flag.begin();
	multimap<string, int>::iterator it_title_flag = url->clientmap->title_flag.begin();
	multimap<string, string>::iterator it_title = url->clientmap->title.begin();
	multimap<string, string>::iterator it_debug = url->clientmap->debug.begin();

	vector<string> status;
	vector<string>::iterator it_status;

	status.push_back("302 Found");
	status.push_back("302 Moved");
	status.push_back("403 Forbidden");
	status.push_back("404 Not Found");
	status.push_back("301 Moved Permanently");
	status.push_back("Moved Temporarily");
//	status.push_back("Moved");
//	status.push_back("Object moved");

	while(it_timestamp != url->clientmap->timestamp.end()){
		it_status = status.begin();
		while(it_status != status.end()){
			string::size_type index = ((*it_title).second).find(*it_status);
			if(index != string::npos){
				(*it_erase_flag).second = 1;
				(*it_debug).second += "HTTPStatus";
				break;
	//			url->clientmap->timestamp.erase(it_timestamp++);
	//			url->clientmap->src_ip.erase(it_src_ip++);
	//			url->clientmap->dst_ip.erase(it_dst_ip++);
	//			url->clientmap->src_port.erase(it_src_port++);
	//			url->clientmap->dst_port.erase(it_dst_port++);
	//			url->clientmap->url.erase(it_url++);
	//			url->clientmap->ref.erase(it_ref++);
	//			url->clientmap->cookie.erase(it_cookie++);
	//			url->clientmap->host.erase(it_host++);
	//			url->clientmap->secusec.erase(it_secusec++);
	//			url->clientmap->sec.erase(it_sec++);
	//			url->clientmap->usec.erase(it_usec++);
	//			url->clientmap->timestamp_def.erase(it_timestamp_def++);
	//			url->clientmap->content_type.erase(it_content_type++);
			}else{
				it_status++;
			}
		}
		it_timestamp++;
		it_src_ip++;
		it_dst_ip++;
		it_src_port++;
		it_dst_port++;
		it_url++;
		it_ref++;
		it_cookie++;
		it_user_agent++;
		it_host++;
		it_secusec++;
		it_sec++;
		it_usec++;
		if(url->clientmap->timestamp_def.size() != 0){
			it_timestamp_def++;
		}
		it_content_type++;
		it_title++;
		it_title_flag++;
		it_erase_flag++;
		it_heading_flag++;
		it_debug++;
	}

	return 0;
}


int Filter::GoogleRedirectFilter(){
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
	multimap<string, int>::iterator it_erase_flag = url->clientmap->erase_flag.begin();
	multimap<string, int>::iterator it_heading_flag = url->clientmap->heading_flag.begin();

	while(it_timestamp != url->clientmap->timestamp.end()){
		if(url->CheckGoogle((*it_url).second, (*it_host).second)){
//			cout << ExtractURLForGoogle((*it_url).second) << endl;
			url->ExtractURLForGoogle((*it_url).second);
		}
		it_timestamp++;
		it_src_ip++;
		it_dst_ip++;
		it_src_port++;
		it_dst_port++;
		it_url++;
		it_ref++;
		it_cookie++;
		it_user_agent++;
		it_host++;
		it_secusec++;
		it_sec++;
		it_usec++;
		it_timestamp_def++;
	}

	return 0;
}

vector<string> Filter::LoadFocusHost(){
	vector<string> host;
	host.push_back("yahoo.co.jp");
//	host.push_back("jp.msn.com");
	host.push_back("bing.com");
	host.push_back("msn.com");
	host.push_back("google.co.jp");
	host.push_back("google.com");
	host.push_back("twitter.com");
	host.push_back("facebook.com");

	return host;
}

vector<string> Filter::GetCookieVariety(string cookie){
	vector<string>::iterator it;
	vector<string> vec;

	string str = cookie;
	string buf = "";
	string tmp = "";
	string tmp2 = "";
	for(unsigned int i = 0; i < str.size(); i++){
		tmp = str[i];
		if(tmp == "="){
			if(buf != ""){
				vec.push_back(buf+"=");
				buf = "";
			}
//			i++;
		}else{
			if(tmp == " " || tmp == "@"){
				if(tmp == "@"){
					tmp2 = str[i+1];
					if(tmp2 == "%"){
						buf = "";
						i++;
					}
				}else{
					buf = "";
				}
			}else{
				buf += tmp;
			}
		}
	}
//	if(buf != ""){
//		vec.push_back(buf+"=");
//	}

//	it = vec.begin();
//	while(it != vec.end()){
//		cout << (*it) << endl;
//		it++;
//	}

	return vec;
}

map<string, string> Filter::GetCookieVarietyValue(string cookie){
	map<string, string>::iterator it;
	map<string, string> map1;


	string str = cookie;
	string buf = "";
	string tmp = "";
	string tmp2 = "";
	string key = "";
	string value = "";
	int flag = 0;
	for(unsigned int i = 0; i < str.size(); i++){
		tmp = str[i];
		if(tmp == "=" && flag == 0){
			flag = 1;
			if(buf != ""){
//				vec.push_back(buf+"=");
				key = buf;
				buf = "";
			}
//			i++;
		}else{
			if(tmp == " " || tmp == "@"){
				if(tmp == "@"){
					tmp2 = str[i+1];
					if(tmp2 == "%"){
						if(key != "" && value != ""){
							map1[key] = value;
							flag = 0;
							key = "";
							value = "";
						}
						i++;
					}
				}else{
					if(key != "" && value != ""){
						map1[key] = value;
						flag = 0;
						key = "";
						value = "";
					}
				}
			}else if(flag == 0){
				buf += tmp;
			}else{
				value += tmp;
			}
		}
	}

	if(key != "" && value != ""){
		map1[key] = value;
		flag = 0;
		key = "";
		value = "";
	}


//	it = map1.begin();
//	while(it != map1.end()){
//		cout << (*it).first << "\t" << (*it).second << endl;
//		it++;
//	}


	return map1;
}
