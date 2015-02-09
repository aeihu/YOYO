/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CSequenceOfAction.h"

bool CSequenceOfAction::OnLoop(bool cleanup)
{
    if (!_actionList.empty()){
        if (_skip)
            _actionList.front()->Skip();

        if (_actionList.front()->OnLoop(cleanup)){
            _tempActionList.push_back(_actionList.front());
            _actionList.pop_front();
            //delete _actionList.front();
            //_actionList.erase(_actionList.begin());
        }
        _skip = false;
    }
    
    if (_actionList.empty()){
        if (cleanup)
            OnCleanup();
        else
            _actionList.swap(_tempActionList);
        
        return true;
    }

    return false;
}
