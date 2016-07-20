/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CSimultaneousOfAction.h"

CSimultaneousOfAction::CSimultaneousOfAction(string name)
{
    _name = name;
}

bool CSimultaneousOfAction::OnLoop()
{
    size_t __count = 0;
    for (list<pair<CActionBaseClass*, bool> >::iterator it = _actionList.begin(); it != _actionList.end();){
        if (!(*it).second){
            if (_skip)
                (*it).first->Skip();

            if ((*it).first->OnLoop()){
                (*it).second = true;
                __count++;
            }
        }
        else
            __count++;
            
        ++it;
    }
    _skip = false;

    if (_actionList.size() == __count){
        if (IsDelete())
            OnCleanup();

        return true;
    }

    return false;
}

CActionBaseClass* CSimultaneousOfAction::Copy()
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction(_name);
    if (!CopyList(__result)){
        delete __result;
        return NULL;
    }

    return __result;
}