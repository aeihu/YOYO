/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CPARSER_H_
    #define _CPARSER_H_

#include <string>
//#include <list>
#include <vector>
#include <map>
#include <iostream>
#include <exception>
#include <cstdio>
#include "../GSM_Window/CMessageBox.h"
#include "CScriptCommand.h"
#include "../Common/CCommon.h"
#include "../Common/Cio.h"

using namespace std;

class CParser
{
    private:        
        vector<string>          _cmdList;
        unsigned long           _delay;
        bool*                   _pRunning;
        size_t                  _index;

        int AnalysisOfParameters(string para, vector<string> &plist);

        bool (*_pFunc)(vector<string>&);
    public:
        static CParser _Parser;
        CParser();

        void reset();
        void SetIndex(size_t i);
        size_t GetIndex();
        void OnLoop();
        void OnCleanup();

        void ExecuteCmd(string cmd);
        void InsertCmd(string cmd);
        void SetDeplay(int ms);

        bool IsDeplaying();
        void SetRunning(bool* running);
};

#endif
