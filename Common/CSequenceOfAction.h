/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/


#ifndef _CSEQUENCEOFACTION_H_
    #define _CSEQUENCEOFACTION_H_

#include "CAction.h"
#include <vector>

using namespace std;

class CSequenceOfAction
{
    private:
        vector<CAction>     _actionList;
    protected:
    public:
        void AddAction(CAction act);
        bool OnLoop();
};

#endif
