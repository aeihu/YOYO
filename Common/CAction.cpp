/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CAction.h"

//CAction::CAction(int* val, int fin, float inc)
//{
//    _data._int = val;
//    _dataOfFinish._int = fin;
//    _incr = inc;
//    _type = INT;
//}

CAction::CAction(void* func, bool pause)
{
    _pause = pause;
}

CAction::CAction(float* val, float fin, float inc, bool pause)
{
    _val = val;
    _valOfFinish = fin;
    _incr = inc;
    _pause = pause;
}

bool CAction::OnLoop()
{
    
    if ((*_val) != _valOfFinish){
        (*_val) += _incr;

        if (_incr < 0){
            if ((*_val) < _valOfFinish){
                (*_val) = _valOfFinish;
                return true;
            }
        }
        else if (_incr > 0)
            if ((*_val) > _valOfFinish){
                (*_val) = _valOfFinish;
                return true;
            }

        return false;
    }
    else
        return true;
}