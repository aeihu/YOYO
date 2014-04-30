/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
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
    return _messageBoxList.count(name) < 1 ? false : true;
}

char CMessageBoxControl::AddMessageBox(std::string name, const char* filename)
{
    if (!IsAlreadyExists(name)){
        _messageBoxList.insert(
            std::pair<std::string,CMessageBox>(name, CMessageBox()));
    }
    else
        return -1;

    if(_messageBoxList[name].LoadBox(filename)){
        _messageBoxList[name].CBox::_Alpha = 0;

        return 0;
    }
    else{
        _messageBoxList.erase(name);
        return -2;
    }
}

bool CMessageBoxControl::DelMessageBox(std::string name)
{
    if (IsAlreadyExists(name)){
        _messageBoxList.erase(name);
        return true;
    }

    return false;
}

bool CMessageBoxControl::OnLButtonUp(int mX, int mY)
{
    map<string, CMessageBox>::iterator it;
    for ( it=_messageBoxList.begin(); it!=_messageBoxList.end(); it++ ){
        if ((*it).second.OnLButtonUp(mX,mY)){
            cout << "MessageBox \"" << (*it).first << "\" Left-ButtonUp event has actived." << endl;
            return true;
        }
    }
    return false;
}

bool CMessageBoxControl::OnLButtonDown(int mX, int mY)
{
    map<string, CMessageBox>::iterator it;
    for ( it=_messageBoxList.begin(); it!=_messageBoxList.end(); it++ ){
        if ((*it).second.OnLButtonDown(mX,mY)){
            cout << "MessageBox \"" << (*it).first << "\" Left-ButtonDown event has actived." << endl;
            return true;
        }
    }
    return false;
}

void CMessageBoxControl::OnLoop(bool &pause)
{
    std::map<std::string, CMessageBox>::iterator it;
    for ( it=_messageBoxList.begin(); it !=_messageBoxList.end(); it++ )
    {
        if((*it).second.OnLoop()) pause=true;
        //(*it).second.CSequenceOfFrames::_Alpha = (*it).second.CBox::_Alpha;
    }
}

void CMessageBoxControl::OnRender(sf::RenderWindow* Surf_Dest)
{
    std::map<std::string, CMessageBox>::iterator it;

    for ( it=_messageBoxList.begin() ; it!=_messageBoxList.end(); it++ )
        (*it).second.OnRender(Surf_Dest);
}

CImageBaseClass* CMessageBoxControl::GetObject(std::string name)
{
    if (_messageBoxList.count(name) < 1)
        return NULL;

    CBox* __p = &_messageBoxList[name];
    return __p;
}

void CMessageBoxControl::OnCleanup()
{
    _messageBoxList.clear();
}
