/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CAdder.h"

CiAdder::CiAdder(char type, int goal, unsigned int interval, bool pause, int* val, int val1, int val2, int val3, int val4)
{
    _type = type;
    _pValue = val;
    _value1 = val1;
    _value2 = val2;
    _value3 = val3;
    _value4 = val4;
    _goal = goal;
    _oldTime = 0;
    _pause = pause;
}

bool CiAdder::Check()
{
    if (_pValue == 0){
        return false;
    }
    return true;
}

bool CiAdder::Recursion()
{
    if (*_pValue < _goal){
        *_pValue += _value1;
        if (*_pValue >= _goal){
            *_pValue = _goal;
            return true;
        }
    }
    else if (*_pValue > _goal){
        *_pValue -= _value1;
        if (*_pValue <= _goal){
            *_pValue = _goal;
            return true;
        }
    }
    return false;
}

bool CiAdder::DecreaseRecursion()
{
    if (*_pValue < _goal){
        *_pValue += (_goal - *_pValue)/_value1 + _value2;
        if (*_pValue>=_goal){
            *_pValue = _goal;
            return true;
        }
    }
    else if (*_pValue > _goal){
        *_pValue -= (*_pValue - _goal)/_value1 + _value2;
        if (*_pValue<=_goal){
            *_pValue = _goal;
            return true;
        }
    }
    return false;
}
