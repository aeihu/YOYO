/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CActionSet.h"

bool CActionSet::IsPause()
{
    return _pause || 
        (_actionList.size() < 1 ? 
            false : _actionList.front()->IsPause());
}

//bool CActionSet::OnLoop()
//{
//    if (!_actionList.empty()){
//        if (_actionList.front()->OnLoop()){
//            delete _actionList.front();
//            _actionList.erase(_actionList.begin());
//        }
//    }
//    
//    return _actionList.empty();
//}

void CActionSet::AddAction(CActionBaseClass* act)
{
    if (act != NULL)
        _actionList.push_back(act);
}