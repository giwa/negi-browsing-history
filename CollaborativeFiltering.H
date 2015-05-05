#pragma once

#include "Include.H"
//#include "Global.H"

//using namespace std;
//using namespace pqxx;

class CollaborativeFiltering{
	private:
		double parameter_k;
		double parameter_lambda;
		vector<string> GetCommonEvaItem(map<string, double> item_map1, map<string, double> item_map2);
		vector<string> GetTargetEvaItem(map<string, double> item_map);
		double CalPearson(vector<string> item_vec, map<string, double> item_map, map<string, double> item_map2);
		double GetEvaItemAve(vector<string> vec, map<string, double> item_map);
		double GetEvaCommonItemAve(vector<string> common_item, map<string, double> item_map);
		//double Newton(vector<double> time_vec, double k);
		double Newton(const string sql, double k);
		void SetK(double k);
		void SetLambda(double lambda);

		multimap<double, string> pearson_map;

	public:
		CollaborativeFiltering();
		int ConstructMatrix();
		map<string, map<string, double> > CreateMatrix(string filename);
		map<string, map<string, double> > CreateMatrixRev(string filename);
		map<string, map<string, double> > InitMatrix(map<string, map<string, double> > matrix, map<string, map<string, double> > matrix_rev, string target_user);
		map<string, map<string, double> > InitMatrixRev(map<string, map<string, double> > matrix);
		multimap<double, string> CalNonEvaValue(map<string, map<string, double> > matrix, string target_str);
		//int MLEWeibullDistribution(vector<double> time_vec);
		int MLEWeibullDistribution(const string sql);
		double GetK();
		double GetLambda();
		double GetValue(double k, double lambda, double browsing_time);
		void InitParameter();
		vector<double> GetUserSample(string filename, string target_user);
		vector<string> GetUsers(string filename);
		multimap<double, string> GetUserPearson();
		int Proc(string mac_addr);
};
