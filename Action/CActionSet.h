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
        bool                                            _isDelete;
        
        void SetIsDelete(CActionBaseClass* act, bool b);
    protected:
        string                                          _name;
        list<pair<CActionBaseClass*, bool> >::iterator  _iterator;
        list<pair<CActionBaseClass*, bool> >            _actionList;

        bool CopyList(CActionSet* act);
        bool IsDelete() const;
        void RestoreActionList();
    public:
        CActionSet();
        virtual void AddAction(CActionBaseClass* act);
        virtual string GetName() const;
        bool DeleteAct(string name, bool skip);

        void OnCleanup();
        virtual inline EActType GetType() { return ACTION_SET;}
};

#endif
