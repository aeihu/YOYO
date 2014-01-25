/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CAdder.h"

CAdder::CAdder()
{
    _type = 0;
    _oldTime = 0;
    _interval = 0;
    _pause = false;
}

CAdder::~CAdder()
{}

bool CAdder::Exec(unsigned long time)
{
    if (_oldTime + _interval > time)
        return false;

    if (!Check())
        return true;

    _oldTime = time;

    switch (_type){
        case 0:
            if (Recursion()){
                return true;
            }
            return false;
        break;
        case 1:
            if (DecreaseRecursion()){
                return true;
            }
            return false;
        break;
        case 2:
            if (Oscillate()){
                return true;
            }
            return false;
        break;
        case 3:
        break;
    }

    return true;
}

bool CAdder::IsPause()
{
    return _pause;
}

bool CAdder::Oscillate()
{
    return true;
}

