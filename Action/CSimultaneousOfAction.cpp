/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CSimultaneousOfAction.h"

CSimultaneousOfAction::CSimultaneousOfAction(string name, bool pause)
{
    _name = name;
    _pauseRequest = pause;

    if (_pauseRequest)
        _numOfPauseActions++;
}

bool CSimultaneousOfAction::OnLoop()
{
    size_t __count = 0;
    for (list<CActionBaseClass*>::iterator it=_actionList.begin();it!=_actionList.end(); ){
        if (_skip)
            (*it)->Skip();

        if ((*it)->OnLoop()){
            __count++;
        }
            
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

bool CSimultaneousOfAction::PauseRequest() const
{
    size_t __count = 0;
    for (list<CActionBaseClass*>::const_iterator it=_actionList.begin();it!=_actionList.end(); it++){
        if ((*it)->PauseRequest())
            return true;

        __count++;
    }

    return __count < 1 ? false : _pauseRequest;
}

CActionBaseClass* CSimultaneousOfAction::Copy()
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction(_name, _pauseRequest);
    if (!CopyList(__result)){
        delete __result;
        return NULL;
    }

    return __result;
}