/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CSequenceOfAction.h"

CSequenceOfAction::CSequenceOfAction(string name)
{
    _name = name;
    _skip = false;
}

bool CSequenceOfAction::OnLoop()
{
    do {
        if (_iterator != _actionList.end()){
            if (_skip || _allSkip)
                (*_iterator).first->SetSkip();

            if ((*_iterator).first->OnLoop()){
                (*_iterator).second = true;
                _iterator++;
            }
        }
        else
            _skip = false;
    } while (_skip);
    
    if (_iterator == _actionList.end()){
        if (IsDelete())
            OnCleanup();
        
        return true;
    }

    return false;
}

CActionBaseClass* CSequenceOfAction::Copy()
{
    CSequenceOfAction* __result = new CSequenceOfAction(_name);
    if (!CopyList(__result)){
        delete __result;
        return NULL;
    }

    return __result;
}
