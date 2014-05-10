/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CLogBoxControl.h"

CObject* CLogBoxControl::GetObject(std::string name)
{
    if (_logBoxList.count(name) < 1)
        return NULL;

    CBox* __p = &_logBoxList[name];
    return __p;
}

char CLogBoxControl::AddLogBox(std::string name, const char* filename)
{
    if (!IsExists(name)){
        _logBoxList.insert(
            std::pair<std::string,CLogBox>(name, CLogBox()));
    }
    else
        return -1;


    if(_logBoxList[name].LoadBox(filename)){
        _logBoxList[name].CBox::_Alpha = 0;


        return 0;
    }
    else{
        _logBoxList.erase(name);
        return -2;
    }
}

bool CLogBoxControl::DelLogBox(std::string name)
{
    
    if (IsExists(name)){
        _logBoxList.erase(name);
        return true;
    }


    return false;
}

bool CLogBoxControl::OnLButtonUp(int mX, int mY)
{
    map<string, CLogBox>::iterator it;
    for ( it=_logBoxList.begin(); it!=_logBoxList.end(); it++ ){
        if ((*it).second.OnLButtonUp(mX,mY)){
            cout << "LogBox \"" << (*it).first << "\" Left-ButtonUp event has actived." << endl;
            return true;
        }
    }
    return false;
}

bool CLogBoxControl::OnLButtonDown(int mX, int mY)
{
    map<string, CMessageBox>::iterator it;
    for ( it=_logBoxList.begin(); it!=_logBoxList.end(); it++ ){
        if ((*it).second.OnLButtonDown(mX,mY)){
            cout << "LogBox \"" << (*it).first << "\" Left-ButtonDown event has actived." << endl;
            return true;
        }
    }
    return false;
}


void CLogBoxControl::OnLoop(bool &pause)
{
    std::map<std::string, CMessageBox>::iterator it;
    for ( it=_logBoxList.begin(); it !=_logBoxList.end(); it++ )
    {
        if((*it).second.OnLoop()) pause=true;
    }
}



void CLogBoxControl::OnRender(sf::RenderWindow* Surf_Dest)
{
    std::map<std::string, CLogBox>::iterator it;
    
    for ( it=_logBoxList.begin() ; it!=_logBoxList.end(); it++ )
        (*it).second.OnRender(Surf_Dest);
}
