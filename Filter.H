#pragma once
#include "Include.H"

class Filter{
	private:
		vector<string> removed_url;
	
	public:
		Filter();
//		int CalTimeDef();
		int TimeDiffFilter();
		int RefFilter();
		int RefFilterAdv();
		int GoogleRedirectFilter();
		int ResponseExistenceFilter();
		int ExtensionFilter();
		int ContentTypeFilter();
		int HTTPStatusFilter();
		int URLFilter();
		int ErrorFilter();//satoshi_added
		int TitleExitFilter();//satoshi_added
		int TitleFilter();
		int Erase();
		int EraseGoogle();
		int AloneFilter();
		int WhiteList();
		vector<string> LoadFocusHost();
		vector<string> GetCookieVariety(string cookie);
		map<string, string> GetCookieVarietyValue(string cookie);
};
