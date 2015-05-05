#pragma once
#include "Include.H"
#include "Global.H"

class Url{
	private:
//		string GetGET(string get_str);
//		string GetHost(string host_str);
//		string GetRef(string ref_str);
//		string GetRefHost(string ref_str);
//		string GetURL();
//		string GetTitle(string str);
//		string GetContentType(string str);
//		string GetURLQuery(string str);
//		string GetRefQuery(string str);
//		int CheckSE(string url, string host);
//		int CheckGoogle(string url, string host);
//		string ExtractURLForGoogle(string str);
		int CheckBL(string src_mac_addr);
		string AvoidGoogle(string src_mac_addr);
		long GetSec(string unix_time);
		long GetUSec(string unix_time);
//		long double GetSecUSec(string unix_time);
		double GetSecUSec(string unix_time);
		void ClearGET();
		void ClearHost();
		void ClearRef();
		void ClearTitle();
		void ClearCookie();
		void ClearUserAgent();
		void ClearVector();
		void ClearIdMap();
		void ClearTimestampMap();
		void ClearClientMap();
		void ClearContentType();
		int MatchNumberInStream(vector<string>::iterator it);
		int wait_num;

//		string CalBrowsingTime(string prev_time, string time);

//		int CalTimeDef();
//		int TimeDefFilter();
//		int RefFilter();
//		int GoogleRedirectFilter();
//		int ResponseExistenceFilter();
//		int ExtensionFilter();
//		int ContentTypeFilter();
		int UrlShow();
		int UrlInsert(string prepretimestamp);

//		vector<string> removed_url;
		string tmptimestamp;
		void SetTmpTimestamp(string timestamp);
		int exit_new_history;

	public:
		Url();
		int Reconstruct(const string sql);
		int Identify();
		int GetHistory(string prepretimestamp);

		string CalBrowsingTime(long sec, long usec, long next_sec, long next_usec);

		string GetGET(string get_str);
		string GetHost(string host_str);
		string GetRef(string ref_str);
		string GetRefHost(string ref_str);
		string GetURL();
		string GetTitle(string str);
		string GetContentType(string str);
		string GetURLQuery(string str);
		string GetRefQuery(string str);
		string GetCookie(string str);
		string GetUserAgent(string str);

		int CheckSE(string url, string host);
		int CheckGoogle(string url, string host);
		string ExtractURLForGoogle(string str);

		string get_str;
		string host_str;
		string ref_str;
		string cookie_str;
		string user_agent_str;
		string title_str;
		string content_type_str;

		vector<string>::iterator it_stream_id;
		vector<string>::iterator it_result_id;
		vector<string>::iterator it_timestamp;
		vector<string>::iterator it_src_ip;
		vector<string>::iterator it_dst_ip;
		vector<string>::iterator it_src_port;
		vector<string>::iterator it_dst_port;
		vector<string>::iterator it_src_mac_addr;
		vector<string>::iterator it_dst_mac_addr;
		vector<string>::iterator it_pattern;
		vector<string>::iterator it_result;
		vector<string>::iterator it_prefilter_log;
		vector<string>::iterator it_unix_time;

		vector<string> stream_id;
		vector<string> result_id;
		vector<string> timestamp;
		vector<string> src_ip;
		vector<string> dst_ip;
		vector<string> src_port;
		vector<string> dst_port;
		vector<string> src_mac_addr;
		vector<string> dst_mac_addr;
		vector<string> pattern;
		vector<string> result_string;
		vector<string> prefilter_log;
		vector<string> unix_time;

		vector<string> query;

		map<string, string> google_redirect;

		class TimestampMap{
			public:
				map<string, string> result_id;
				map<string, string> timestamp;
				map<string, string> src_ip;
				map<string, string> dst_ip;
				map<string, string> src_port;
				map<string, string> dst_port;
				map<string, string> src_mac_addr;
				map<string, string> dst_mac_addr;
				map<string, string> url;
				map<string, string> title;
				map<string, string> ref;
				map<string, string> cookie;
				map<string, string> user_agent;
				map<string, string> host;
				map<string, double> secusec;
//				map<string, long double> secusec;
				map<string, long> sec;
				map<string, long> usec;
				map<string, string> unique_id;
				map<string, int> title_flag;
				map<string, int> heading_flag;
				map<string, string> content_type;
		}*timestampmap;

//		class IdMap{
//			public:
//				map<int, string> result_id;
//				map<int, string> timestamp;
//				map<int, string> src_ip;
//				map<int, string> dst_ip;
//				map<int, string> src_port;
//				map<int, string> dst_port;
//				map<int, string> src_mac_addr;
//				map<int, string> dst_mac_addr;
//				map<int, string> url;
//				map<int, string> title;
//				map<int, string> ref;
//				map<int, string> cookie;
//				map<int, string> host;
//				map<int, double> secusec;
////				map<int, long double> secusec;
//				map<int, long> sec;
//				map<int, long> usec;
//				map<int, string> unique_id;
//				map<int, int> title_flag;
//				map<int, int> heading_flag;
//				map<int, string> content_type;
//		}*idmap;

		class ClientMap{
			public:
				multimap<string, string> timestamp;
				multimap<string, string> src_ip;
				multimap<string, string> dst_ip;
				multimap<string, string> src_port;
				multimap<string, string> dst_port;
				multimap<string, string> src_mac_addr;
				multimap<string, string> url;
				multimap<string, string> ref;
				multimap<string, string> title;
				multimap<string, string> cookie;
				multimap<string, string> user_agent;
				multimap<string, string> host;
				multimap<string, double> secusec;
//				multimap<string, long double> secusec;
				multimap<string, long> sec;
				multimap<string, long> usec;
				multimap<string, double> timestamp_def;
				multimap<string, int> title_flag;
				multimap<string, string> content_type;
				multimap<string, int> erase_flag;
				multimap<string, int> heading_flag;

				multimap<string, int> local_id;
				multimap<string, string> debug;

				multimap<string, string> browsing_time;

		}*clientmap;

		class ForAllMap{
			public:
				map<string, string> timestamp;
				map<string, string> src_ip;
				map<string, string> dst_ip;
				map<string, string> src_port;
				map<string, string> dst_port;
				map<string, string> src_mac_addr;
				map<string, string> url;
				map<string, string> ref;
				map<string, string> title;
				map<string, string> cookie;
				map<string, string> user_agent;
				map<string, string> host;
				map<string, double> secusec;
//				map<string, long double> secusec;
				map<string, long> sec;
				map<string, long> usec;
				map<string, double> timestamp_def;
				map<string, int> title_flag;
				map<string, string> content_type;
				map<string, int> erase_flag;
				map<string, int> heading_flag;

				map<string, int> local_id;
//				map<string, string> local_id;
				map<string, string> debug;

				map<string, string> browsing_time;
		}*forallmap;


		map<string, string> url_title;

		string GetTmpTimestamp(){return tmptimestamp;}
		int GetExitNewHistory(){return exit_new_history;}
};

