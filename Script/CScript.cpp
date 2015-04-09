/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CScript.h"
#include "../Common/Cio.h"
#include "../Parser/CParser.h"

bool CScript::AddScript(string name, Array scr)
{
    if (_scriptList.count(name) > 0)
        return false;
    
    _scriptList[name] = new CSequenceOfAction();

    for (size_t i=0; i<scr.size(); i++)
        CParser::_Parser.Execute(scr, i, _scriptList[name], true);
        
    return true;
}
        
bool CScript::DelScript(string name)
{
    if (_scriptList.count(name) < 1)
        return false;

    _scriptList.erase(name);
    return true;
}
        
void CScript::OnCleanup()
{
    for (map<string, CSequenceOfAction*>::const_iterator it=_scriptList.begin();it!=_scriptList.end(); it++){
        (*it).second->OnCleanup();
        delete (*it).second;
    }

    _scriptList.clear();
}
