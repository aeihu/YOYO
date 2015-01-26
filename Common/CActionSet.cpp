/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CActionSet.h"

CActionSet::CActionSet()
{
}

bool CActionSet::IsPause()
{
    return _pause || 
        (_actionList.size() < 1 ? 
            false : _actionList.front()->IsPause());
}

void CActionSet::AddAction(CActionBaseClass* act)
{
    if (act != NULL)
        _actionList.push_back(act);
}

void CActionSet::OnCleanup()
{
    if (_actionList.empty() && _tempActionList.empty())
        return;

    for (list<CActionBaseClass*>::iterator it=_actionList.begin();it!=_actionList.end(); it++){
        (*it)->OnCleanup();
        delete (*it);
        (*it) = NULL;
    }
    _actionList.clear();

    for (list<CActionBaseClass*>::iterator it=_tempActionList.begin();it!=_tempActionList.end(); it++){
        (*it)->OnCleanup();
        delete (*it);
        (*it) = NULL;
    }
    _tempActionList.clear();
}
