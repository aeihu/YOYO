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
    //list<string> __expressions = Cio::LoadTxtFile(FileName, "\r\n");
    //map<string, string> __valueList;

 /*   for (list<string>::iterator it=__expressions.begin();
        it!=__expressions.end(); it++){
        string __paraName = "";
        string __paraValue = "";
        if(Cio::AnalyticExpression((*it), __paraName, __paraValue))
            __valueList[__paraName] = __paraValue;
    }*/

    if (!CheckList(json))
        return false;

    if (!SetProperty(json))
        return false;

    return true;
}