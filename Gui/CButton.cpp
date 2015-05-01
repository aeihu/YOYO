/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CButton.h"

void CButton::Exec(void* data)
{
    //CParser::_Parser.InsertCmdList(_cmdList);
}

bool CButton::CheckList(Object json)
{
    bool result = CButtonBase::CheckList(json);

    if (!json.has<String>("SCRIPT_PATH")){
        cout << "can't find value of SCRIPT_PATH." << endl;
        result = false;
    }
    
    if (!json.has<String>("SCRIPT_SECTION")){
        cout << "can't find value of SCRIPT_SECTION." << endl;
        result = false;
    }
    return result;
}

bool CButton::SetProperty(Object json, bool isLoad)
{
    //return CParser::_Parser.LoadScript(json.get<String>("SCRIPT_PATH").c_str(), 
    //    json.get<String>("SCRIPT_SECTION").c_str(), _cmdList) && 
    //    CButtonBase::SetProperty(json);

    return true;
}

CButton* CButton::Create(const char* filename)
{
    CButton* __btn = new CButton();
    if (__btn->LoadConfigFile(filename)){
        __btn->SetClassName("Button");
        __btn->SetPath(filename);
        __btn->SetLayerOrder(6);
        return __btn;
    }
    
    delete __btn;
    return NULL;
}
