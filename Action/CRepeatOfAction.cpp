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
    _count = _loopNum = 0;
}
        
bool CRepeatOfAction::IsPause() const
{
    if (_actionList.size() < 1 || _count == 0)
        return false;

    return _pause || _actionList.front()->IsPause();
}

bool CRepeatOfAction::OnLoop(bool cleanup)
{
    if (_loopNum == 0){
        OnCleanup();
        return false;
    }

    do {
        if (!_actionList.empty()){
            if (_skip)
                _actionList.front()->Skip();

            if (_actionList.front()->OnLoop(_count == 0 && cleanup)){
                if (!cleanup || _count != 0)
                    _tempActionList.push_back(_actionList.front());

                _actionList.pop_front();
            }
        }
        else
            _skip = false;
    } while (_skip);

    if (_actionList.empty()){
        if (_count > 0){ 
            --_count;
            
            if (_count == 0){
                if (cleanup){
                    OnCleanup();
                }
                else{
                    _actionList.swap(_tempActionList);
                    _count = _loopNum;
                }

                return true;
            }
            else// bigger then 0
                _actionList.swap(_tempActionList);
        }
        else// smaller then 0
            _actionList.swap(_tempActionList);
    }

    return false;
}

void CRepeatOfAction::SetLoopNum(int num)
{
    _count = _loopNum = num;
}
