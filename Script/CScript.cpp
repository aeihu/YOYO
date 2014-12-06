/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CScript.h"
#include "../Common/Cio.h"

bool CScript::AddVariable(string name, string val)
{
    if(_userVariableList.count("$"+name) > 0)
        return false;

    _userVariableList["$"+name] = val;
    return true;
}

bool CScript::SetVariable(string name, string val)
{
    if(_userVariableList.count("$"+name) > 0){
        _userVariableList["$"+name] = val;
        return true;
    }

    return false;
}

//bool CScript::OnInit(string filename)
//{
//    Object json;
//    if (!json.parse(Cio::LoadTxtFile(filename)))
//        return false;
//    
//
//    return true;
//
//}
//
//bool CScript::LoadScript(string filename)
//{
//    
//    Object json;
//    if (!json.parse(Cio::LoadTxtFile(filename)))
//        return false;
//        
//    //SetValue(json);
//    return true;
//}