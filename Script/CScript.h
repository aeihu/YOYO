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
#include "..\Action\CSequenceOfAction.h"

using namespace jsonxx;
using namespace std;

class CScript
{
    protected:
        map<string, CSequenceOfAction*>  _scriptList;
    
    public:
        bool AddScript(string name, Array scr);
        bool DelScript(string name);
        virtual void OnCleanup();
        //const CSequenceOfAction& GetScript(string name) const;
};

#endif
