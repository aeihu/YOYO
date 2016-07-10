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
    private:
        lua_State*  _luaState; 
        lua_State*  _luaThread;
        sf::Thread  _thread;
        sf::Mutex   _mutex;

        string      _currentScriptName;
        string      _codeAtBeginOfScript;
        string      _codeAtEndOfScript;

        void RunScript();

    public:
        CLua();
        ~CLua();

        bool OnInit();
        void OnCleanup();
        bool LoadScript(string filename, string codeAtB = "", string codeAtE = "");
        bool GetGlobal(const char* name, bool &val);
        int GetLuaThreadStatus() const;
        int ResumeLuaThread();
};

#endif
