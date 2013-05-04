/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CMessageBoxControl.h"

CMessageBoxControl::CMessageBoxControl()
{}

bool CMessageBoxControl::IsAlreadyExists(std::string name)
{
    return _MessageBoxList.count(name) < 1 ? false : true;
}

char CMessageBoxControl::AddMessageBox(std::string name, const char* filename)
{
    if (!IsAlreadyExists(name)){
        _MessageBoxList.insert(
            std::pair<std::string,CMessageBox>(name, CMessageBox()));
    }
    else
        return -1;

    if(_MessageBoxList[name].LoadBox(filename)){
        _MessageBoxList[name].CBox::_Alpha = 0;

        return 0;
    }
    else{
        _MessageBoxList.erase(name);
        return -2;
    }
}

bool CMessageBoxControl::DelMessageBox(std::string name)
{
    if (IsAlreadyExists(name)){
        _MessageBoxList.erase(name);
        return true;
    }

    return false;
}

bool CMessageBoxControl::SetImageVisibility(std::string name, int alpha, int incr, int msec, bool pause)
{
    if (IsAlreadyExists(name)){
        _MessageBoxList[name].Insert(0,
            alpha, msec, pause,
            &_MessageBoxList[name].CBox::_Alpha,
            incr);

        return true;
    }
    return false;
}

void CMessageBoxControl::OnLoop(bool &pause)
{
    std::map<std::string, CMessageBox>::iterator it;
    for ( it=_MessageBoxList.begin(); it !=_MessageBoxList.end(); it++ )
    {
        if((*it).second.OnLoop()) pause=true;
        //(*it).second.CSequenceOfFrames::_Alpha = (*it).second.CBox::_Alpha;
    }
}

void CMessageBoxControl::OnRender(sf::RenderWindow* Surf_Dest)
{
    std::map<std::string, CMessageBox>::iterator it;

    for ( it=_MessageBoxList.begin() ; it!=_MessageBoxList.end(); it++ )
        (*it).second.OnRender(Surf_Dest);
}
