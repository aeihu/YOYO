/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CRepeatOfAction.h"

CRepeatOfAction::CRepeatOfAction()
{
    _iterator = _actionList.begin();
}

bool CRepeatOfAction::OnLoop()
{
    if (_loopNum == 0){
        for (list<CActionBaseClass*>::iterator it=_actionList.begin();it!=_actionList.end(); it++){
            delete (*it);
            (*it) = NULL;
        }
        _actionList.clear();
        return true;
    }
    
    if (_iterator == _actionList.end()){
        if (_loopNum > 0) 
            --_loopNum;

        _iterator = _actionList.begin();
    }
    else{
        if ((*_iterator)->OnLoop())
            _iterator++;
    }

    return false;
}

void CRepeatOfAction::SetLoopNum(int num)
{
    _loopNum = num;
}
