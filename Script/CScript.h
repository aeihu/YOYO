/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
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
    
    public:
        bool AddVariable(string name, string val);
        bool SetVariable(string name, string val);
        string GetVariable(string name);
        bool DelVariable(string name);
        
        virtual bool OnInit(string filename)=0;
        virtual bool LoadScript(string filename)=0;
};

#endif
