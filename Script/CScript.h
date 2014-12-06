/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CSCRIPT_H_
    #define _CSCRIPT_H_

#include <string>
#include <map>
#include "jsonxx.h"

using namespace jsonxx;
using namespace std;

class CScript
{
    protected:
        map<string, string>         _userVariableList;
        map<string, string>         _systemVariableList;
        //map<string, string>         _imagesInScript;
        //map<string, string>         _backgraundInScript;
        //map<string, string>         _musicInScript;
        //map<string, string>         _seInScript;
        //map<string, string>         _voiceInScript;
        //map<string, string>         _characterInScript;
        //map<string, string>         _buttonInScript;
    
    public:
        bool AddVariable(string name, string val);
        bool SetVariable(string name, string val);
        
        virtual bool OnInit(string filename)=0;
        virtual bool LoadScript(string filename)=0;
};

#endif
