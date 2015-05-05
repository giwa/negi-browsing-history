#pragma once
#include "Include.H"

class Local{
	private:
//		map<string, string> user_agent_map;

	public:
		Local();
		int Identify();
		int ReconstructByCookie();
		int ReconstructByRef();
		map<string, string> CookieParse(string str);
		map<string, string> CookieParseURLLevel(string str);
		int Show();
		int GetCookieValueNum(string cookie);
};
