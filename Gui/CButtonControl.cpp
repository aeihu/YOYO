/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CButtonControl.h"

CButtonControl::CButtonControl()
{}

bool CButtonControl::IsAlreadyExists(string name)
{
    return _ButtonList.count(name) < 1 ? false : true;
}

char CButtonControl::AddButton(std::string name, const char* filename)
{
    if (!IsAlreadyExists(name)){
        _ButtonList.insert(
            std::pair<string,CButton>(name, CButton()));
    }
    else
        return -1;

    if(_ButtonList[name].LoadButton(filename)){
        _ButtonList[name]._Alpha = 1;

        return 0;
    }
    else{
        _ButtonList.erase(name);
        return -2;
    }
}

bool CButtonControl::DelButton(std::string name)
{
    if (IsAlreadyExists(name)){
        _ButtonList.erase(name);
        return true;
    }

    return false;
}

bool CButtonControl::SetImageVisibility(std::string name, int alpha, int incr, int msec, bool pause)
{
    if (IsAlreadyExists(name)){
        _ButtonList[name].Insert(0,
            alpha, msec, pause,
            &_ButtonList[name]._Alpha,
            incr);

        return true;
    }
    return false;
}

void CButtonControl::OnLoop(bool &pause)
{
    map<string, CButton>::iterator it;
    for ( it=_ButtonList.begin(); it !=_ButtonList.end(); it++ )
    {
        if((*it).second.CImageBaseClass::OnLoop()) pause=true;
    }
}

void CButtonControl::OnRender(sf::RenderWindow* Surf_Dest)
{
    map<std::string, CButton>::iterator it;

    for (it=_ButtonList.begin();it!=_ButtonList.end();it++)
        (*it).second.CImageBaseClass::OnRender(Surf_Dest);
}
