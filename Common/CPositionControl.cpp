/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CPositionControl.h"

void CPositionControl::AddPosition(string name, float x, float y)
{
    _positionList[name].x = x;
    _positionList[name].y = y;
}

void CPositionControl::DelPosition(string name)
{
    if (_positionList.count(name)>0)
        _positionList.erase(name);
}

bool CPositionControl::GetPosition(string name, float* x, float* y)
{
    if (_positionList.count(name)<1)
        return false;

    if (x != NULL) *x=_positionList[name].x;
    if (y != NULL) *y=_positionList[name].y;
    return true;
}