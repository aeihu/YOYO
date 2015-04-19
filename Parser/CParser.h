/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CPARSER_H_
    #define _CPARSER_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <exception>
#include <cstdio>
#include "../GSM_Window/CMessageBox.h"
#include "CScriptCommand.h"
#include "../Common/CCommon.h"
#include "../Common/Cio.h"
#include "../Action/CRepeatOfAction.h"
#include "../Action/CDeplayOfAction.h"


using namespace std;

class CParser
{
    private:
        Array                   _cmdList;
        unsigned long           _delay;
        bool*                   _pRunning;
        size_t                  _index;
        bool                    _pause;

        int AnalysisOfParameters(string para, vector<string> &plist);
        void ParserObject(Object& obj, CActionSet* act, bool isEffect);

        bool (*_pFunc)(vector<string>&, CActionSet*);
    public:
        static CParser _Parser;
        CParser();
        
        void Pause();
        void Continue();
        void Reset();
        void GoToIndex(size_t i);
        size_t GetIndex();
        void OnLoop();
        void OnCleanup();
        
        void Execute(Array& commands, size_t i, CActionSet* act, bool isEffect);
        void ExecuteCmd(string cmd, CActionSet* act, bool isEffect);
        void InsertCmd(Array cmd);
        void SetDeplay(int ms);

        bool IsDeplaying();
        void SetRunning(bool* running);
        void OnSaveData(Object& json) const;
        void OnLoadData(Object json);
};

#endif
