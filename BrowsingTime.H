#pragma once
#include "Include.H"
//#include "Global.H"


class BrowsingTime{
	private:
		int testval;
		map<string, string> pretimestamp;
		map<string, string> prepretimestamp;
		map<string, string> preprepretimestamp;

	public:
		BrowsingTime();
		~BrowsingTime();
		int Proc(string mac_addr);
};
