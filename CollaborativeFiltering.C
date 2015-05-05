#include "CollaborativeFiltering.H"
#include "Global.H"

CollaborativeFiltering::CollaborativeFiltering(){
}

multimap<double, string> CollaborativeFiltering::GetUserPearson(){
	multimap<double, string> m;
	m = pearson_map;

	return m;
}

multimap<double, string> CollaborativeFiltering::CalNonEvaValue(map<string, map<string, double> > matrix, string target_str){
	map<string, map<string, double> >::iterator it_matrix;

	multimap<double, string> recom_map;

//	vector<string> user;
//	vector<string>::iterator it_user;


//	it_matrix = matrix.begin();
//	while(it_matrix != matrix.end()){
//		user.push_back((*it_matrix).first);
//		it_matrix++;
//	}
//
//	it_user = user.begin();
//	while(it_user != user.end()){
//		//calculate user simirality
		vector<string> common_item;
		vector<string> target_item;
		map<string, double> user_pearson;
//		string target_str = (*it_user);
		it_matrix = matrix.begin();
		while(it_matrix != matrix.end()){
			if(target_str != (*it_matrix).first){
				common_item = GetCommonEvaItem(matrix[target_str], matrix[(*it_matrix).first]);
				user_pearson[(*it_matrix).first] = CalPearson(common_item, matrix[target_str], matrix[(*it_matrix).first]);
				pearson_map.insert(pair<double, string>(user_pearson[(*it_matrix).first], (*it_matrix).first));
//				pearson_map.insert(pair<double, string>(1, "hoge"));
//				cout << (*it_matrix).first << "\t" << user_pearson[(*it_matrix).first] << endl;
			}
			it_matrix++;
		}

		//korenanisiteruno?
		map<string, double> user_ave;
		target_item = GetTargetEvaItem(matrix[target_str]);
		it_matrix = matrix.begin();
		while(it_matrix != matrix.end()){
			if(target_str != (*it_matrix).first){
				common_item = GetCommonEvaItem(matrix[target_str], matrix[(*it_matrix).first]);
//				cout << common_item.size() << "\tCOMMON" << endl;
//				user_ave[(*it_matrix).first] = GetEvaItemAve(target_item, matrix[(*it_matrix).first]);
				user_ave[(*it_matrix).first] = GetEvaCommonItemAve(common_item, matrix[(*it_matrix).first]);
//				cout << "USERAVE" << user_ave[(*it_matrix).first] << endl;
//				cout << "EVAITEM:" << (*it_matrix).first << "\t" << user_ave[(*it_matrix).first] << endl;
			}
			it_matrix++;
		}

		map<string, double> item_value;
		map<string, double>::iterator it_item_value;

		item_value = matrix[target_str];
		it_item_value = item_value.begin();
		while(it_item_value != item_value.end()){
//			cout << "VAL:" << (*it_item_value).second << endl;
			if((*it_item_value).second == 0){
				string item_str = (*it_item_value).first;

				map<string, double>::iterator it_user_pearson = user_pearson.begin();
				map<string, double>::iterator it_user_ave = user_ave.begin();

				double upper = 0;
				double lower = 0;

//				cout << "LOOP" << endl;
				while(it_user_pearson != user_pearson.end()){
					if((matrix[(*it_user_ave).first])[item_str] != 0){
						upper = upper + (*it_user_pearson).second * ((matrix[(*it_user_ave).first])[item_str] - (*it_user_ave).second);
//						cout << "UP::" << (*it_user_pearson).second << "\t" << ((matrix[(*it_user_ave).first])[item_str]) << "\t" << (*it_user_ave).second << endl;
						lower = lower + fabs((*it_user_pearson).second);
//						cout << "LOW::" << fabs((*it_user_pearson).second) << endl;
//						cout << (*it_user_pearson).second << "\t" << (matrix[(*it_user_ave).first])[item_str] << "\t" << (*it_user_ave).second << endl;
					}
					it_user_pearson++;
					it_user_ave++;
				}

				if(lower != 0){
//					cout << "VAL::::" << GetEvaItemAve(target_item, matrix[target_str]) << "\t" << upper << "\t" <<  lower << endl;
					(matrix[target_str])[item_str] = GetEvaItemAve(target_item, matrix[target_str]) + upper / lower;
					//cout << item_str << "\t" << (matrix[target_str])[item_str] << endl;
					recom_map.insert(pair<double, string>((matrix[target_str])[item_str], item_str));
				}
			}
			it_item_value++;
		}

//		it_user++;
//	}

	return recom_map;
}



double CollaborativeFiltering::GetEvaItemAve(vector<string> vec, map<string, double> item_map){
	vector<string>::iterator it;
	double ave = 0;
	double num = 0;

	it = vec.begin();
	while(it != vec.end()){
		if(item_map[(*it)] != 0){
//			cout << (*it) << "\t" << item_map[(*it)] << endl;
			ave = ave + item_map[(*it)];
			num++;
		}
		it++;
	}

	ave = ave / num;

	if(num == 0){
		ave = 0;
	}

	return ave;

}

double CollaborativeFiltering::GetEvaCommonItemAve(vector<string> common_item, map<string, double> item_map){
	vector<string>::iterator it;
	double ave = 0;
	double num = 0;

	it = common_item.begin();
	while(it != common_item.end()){
		if(item_map[(*it)] != 0){
			ave = ave + item_map[(*it)];
			num++;
		}
		it++;
	}

//	cout << "AVE" << ave << endl;
//	cout << "NUM" << num << endl;

	ave = ave / num;

	if(num == 0){
		ave = 0;
	}

//	cout << ave << endl;

	return ave;

}

vector<string> CollaborativeFiltering::GetTargetEvaItem(map<string, double> item_map){
	map<string, double>::iterator it;
	vector<string> vec;

	it = item_map.begin();

	while(it != item_map.end()){
		if((*it).second > 0){
			vec.push_back((*it).first);
		}
		it++;
	}

	return vec;

}

vector<string> CollaborativeFiltering::GetCommonEvaItem(map<string, double> item_map1, map<string, double> item_map2){
	map<string, double>::iterator it, it2;
	map<string, double> user_map1, user_map2;
	vector<string> vec;

	it = item_map1.begin();
//	it2 = item_map2.begin();

	while(it != item_map1.end()){
//		cout << (*it).second << "  *  " << (*it2).second << endl;
//		if((*it).second * (*it2).second > 0){
		it2 = item_map2.begin();
		while(it2 != item_map2.end()){
//			cout << "VEC:" << (*it).first << endl;
			if((*it).first == (*it2).first){
				vec.push_back((*it).first);
			}
			it2++;
		}
		it++;
	}

//	cout << vec.size() << endl;

	return vec;

}

double CollaborativeFiltering::CalPearson(vector<string> item_vec, map<string, double> item_map, map<string, double> item_map2){
//	map<string, double> item_map;
	vector<string>::iterator it;
	double ave = 0;
	double ave2 = 0;
	double pearson = 0;
	double numerator = 0;
	double donominator = 0;
	double don_left = 0;
	double don_right = 0;

	it = item_vec.begin();
	while(it != item_vec.end()){
//		cout << item_map[*it] << "\t" << item_map2[*it] << endl;
		ave = ave + item_map[(*it)];
		ave2 = ave2 + item_map2[(*it)];
		it++;
	}
	ave = ave / item_vec.size();
	ave2 = ave2 / item_vec.size();

	it = item_vec.begin();
	while(it != item_vec.end()){
		numerator = numerator + (item_map[(*it)] - ave) * (item_map2[(*it)] - ave2);
//		cout << item_map[(*it)] << "\t" << ave << "\t" << item_map2[(*it)] << "\t" << ave2 << endl;
//		cout << "NUUUUUUUUU::::::" << numerator << endl;
		don_left = don_left + pow((item_map[(*it)] - ave), 2);
		don_right = don_right + pow((item_map2[(*it)] - ave2), 2);
		it++;
	}
	donominator = sqrt(don_right) * sqrt(don_left);

	pearson = numerator / donominator;

	if(item_vec.size() <= 1 || donominator == 0){
		pearson = 0;
	}

	return pearson;
}

map<string, map<string, double> > CollaborativeFiltering::InitMatrix(map<string, map<string, double> > matrix, map<string, map<string, double> > matrix_rev, string target_user){
	map<string, map<string, double> >::iterator it_matrix;
	map<string, map<string, double> >::iterator it_matrix_rev;

	it_matrix = matrix.begin();
	while(it_matrix != matrix.end()){
		if(target_user == (*it_matrix).first){
			it_matrix_rev = matrix_rev.begin();
			while(it_matrix_rev != matrix_rev.end()){
				map<string, double> tmp_map;
				tmp_map = (*it_matrix).second;
//				if(((*it_matrix).second).find((*it_matrix_rev).first) == matrix_rev.end()){
				if(tmp_map.find((*it_matrix_rev).first) == tmp_map.end()){
					((*it_matrix).second)[(*it_matrix_rev).first] = 0;
				}
				it_matrix_rev++;
			}
		}
		it_matrix++;
	}

	return matrix;

}

map<string, map<string, double> > CollaborativeFiltering::InitMatrixRev(map<string, map<string, double> > matrix){
	map<string, map<string, double> > matrix_rev;
	map<string, map<string, double> >::iterator it_matrix;
	map<string, map<string, double> >::iterator it_matrix_rev;

//	it_matrix_rev = matrix_rev.begin();
//	while(it_matrix_rev != matrix_rev.end()){
//		it_matrix = matrix.begin();
//		while(it_matrix != matrix.end()){
////			map<string, double> tmp_map;
//			if(tmp_map.find((*it_matrix).first) == tmp_map.end()){
//				((*it_matrix_rev).second)[(*it_matrix).first] = 0;
//			}
//			it_matrix++;
//		}
//		it_matrix_rev++;
//	}

//	matrix_rev.clear();

	it_matrix = matrix.begin();
	while(it_matrix != matrix.end()){
		map<string, double> tmp_map;
		map<string, double>::iterator it_tmp;
		tmp_map = (*it_matrix).second;
		it_tmp = tmp_map.begin();
		while(it_tmp != tmp_map.end()){
			(matrix_rev[(*it_tmp).first])[(*it_matrix).first] = (*it_tmp).second;
			it_tmp++;
		}
		it_matrix++;
	}

	return matrix_rev;

}


map<string, map<string, double> > CollaborativeFiltering::CreateMatrix(string filename){
	ifstream is;
	is.open(filename.c_str());
	if(!is){
		cout << "cannot open" << endl;
		exit(1);
	}

	map<string, map<string, double> > matrix;

	while(!is.fail()){
		string user = "";
		string item = "";
		double rate = 0;
//		map<string, double> item_map;

		is >> user >> item >> rate;

		if(user != "" && item != ""){
//			item_map[item] = rate;
			(matrix[user])[item] = rate;
		}
	
	}


	return matrix;
}

map<string, map<string, double> > CollaborativeFiltering::CreateMatrixRev(string filename){
	ifstream is;
	is.open(filename.c_str());
	if(!is){
		cout << "cannot open" << endl;
		exit(1);
	}

	map<string, map<string, double> > matrix_rev;

	while(!is.fail()){
		string user;
		string item;
		double rate;
//		map<string, double> user_map;

		is >> user >> item >> rate;

		if(user != "" && item != ""){
//			user_map[user] = rate;
			(matrix_rev[item])[user] = rate;
		}
	
	}

	return matrix_rev;
}


//int CollaborativeFiltering::MLEWeibullDistribution(vector<double> time_vec){
int CollaborativeFiltering::MLEWeibullDistribution(const string sql){
//	ifstream is;
//	is.open(filename.c_str());
//	if(!is){
//		cout << "cannnot open" << endl;
//		exit(1);
//	}
//
//	vector<double> time_vec;
//	vector<double>::iterator it;
//
//	while(!is.fail()){
//		double time;
//		is >> time;
//		time_vec.push_back(time);
//	}
//
//	it = time_vec.end();
//	time_vec.erase(--it);

//	Newton(time_vec, 1);
	Newton(sql, 1);

	return 0;

}

//double CollaborativeFiltering::Newton(vector<double> time_vec, double k){
double CollaborativeFiltering::Newton(const string sql, double k){
//	vector<double>::iterator it;
//	result::const_iterator it;
	int count;
	int loop_num = 0;
	int diversity = 0;

	double evenk, oddk;

	sqlite3_stmt* hogehoge;

//	cout << time_vec.size() << endl;

	while(1){
		double squarek = 0;
		double ln = 0;
		double squarek_ln = 0;
		double squarek_squareln = 0;
	
		double n = 0;

		double time = 0;

		//it = time_vec.begin();
		//it = bt_list->begin();
		hogehoge = sqlite_dao->ExecSqlMemory(sql);
	//	while(it != bt_list->end()){
		while(SQLITE_ROW == sqlite3_step(hogehoge)){
			if(string((char *)sqlite3_column_text(hogehoge, 0)) != "none"){
				//time = it[0].as( double() );
				string tmp = (string((char *)sqlite3_column_text(hogehoge, 0)));
				stringstream ss;
				ss.str("");
				ss.clear(stringstream::goodbit);
				ss << tmp;
				ss >> time;
				if(time < 1800 && time > 0){
					squarek = squarek + pow(time, k);
					ln = ln + log(time);
					squarek_ln = squarek_ln + (pow(time, k) * log(time));
					squarek_squareln = squarek_squareln + (pow(time, k) * (pow(log(time), 2)));
					n++;
				}
			}
//			cout << "sample" << *it << endl;

	//		it++;
		}
		if(n < 10){
//			cout << "mottomiteyo--" << endl;
			break;
		}else if(n >= 10){

		double g = 0;
		double gdash = 0;
		double nextk;
		double lambda;

		g = squarek + ((k * squarek * ln) / n) - (k * squarek_ln);
		gdash = (ln / n) * (squarek + (k * squarek_ln)) - (k * squarek_squareln);

		nextk = k - (g / gdash);
		lambda = pow((squarek / n), (1 / k));

		//cout << "g" << g << endl;
		//cout << "gdash" << gdash << endl;
		//cout << "k" << k << endl;


		if(loop_num % 2 == 0){
			evenk = k;
		}else{
			oddk = k;
		}

		if(evenk == oddk){
			diversity++;
			if(diversity == 1000){
				SetK(k);
				SetLambda(lambda);
				//cout << "diversity" << "\t" << k << "\t" << lambda << endl;//debug
				break;
			}
		}

		if(loop_num == 10000){
			//cout << "ENDLOOP" << endl;//debug
			break;
		}

		if((int)(k * 1000000) == (int)(nextk * 1000000)){
			count++;
			if(count == 20){
				SetK(k);
				SetLambda(lambda);
				//cout << k << "\t" << lambda << endl;//debug
				break;
			}
		}else{
			count = 0;
		}

		k = nextk;

		loop_num++;
		}else{
		cout << "error" << endl;
		break;
		}
	}


	return 0;

}

void CollaborativeFiltering::SetLambda(double lambda){
	parameter_lambda = lambda;
}

void CollaborativeFiltering::SetK(double k){
	parameter_k = k;
}

double CollaborativeFiltering::GetK(){
	return parameter_k;
}

double CollaborativeFiltering::GetLambda(){
	return parameter_lambda;
}

void CollaborativeFiltering::InitParameter(){
	SetK(0);
	SetLambda(0);
}

double CollaborativeFiltering::GetValue(double k, double lambda, double browsing_time){
	double value;
	double rate;

//	value = (k / lambda) * (pow((browsing_time / lambda), (k - 1))) * exp(-(pow((2 / lambda), k)));
	value = 1 - exp(-(pow((browsing_time / lambda), k)));

	double timeout = 1800;
	double timeout_value = 1 - exp(-(pow((timeout / lambda), k)));

	double cmp;
	double one_third;
	double two_third;

	double one = 1;
	double two = 2;
	double three = 3;

	one_third = one / three;
	two_third = two / three;

	if(value < (one_third * timeout_value)){
		rate = 1;
	}else if(value >= (one_third * timeout_value) && value < (two_third * timeout_value)){
		rate = 2;
	}else{
		rate = 3;
	}

	return rate;
}

vector<double> CollaborativeFiltering::GetUserSample(string filename, string target_user){
	ifstream is;
	is.open(filename.c_str());

	vector<double> time_vec;

	if(!is){
		cout << "cannnot open" << endl;
		exit(1);
	}

	while(!is.fail()){
		string user;
		string item;
		string tmp;
		double time;
		is >> user >> item >> tmp;
		if(tmp != "none"){
			stringstream ss;
			ss.str("");
			ss.clear(stringstream::goodbit);
			ss << tmp;
			ss >> time;
			if(user == target_user){
//				cout << user << endl;
				time_vec.push_back(time);
			}
		}
	}

	return time_vec;

}

vector<string> CollaborativeFiltering::GetUsers(string filename){
	ifstream is;
	is.open(filename.c_str());

	map<string, string> user_map;
	map<string, string>::iterator it;
	vector<string> users_vec;

	while(!is.fail()){
		string user;
		string item;
		string time;
		is >> user >> item >> time;
		user_map[user] = "";
	}

	it = user_map.begin();
	while(it != user_map.end()){
		if((*it).first != ""){
			users_vec.push_back((*it).first);
		}
		it++;
	}

	return users_vec;

}


int CollaborativeFiltering::Proc(string mac_addr){
	string user;

	ofstream ofs;
	ofs.open("target_prefer.txt");

	map<string, map<string, double> > matrix;
	map<string, map<string, double> > matrix_rev;


//	vector<string> users_vec;
//	vector<string>::iterator it;

//	if(GetUserSample(samplefile, user).size() == 0){
//		cout << "NO SAMPLE" << endl;
//		exit(1);
//	}

//	users_vec = GetUsers(filename);
//	it = users_vec.begin();

	sqlite3_stmt *user_list;
	user_list = sqlite_dao->ExecSqlMemory("select distinct src_mac_addr from save_history;");

//	result::const_iterator it;
//	it = user_list->begin();

//	users_vec.clear();

//	ifstream ifsss;
//	ifsss.open("naihito");
//	while(!ifsss.fail()){
//		string s;
//		ifsss >> s;
//		if(s != ""){
//			users_vec.push_back(s);
//		}
//	}
//	ifsss.close();
//	it = users_vec.begin();

//	while(it != users_vec.end()){
//	while(it != user_list->end()){
	while(SQLITE_ROW == sqlite3_step(user_list)){
		string target_user;
	//	target_user = it[0].as( string() );
		target_user = string((char *)sqlite3_column_text(user_list, 0));
//		cout << target_user << endl;
//		if(target_user != argv[1]){
//			it++;
//			continue;
//		}
//		cout << target_user << endl;
	
//		vector<double> sample_vec;
//		sample_vec = GetUserSample(samplefile, target_user);
//		result *bt_list;
	//	sqlite3_stmt *bt_list;
	//	bt_list = sqlite_dao->ExecSqlMemory("select browsing_time from save_history");
//		string sqlbt = "select browsing_time from save_history;";
//		MLEWeibullDistribution(sqlbt);

//		cout << cf->GetK() << endl;
//		if(sample_vec.size() != 0){
//		if(isnan(GetK()) == 0){
//			ifstream ifs;
//			ifs.open(filename.c_str());
	//		result *bt_his;
	//		bt_his = new result( T.exec("select src_mac_addr, url, browsing_time from save_history") );
	//		result::const_iterator bt_his_it;
	//		bt_his_it = bt_his->begin();
			sqlite3_stmt *bt_his;
	//		bt_his = sqlite_dao->ExecSqlMemory("select src_mac_addr, url, browsing_time from save_history;");
			bt_his = sqlite_dao->ExecSqlMemory("select src_mac_addr, url, Count(*) from save_history where browsing_time = 'none' group by src_ip, url;");
			//string sql2;
			//sql2 = "select Count(*) from save_history where browsing_time = 'none' AND "
			//sql2 += "src_ip = ";
			//sql2 += "target_user"
			//sql2 += " order by datetime(timestamp);";
			//sqlite3_stmt* bt_his_num;
			//bt_his_num = sqlite_dao->ExecSqlMemory(sql2);
//			while(!ifs.fail()){
	//		while(bt_his_it != bt_his->end()){
			while(SQLITE_ROW == sqlite3_step(bt_his)){
				
				string user = string((char *)sqlite3_column_text(bt_his, 0));
				string item = string((char *)sqlite3_column_text(bt_his, 1));
				string tmp = string((char *)sqlite3_column_text(bt_his, 2));
				double time;
//				ifs >> user >> item >> tmp;
				if(tmp != "none"){
					stringstream ss;
					ss.str("");
					ss.clear(stringstream::goodbit);
					ss << tmp;
					ss >> time;
					//cout << user << "\t" << item << "\t" << target_user << endl;
					//if(user == target_user && time <= 1800){
					if(user == target_user){
						//ofs << user << "\t" << item << "\t" << GetValue(GetK(), GetLambda(), time) << endl;
						if(time == 1){
							ofs << user << "\t" << item << "\t" << "1" << endl;
						}else if(time == 2){
							ofs << user << "\t" << item << "\t" << "2" << endl;
						}else{
							ofs << user << "\t" << item << "\t" << "3" << endl;
						}

//					cout << user << "\t" << item << "\t" << "3" << endl;
					}
				}
				//bt_his_it++;
			}
			sqlite3_finalize(bt_his);
//			ifs.close();
	//	}

	//	it++;
	}
	sqlite3_finalize(user_list);

	string ofname1 = "/var/www/html/recom/recommendation/output_recom:";
	//string ofname1 = "./recommendation/output_recom:";
	ofname1 += mac_addr;
	const char *ofname = ofname1.c_str();

//	ofstream ofs2;
//	ofs2.open("recommend_webpages_frequency");
//	ofs2.open("recommend_webpages_dwelltime");
//	ofs2.open("output_recom.txt");
//	ofs2.open(ofname, ios::app);
//	ofs2.open(ofname);
//	it = user_list->begin();
	sqlite3_stmt* user_list2;	
	user_list2 = sqlite_dao->ExecSqlMemory("select distinct src_mac_addr from save_history;");
	multimap<string, double> result_temp;
	int result_num = 0;
	while(SQLITE_ROW == sqlite3_step(user_list2)){
		user = string((char *)sqlite3_column_text(user_list2, 0));
		//cout << user << endl;
		//string test_user = mac_addr == "" ? "68:a8:6d:00:da:f8" : mac_addr;
		string test_user = mac_addr;
		if(user != test_user){
			sqlite3_step(user_list2);
			//it++;
			continue;
		}

		matrix = CreateMatrix("target_prefer.txt");//kokokaihen
		matrix_rev = CreateMatrixRev("target_prefer.txt");//kokokaihen
//		matrix = cf->CreateMatrix("prefer_fre.txt");
//		matrix_rev = cf->CreateMatrixRev("prefer_fre.txt");
		matrix = InitMatrix(matrix, matrix_rev, user);
	//	matrix_rev = cf->InitMatrixRev(matrix);
	
		multimap<double, string> recom_map;
		multimap<double, string>::iterator it_recom_map;
		multimap<double, string> p_map;
		multimap<double, string>::iterator it_p_map;
		recom_map = CalNonEvaValue(matrix, user);
	
		int num = 0;
		double pre_score;
		it_recom_map = recom_map.end();
//		cout << "RECOMMENED WEBPAGES" << endl;i
		while(it_recom_map != recom_map.begin()){
			if(it_recom_map != recom_map.end()){
				if(num >= 10 && pre_score != (*it_recom_map).first){
					break;
				}
				pre_score = (*it_recom_map).first;
			}
			--it_recom_map;
			string::size_type index = (*it_recom_map).second.find("www.google.co.jp");
			if(index == string::npos){
				//cout << test_user << "\t" << (*it_recom_map).second << "\t" << (*it_recom_map).first << endl;
				//ofs2 << (*it_recom_map).second << "\t" << (*it_recom_map).first << endl;
				result_temp.insert(pair<string, double>((*it_recom_map).second, (*it_recom_map).first));
				num++;
				result_num++;
			}
		}
//		it++;
	}
	multimap<string, double>::iterator it_result_temp;
	if(result_num > 0){
		ofstream ofs2;
		ofs2.open(ofname);
		for(it_result_temp = result_temp.begin(); it_result_temp != result_temp.end(); it_result_temp++){
			ofs2 << (*it_result_temp).first << "\t" << (*it_result_temp).second << endl;
		}
		ofs2.close();

		//chmod
		string kengen1 = "";
		kengen1 += "chmod 777 ";
		kengen1 += ofname1;
		const char *kengen = kengen1.c_str();
		system(kengen);
	}
	
	return 0;

}
