/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
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

        virtual bool CopyList(CActionSet* act);
    public:
        CActionSet();
        virtual void AddAction(CActionBaseClass* act);
        virtual bool IsPause() const=0;
        virtual string GetName() const;
        void SetName(string name);
        void SetPause(bool pause);
        bool DeleteAct(string name, bool skip);

        void OnCleanup();
        virtual inline EActType GetType() { return ACTION_SET;}
};

#endif
