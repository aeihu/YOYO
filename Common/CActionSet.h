/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CACTIONSET_H_
    #define _CACTIONSET_H_

#include "CActionBaseClass.h"
#include <list>

using namespace std;

class CActionSet : public CActionBaseClass
{
    private:
    protected:
        list<CActionBaseClass*>     _actionList;
    public:
        virtual void AddAction(CActionBaseClass* act);
        //virtual bool OnLoop();
        virtual bool IsPause();
};

#endif
