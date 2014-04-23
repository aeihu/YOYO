/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
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
    return _buttonList.count(name) < 1 ? false : true;
}

char CButtonControl::AddButton(std::string name, const char* filename)
{
    if (!IsAlreadyExists(name)){
        _buttonList.insert(
            std::pair<string,CButton>(name, CButton()));
    }
    else
        return -1;

    if(_buttonList[name].LoadButton(filename)){
        _buttonList[name]._Alpha = 0;

        return 0;
    }
    else{
        _buttonList.erase(name);
        return -2;
    }
}

bool CButtonControl::DelButton(std::string name)
{
    if (IsAlreadyExists(name)){
        _buttonList.erase(name);
        return true;
    }

    return false;
}

bool CButtonControl::SetImageVisibility(std::string name, int alpha, int incr, bool pause)
{
    if (incr == 0)
        incr = CCommon::common.INCREMENT;

    if (IsAlreadyExists(name)){
        _buttonList[name].Insert(0,
            alpha, pause,
            &_buttonList[name]._Alpha,
            incr);

        return true;
    }
    return false;
}

void CButtonControl::OnLoop(bool &pause)
{
    map<string, CButton>::iterator it;
    for ( it=_buttonList.begin(); it !=_buttonList.end(); it++ )
    {
        if((*it).second.CImageBaseClass::OnLoop()) pause=true;
    }
}

void CButtonControl::OnRender(sf::RenderWindow* Surf_Dest)
{
    map<std::string, CButton>::iterator it;
    for (it=_buttonList.begin();it!=_buttonList.end();it++)
        (*it).second.CImageBaseClass::OnRender(Surf_Dest);
}

CImageBaseClass* CButtonControl::GetObject(std::string name)
{
    if (_buttonList.count(name) < 1)
        return NULL;

    return &_buttonList[name];
}

void CButtonControl::OnCleanup()
{
    _buttonList.clear();
}

void CButtonControl::OnMouseMove(int mX, int mY)
{
    map<std::string, CButton>::iterator it;
    for ( it=_buttonList.begin();it!=_buttonList.end(); it++ )
        (*it).second.OnMouseMove(mX,mY);
}

bool CButtonControl::OnLButtonUp(int mX, int mY)
{
    map<std::string, CButton>::iterator it;
    for ( it=_buttonList.begin();it!=_buttonList.end(); it++ )
    {
        if ((*it).second.OnLButtonUp(mX,mY)){
            cout << "Button \"" << (*it).first << "\" Left-ButtonUp event has actived." << endl;
            return true;
        }
    }

    return false;
}

bool CButtonControl::OnLButtonDown(int mX, int mY)
{
    map<std::string, CButton>::iterator it;
    for ( it=_buttonList.begin();it!=_buttonList.end(); it++ )
    {
        if ((*it).second.OnLButtonDown(mX,mY)){
            cout << "Button \"" << (*it).first << "\" Left-ButtonDown event has actived." << endl;
            return true;
        }
    }

    return false;
}
