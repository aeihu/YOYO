/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CPosition.h"

void CPosition::AddPosition(string name, float x, float y)
{
    _positions[name].x = x;
    _positions[name].y = y;
}

void CPosition::DelPosition(string name)
{
    if (_positions.count(name)>0)
        _positions.erase(name);
}

bool CPosition::GetPosition(string name, float* x, float* y)
{
    if (_positions.count(name)<1)
        return false;

    if (x != NULL) *x=_positions[name].x;
    if (y != NULL) *y=_positions[name].y;
    return true;
}