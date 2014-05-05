/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CAdder.h"

CfAdder::CfAdder(char type, float goal, bool pause, float* val, float val1, float val2, float val3, float val4)
{
    _type = type;
    _pFloat = val;
    _value = *val;
    _par1 = val1;
    _par2 = val2;
    _par3 = val3;
    _par4 = val4;
    _goal = goal;
    _oldTime = 0;
    _pause = pause;
    _pInt = NULL;
}

CfAdder::CfAdder(char type, float goal, bool pause, int* val, float val1, float val2, float val3, float val4)
{
    _type = type;
    _pInt = val;
    _value = static_cast<float>(*val);
    _par1 = val1;
    _par2 = val2;
    _par3 = val3;
    _par4 = val4;
    _goal = goal;
    _oldTime = 0;
    _pause = pause;
    _pFloat = NULL;
}

bool CfAdder::Check()
{
    if (_pFloat == NULL && _pInt == NULL){
        return false;
    }
    return true;
}

void CfAdder::SetValue(float val)
{
    _value = val;
    if (_pFloat){
        *_pFloat = val;
        return;
    }

    if (_pInt)
        *_pInt = static_cast<int>(val);
}

bool CfAdder::Recursion()
{
    if (_value < _goal){
        SetValue(_value+_par1);
        if (_value >= _goal){
            SetValue(_goal);
            return true;
        }
    }
    else if (_value > _goal){
        SetValue(_value-_par1);
        if (_value <= _goal){
            SetValue(_goal);
            return true;
        }
    }
    return false;
}

bool CfAdder::DecreaseRecursion()
{
    if (_value < _goal){
        SetValue(_value + (_goal - _value)/_par1 + _par2);
        if (_value>=_goal){
            SetValue(_goal);
            return true;
        }
    }
    else if (_value > _goal){
        SetValue(_value - (_value - _goal)/_par1 + _par2);
        if (_value<=_goal){
            SetValue(_goal);
            return true;
        }
    }
    return false;
}

bool CfAdder::Oscillate()
{
    if (_par1<_goal){
        SetValue(_par2*sin(_par1/360*2*PI));
        _par1+=_par3;

        if (_par1>=_goal)
            SetValue(_goal);
        else
            return false;
    }
    else if (_par1>_goal){
        SetValue(_par2*sin(_par1/360*2*PI));
        _par1-=_par3;

        if (_par1<=_goal)
            SetValue(_goal);
        else
            return false;
    }

    _par4--;
    if (_par4>0.0f){
        _par1=0.0f;
        return false;
    }
    return true;
}
