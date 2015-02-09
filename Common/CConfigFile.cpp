/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CConfigFile.h"
        

bool CConfigFile::LoadConfigFile(const char* FileName)
{
    Object json;
    json.parse(Cio::LoadTxtFile(FileName));

    if (!CheckList(json))
        return false;

    if (!SetProperty(json))
        return false;

    return true;
}