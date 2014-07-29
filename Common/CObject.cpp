/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CObject.h"

CObject::CObject()
{
    _path = _className = ""; 
}

string CObject::GetClassName() const
{
    return _className;
}
        
string CObject::GetPath() const
{
    return _path;
}
        
void CObject::OnSaveData(ofstream& file) const
{
    file << "class_name=" << _className << endl;
    file << "path=" << _path << endl;
}

void CObject::SetClassName(string name)
{
    _className = name;
}

void CObject::SetPath(string path)
{
    _path = path;
}
