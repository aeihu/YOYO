/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CActionBaseClass.h"
#include <iostream>

using namespace std;

bool CActionBaseClass::_allSkip = false;

CActionBaseClass::CActionBaseClass()
{
    _name = "";
    _skip = false;
}

CActionBaseClass::~CActionBaseClass()
{
}

string CActionBaseClass::GetName() const 
{ 
    return _name;
}

void CActionBaseClass::SetName(string name)
{
    _name = name;
}

void CActionBaseClass::SetSkip()
{ 
    _skip = true; 
}

void CActionBaseClass::AllSkipOn()
{
    _allSkip = true;
}

void CActionBaseClass::AllSkipOff()
{
    _allSkip = false;
}