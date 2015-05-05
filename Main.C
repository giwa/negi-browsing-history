/*
 * ** Copyright (C) 2012 Shinichi Ishida, All Rights Reserved.
 * **
 * ** Please see the LICENSE file distributed with this source
 * ** code archive for information covering the modification and
 * ** redistribution of this file and binaries built from it.
 * */

/*
 *$Id: srim.C,v 5.27 2012-08-22 08:05:53 sin Exp $
 */
#include "Main.H"
#include "PacketCapture.H"
#include "PacketFileReader.H"
#include "Test.H"
#include "TestRule.H"
#include "Observer.H"
#include "SSS.H"

#include <functional>
#include <utility>



int main(int argc, char *argv[]){
//	signal(SIGINT, signal_handler);
//
//Initialize!!

	//time_t start = time(NULL);
	struct timeval t0;
	struct timeval t1;
	gettimeofday(&t0, NULL);


if(argc != 2){
	cerr << "Usage: " << argv[0] << " config_file" << endl;
	return 1;
}

	//Read arguments
 	string config_file = argv[1];   

	//Create instances
	config = new Config;
	config->init(config_file);

	master = new Master;
	rule_pool = new RulePool;
	stream_rebuild = new StreamRebuild;
	ip_filter = new IpFilter;
	http_decoder = new HttpDecoder;
//	match_pre_filter = new MatchPreFilter;
	extractor = new Extractor;
	stream_pool = new StreamPool;
	tcp_conn_pool = new TcpConnPool;
	packet_clean = new PacketClean;
	observer = new Observer;
	gzip = new Gzip;

#ifdef FILEWRITE_MODE
	file_writer = new FileWriter;
#endif

#ifdef USE_POSTGRES
	pgsql = new Pgsql;
	pgsql_saver = new PgsqlSaver;
	rule_loader_pgsql = new RuleLoaderPgsql;

	pgsql->Connect(config->get("dbname"),config->get("dbuser"),config->get("dbhost"),config->get("dbpass"));

	rule_loader_pgsql->Proc();
#else
	rule_loader_file = new RuleLoaderFile;
	rule_loader_file->Proc();
	sqlite_dao = new SqliteDao;
	sqlite_dao->Connect(config->get("dbname"));
	sqlite_dao->ConnectMemory();
	sqlite_dao->CreateTableFromFileMemory(config->get("sql_table"));
	sqlite_dao->CreateTableFromFile(config->get("sql_table"));
	sqlite_saver = new SqliteSaver;

#endif


	match_pre_filter = new MatchPreFilter;
	rule_pool->ShowRules();

#ifdef RECOMMENDATION
//	btpgsql = new BTPgsql;
//	url = new Url;
//	filter = new Filter;
//	search_client = new SearchClient;
//	local = new Local;
	browsingtime = new BrowsingTime;
	cf = new CollaborativeFiltering;
#endif



	//Create threads
	//SSS thread
/*
	pthread_t thread_sss_t;
	pthread_create(&thread_sss_t, NULL, thread_sss, NULL);
	pthread_detach(thread_sss_t);
	sleep(1);
*/

///*
	packetcap();
//*/

/*
	//Capture thread
	pthread_t thread_cap;
	status=pthread_create(&thread_cap, NULL, thread_packetcap, NULL);
*/
	gettimeofday(&t1, NULL);
	if (t1.tv_usec < t0.tv_usec) {
		printf("%d.%d\n", t1.tv_sec - t0.tv_sec - 1, 1000000 + t1.tv_usec - t0.tv_usec);
	}else {
		printf("%d.%d\n", t1.tv_sec - t0.tv_sec, t1.tv_usec - t0.tv_usec);
	}

	return 0;
}
