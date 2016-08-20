/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CConfigFile.h"
        

bool CConfigFile::LoadConfigFile(const char* FileName)
{
    _json.reset();
    _json.parse(Cio::LoadTxtFile(FileName));

    if (!CheckList(_json))
        return false;

    if (!SetProperty(_json))
        return false;

    return true;
}
        
void CConfigFile::Reset()
{
    SetProperty(_json, false);
}