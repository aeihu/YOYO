/*
* Copyright (C) 2012-2016, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CLUA_H_ 
	#define _CLUA_H_

#include "lua.hpp"
#include <string>
#include <SFML/System.hpp>

using namespace std;

class CLua
{
	public:
		CLua();
		~CLua();

		bool OnInit();
		bool LoadScript(string filename);
		void OnCleanup();
	private:
		lua_State* _luaState;
		sf::Thread _thread;
		sf::Mutex _mutex;
		string _currentScriptName;

		void RunScript();
};

#endif
