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
    _childrenList.push_back(&_scrollbar);
    //_spriteList.push_back(make_pair(&_btnArrowUp._sprite, &_btnArrowUp.GetPosition()));
    //_spriteList.push_back(make_pair(&_btnArrowDown._sprite, &_btnArrowDown.GetPosition()));
    //_spriteList.push_back(make_pair(&_btnBar._sprite, &_btnBar.GetPosition()));
}

CLogBox* CLogBox::Create(const char* filename)
{
    CLogBox* __logBox = new CLogBox();
    if (__logBox->LoadConfigFile(filename)){
        __logBox->SetLayerOrder(7);
        return __logBox;
    }
    
    delete __logBox;
    return NULL;
}

bool CLogBox::OnLoop()
{
    //for (unsigned int __i = 0; __i < _visNum; __i++){
    //    if (_scrollbar.GetValue()+__i < _logList.size()){
    //        _logList[_scrollbar.GetValue()+__i]->SetPosition(_Coordinate.x+_logOffset.x, _Coordinate.y+_logOffset.y);
    //        _logList[_scrollbar.GetValue()+__i]->SetAlpha(CBox::GetAlpha());
    //        _logList[_scrollbar.GetValue()+__i]->OnLoop();
    //    }
    //    else
    //        break;
    //}

    bool __result = CBox::OnLoop();

    return __result && _scrollbar.OnLoop();
}

void CLogBox::OnRender(sf::RenderWindow* Surf_Dest)
{
    if (CBox::_visible){
        CBox::OnRender(Surf_Dest);
        
        for (unsigned int __i = 0; __i < _visNum; __i++){
            if (_scrollbar.GetValue()+__i < _logList.size()){
                _logList[_scrollbar.GetValue()+__i]->OnRender(Surf_Dest);
            }
            else
                break;
        }

        _scrollbar.OnRender(Surf_Dest);
    }
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

    if (!_scrollbar.CheckList(list))
        __result = false;

    if (list.count("LOG_OFFSET_X") < 1){
        cout << "can't find value of LOG_OFFSET_X." << endl;
        __result = false;
    }

    if (list.count("LOG_OFFSET_Y") < 1){
        cout << "can't find value of LOG_OFFSET_Y." << endl;
        __result = false;
    }

    if (list.count("LOG_MAXNUM") < 1){
        cout << "can't find value of LOG_MAXNUM." << endl;
        __result = false;
    }

    if (list.count("LOG_VISIBLE_NUM") < 1){
        cout << "can't find value of LOG_VISIBLE_NUM." << endl;
        __result = false;
    }

    if (list.count("SCROLLBAR_OFFSET_X") < 1){
        cout << "can't find value of SCROLLBAR_OFFSET_X." << endl;
        __result = false;
    }

    if (list.count("SCROLLBAR_OFFSET_Y") < 1){
        cout << "can't find value of SCROLLBAR_OFFSET_Y." << endl;
        __result = false;
    }

    return __result;
}

bool CLogBox::SetProperty(map<string, string>& list)
{
    _logMax = atoi(list["LOG_MAXNUM"].c_str());
    _visNum = atoi(list["LOG_VISIBLE_NUM"].c_str());
    _logOffset.x = atof(list["LOG_OFFSET_X"].c_str());
    _logOffset.y = atof(list["LOG_OFFSET_Y"].c_str());
    _scrollbar.SetOffset(atof(list["SCROLLBAR_OFFSET_X"].c_str()), atof(list["SCROLLBAR_OFFSET_Y"].c_str()));

    if (!_scrollbar.SetProperty(list))
        return false;

    return CBox::SetProperty(list);
}

void CLogBox::AddLog(string text, sf::SoundBuffer* voice, sf::Font& font)
{
    if (_logList.size() < _logMax){
        _logList.push_back(new CTextLog());
    }else{
        _logList.push_back(_logList.front());
        _logList.pop_front();
    }
    
    _logList.back()->SetTextLog(text, voice, font);
}

void CLogBox::OnMouseMove(int x, int y)
{
    for (unsigned int __i = 0; __i < _visNum; __i++){
        if (_scrollbar.GetValue()+__i < _logList.size()){
            _logList[_scrollbar.GetValue()+__i]->OnMouseMove(x, y);
        }
        else
            break;
    }

    _scrollbar.OnMouseMove(x, y);
}

bool CLogBox::OnLButtonDown(int x, int y)
{
    for (unsigned int __i = 0; __i < _visNum; __i++){
        if (_scrollbar.GetValue()+__i < _logList.size()){
            if (_logList[_scrollbar.GetValue()+__i]->OnLButtonDown(x, y))
                return true;
        }
        else
            break;
    }

    return _scrollbar.OnLButtonDown(x, y);
}

bool CLogBox::OnLButtonUp(int x, int y)
{
    for (unsigned int __i = 0; __i < _visNum; __i++){
        if (_scrollbar.GetValue()+__i < _logList.size()){
            if (_logList[_scrollbar.GetValue()+__i]->OnLButtonUp(x, y))
                return true;
        }
        else
            break;
    }

    return _scrollbar.OnLButtonUp(x, y);
}
