/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CSimultaneousOfAction.h"


void CSimultaneousOfAction::AddAction(CActionBaseClass* act)
{
    if (act != NULL)
        _actionList.push_back(act);
}

bool CSimultaneousOfAction::IsPause()
{
    return _pause || 
        (_actionList.size() < 1 ? 
            false : _actionList.front()->IsPause());
}

bool CSimultaneousOfAction::OnLoop()
{
    for (list<CActionBaseClass*>::iterator it=_actionList.begin();it!=_actionList.end(); ){
        if ((*it)->OnLoop()){
            delete (*it);
            (*it) = NULL;
            it=_actionList.erase(it);
            if (it == _actionList.end())
                break;
        }
        else{
            ++it;
        }
    }

    return _actionList.empty();
}