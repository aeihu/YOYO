/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CButton.h"

void CButton::Exec(void* data)
{
    CParser::_Parser.InsertCmdList(_cmdList);
}

bool CButton::Subclass_CheckList(map<string, string>& list)
{
    bool result = true;
    if (list.count("SCRIPT_PATH") < 1){
        cout << "can't find value of SCRIPT_PATH." << endl;
        result = false;
    }
    
    if (list.count("SCRIPT_SECTION") < 1){
        cout << "can't find value of SCRIPT_SECTION." << endl;
        result = false;
    }
    return result;
}

bool CButton::Subclass_SetProperty(map<string, string>& list)
{
    return CParser::_Parser.LoadScript(list["SCRIPT_PATH"].c_str(), 
        list["SCRIPT_SECTION"].c_str(), _cmdList);
}