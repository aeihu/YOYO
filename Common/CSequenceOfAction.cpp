/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CSequenceOfAction.h"

bool CSequenceOfAction::OnLoop()
{
    if (_skip){
        for (list<CActionBaseClass*>::iterator it=_actionList.begin();it!=_actionList.end(); ){
            (*it)->Skip();

            if ((*it)->OnLoop()){
                delete (*it);
                (*it) = NULL;
                //it=_actionList.erase(it);
                //if (it == _actionList.end())
                //    break;
            }
            else{
                ++it;
            }
        }
        _actionList.clear();
    }
    
    if (!_actionList.empty()){
        if (_actionList.front()->OnLoop()){
            delete _actionList.front();
            _actionList.erase(_actionList.begin());
        }
    }
    
    return _actionList.empty();
}
