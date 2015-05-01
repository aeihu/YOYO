/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CSequenceOfAction.h"

bool CSequenceOfAction::OnLoop(bool cleanup)
{
    do {
        if (!_actionList.empty()){
            if (_skip)
                _actionList.front()->Skip();

            if (_actionList.front()->OnLoop(cleanup)){
                if (!cleanup)
                    _tempActionList.push_back(_actionList.front());

                 _actionList.pop_front();
            }
        }
        else
            _skip = false;
    } while (_skip);
    
    if (_actionList.empty()){
        if (cleanup)
            OnCleanup();
        else
            _actionList.swap(_tempActionList);
        
        return true;
    }

    return false;
}

bool CSequenceOfAction::IsPause() const
{
    if (_actionList.size() < 1)
        return false;

    return _pause || _actionList.front()->IsPause();
}

CActionBaseClass* CSequenceOfAction::Copy()
{
    CSequenceOfAction* __result = new CSequenceOfAction();
    if (!CopyList(__result)){
        delete __result;
        return NULL;
    }

    return __result;
}