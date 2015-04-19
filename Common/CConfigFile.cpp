/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CConfigFile.h"
        

bool CConfigFile::LoadConfigFile(const char* FileName)
{
    __json.reset();
    __json.parse(Cio::LoadTxtFile(FileName));

    if (!CheckList(__json))
        return false;

    if (!SetProperty(__json))
        return false;

    return true;
}
        
void CConfigFile::Reset()
{
    SetProperty(__json, false);
}