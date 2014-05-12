/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CLogBox.h"

CLogBox::CLogBox()
{
    _logMax = _visNum = 0;
}

bool CLogBox::OnLoop()
{
    for (unsigned int __i = 0; __i < _visNum; __i++){
        if (_value+__i < _logList.size()){
            _logList[_value+__i]->OnLoop();
        }
        else
            break;
    }

    CBox::OnLoop();
    CScrollbar::OnLoop();
    return false;
}

void CLogBox::OnRender(sf::RenderWindow* Surf_Dest)
{
    CBox::OnRender(Surf_Dest);
    
    for (unsigned int __i = 0; __i < _visNum; __i++){
        if (_value+__i < _logList.size()){
            _logList[_value+__i]->OnRender(Surf_Dest);
        }
        else
            break;
    }

    CScrollbar::OnRender(Surf_Dest);
}

void CLogBox::OnCleanup()
{
    for (unsigned int __i=0; __i<_logList.size(); __i++){
        _logList[__i]->OnCleanup();
        delete _logList[__i];
    }

    _logList.clear();
}

bool CLogBox::CheckList(map<string, string>& list)
{
    bool __result = CBox::CheckList(list);
    return __result;
}

bool CLogBox::SetProperty(map<string, string>& list)
{
    return CBox::SetProperty(list);
}

void CLogBox::AddLog(sf::Text text, sf::SoundBuffer* voice)
{
    if (_logList.size() < _logMax){
        _logList.push_back(new CTextLog());
    }else{
        _logList.push_back(_logList.front());
        _logList.pop_front();
    }
    
    _logList.back()->SetTextLog(text, voice);
}

void CLogBox::OnMouseMove(int x, int y)
{
    for (unsigned int __i = 0; __i < _visNum; __i++){
        if (_value+__i < _logList.size()){
            _logList[_value+__i]->OnMouseMove(x, y);
        }
        else
            break;
    }

    CScrollbar::OnMouseMove(x, y);
}

bool CLogBox::OnLButtonDown(int x, int y)
{
    for (unsigned int __i = 0; __i < _visNum; __i++){
        if (_value+__i < _logList.size()){
            if (_logList[_value+__i]->OnLButtonDown(x, y))
                return true;
        }
        else
            break;
    }

    return CScrollbar::OnLButtonDown(x, y);
}

bool CLogBox::OnLButtonUp(int x, int y)
{
    for (unsigned int __i = 0; __i < _visNum; __i++){
        if (_value+__i < _logList.size()){
            if (_logList[_value+__i]->OnLButtonUp(x, y))
                return true;
        }
        else
            break;
    }

    return CScrollbar::OnLButtonUp(x, y);
}
