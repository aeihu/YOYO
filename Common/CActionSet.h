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
        string                      _name;
    protected:
        list<CActionBaseClass*>     _actionList;
        list<CActionBaseClass*>     _tempActionList;
    public:
        CActionSet();
        virtual void AddAction(CActionBaseClass* act);
        virtual bool IsPause();
        string GetName() const;
        void SetName(string name);
        bool DeleteAct(string name);

        void OnCleanup();
};

#endif
