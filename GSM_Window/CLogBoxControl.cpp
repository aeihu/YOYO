/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CLogBoxControl.h"

CObject* CLogBoxControl::GetObject(std::string name)
{
    if (_logBoxList.count(name) < 1)
        return NULL;

    CBox* __p = &_logBoxList[name];
    return __p;
}