/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CAdder.h"

CfAdder::CfAdder(char type, float goal, bool pause, float* val, float val1, float val2, float val3, float val4)
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

bool CfAdder::Check()
{
    if (_pValue == 0){
        return false;
    }
    return true;
}

bool CfAdder::Recursion()
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

bool CfAdder::DecreaseRecursion()
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

bool CfAdder::Oscillate()
{
    if (_value1<_goal){
        *_pValue = _value2*sin(_value1/360*2*PI);
        _value1+=_value3;

        if (_value1>=_goal)
            *_pValue = _goal;
        else
            return false;
    }
    else if (_value1>_goal){
        *_pValue = _value2*sin(_value1/360*2*PI);
        _value1-=_value3;

        if (_value1<=_goal)
            *_pValue = _goal;
        else
            return false;
    }

    _value4--;
    if (_value4>0.0f){
        _value1=0.0f;
        return false;
    }
    return true;
}
