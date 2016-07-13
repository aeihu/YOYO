/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CRepeatOfAction.h"

CRepeatOfAction::CRepeatOfAction(string name, bool pause, int loopNum)
{
    _count = 0;
    _loopNum = loopNum;
    _name = name;
    _pauseRequest = pause;

    if (_pauseRequest)
        _numOfPauseActions++;
}
        
bool CRepeatOfAction::PauseRequest() const
{
    if (_iterator == _actionList.end() || _count == 0)
        return false;

    return _pauseRequest || (*_iterator)->PauseRequest();
}

bool CRepeatOfAction::OnLoop()
{
    if (_loopNum == 0){
        OnCleanup();
        return true;
    }

    do {
        if (_actionList.end() != _iterator){
            if (_skip)
                (*_iterator)->Skip();

            if ((*_iterator)->OnLoop())
                _iterator++;
        }
        else
            _skip = false;
    } while (_skip);

    if (_actionList.end() == _iterator){
        _iterator = _actionList.begin();
        if (_loopNum > 0){
            if (_count > 0){
                --_count;

                if (_count == 0){
                    if (IsDelete())
                        OnCleanup();

                    return true;
                }
            }
        }
    }

    return false;
}

CActionBaseClass* CRepeatOfAction::Copy()
{
    CRepeatOfAction* __result = new CRepeatOfAction(_name, _pauseRequest, _loopNum);
    if (!CopyList(__result)){
        delete __result;
        return NULL;
    }
    
    return __result;
}
