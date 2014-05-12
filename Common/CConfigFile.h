/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CCONFIGFILE_H_
    #define _CCONFIGFILE_H_

#include <map>
#include <string>
#include "Cio.h"

using namespace std;

class CConfigFile
{
    protected:
        virtual bool CheckList(map<string, string>& list)=0;
        virtual bool SetProperty(map<string, string>& list)=0;
    public:
        virtual bool LoadConfigFile(const char* FileName);
};

#endif
