/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CSimultaneousOfAction.h"

bool CSimultaneousOfAction::OnLoop(bool cleanup)
{
    for (list<CActionBaseClass*>::iterator it=_actionList.begin();it!=_actionList.end(); ){
        if (_skip)
            (*it)->Skip();

        if ((*it)->OnLoop(cleanup)){
            if (!cleanup)
                _tempActionList.push_back(*it);

            it=_actionList.erase(it);
        }
        else{
            ++it;
        }
    }
    _skip = false;

    if (_actionList.empty()){
        if (cleanup)
            OnCleanup();
        else
            _actionList.swap(_tempActionList);
        
        return true;
    }

    return false;
}

bool CSimultaneousOfAction::IsPause() const
{
    if (_actionList.size() < 1)
        return false;

    if (_pause)
        return true;

    for (list<CActionBaseClass*>::const_iterator it=_actionList.begin();it!=_actionList.end(); it++){
        if ((*it)->IsPause())
            return true;
    }

    return false;
}