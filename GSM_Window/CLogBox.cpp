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
    _logRowHeight = _logMax = _visNum = 0;
    _childrenList.push_back(&_scrollbar);
    //_spriteList.push_back(make_pair(&_btnArrowUp._sprite, &_btnArrowUp.GetPosition()));
    //_spriteList.push_back(make_pair(&_btnArrowDown._sprite, &_btnArrowDown.GetPosition()));
    //_spriteList.push_back(make_pair(&_btnBar._sprite, &_btnBar.GetPosition()));
}

CLogBox* CLogBox::Create(const char* filename)
{
    CLogBox* __logBox = new CLogBox();
    if (__logBox->LoadConfigFile(filename)){
        __logBox->SetClassName("logbox");
        __logBox->SetPath(filename);
        __logBox->SetLayerOrder(7);
        return __logBox;
    }
    
    delete __logBox;
    return NULL;
}

bool CLogBox::OnSubLoop()
{
    for (size_t __i = 0; __i < _visNum; __i++){
        if (_scrollbar.GetValue()+__i < _logList.size()){
            _logList[_scrollbar.GetValue()+__i]->SetPosition(CBox::GetPosition().x+_logOffset.x, 
                CBox::GetPosition().y+_logOffset.y + __i * _logRowHeight);
            _logList[_scrollbar.GetValue()+__i]->SetAlpha(CBox::GetAlpha());
            _logList[_scrollbar.GetValue()+__i]->OnLoop();
        }
        else
            break;
    }

    //bool __result = CBox::OnLoop();

    return _scrollbar.OnLoop();
}

void CLogBox::OnSubRender(sf::RenderTarget* Surf_Dest)
{
    for (size_t __i = 0; __i < _visNum; __i++){
        if (_scrollbar.GetValue()+__i < _logList.size()){
            _logList[_scrollbar.GetValue()+__i]->OnRender(Surf_Dest);
        }
        else
            break;
    }

    _scrollbar.OnRender(Surf_Dest);
}

void CLogBox::OnCleanup()
{
    for (size_t __i=0; __i<_logList.size(); __i++){
        _logList[__i]->OnCleanup();
        delete _logList[__i];
    }

    _logList.clear();
}

bool CLogBox::CheckList(Object json)
{
    bool __result = CBox::CheckList(json);

    if (!_scrollbar.CheckList(json))
        __result = false;

    if (!json.has<Number>("LOG_OFFSET_X")){
        cout << "can't find value of LOG_OFFSET_X." << endl;
        __result = false;
    }

    if (!json.has<Number>("LOG_OFFSET_Y")){
        cout << "can't find value of LOG_OFFSET_Y." << endl;
        __result = false;
    }

    if (!json.has<Number>("LOG_MAXNUM")){
        cout << "can't find value of LOG_MAXNUM." << endl;
        __result = false;
    }

    if (!json.has<Number>("LOG_VISIBLE_NUM")){
        cout << "can't find value of LOG_VISIBLE_NUM." << endl;
        __result = false;
    }

    if (!json.has<Number>("LOG_ROW_HEIGHT")){
        cout << "can't find value of LOG_ROW_HEIGHT." << endl;
        __result = false;
    }

    if (!json.has<Number>("SCROLLBAR_OFFSET_X")){
        cout << "can't find value of SCROLLBAR_OFFSET_X." << endl;
        __result = false;
    }

    if (!json.has<Number>("SCROLLBAR_OFFSET_Y")){
        cout << "can't find value of SCROLLBAR_OFFSET_Y." << endl;
        __result = false;
    }

    return __result;
}

bool CLogBox::SetProperty(Object json)
{
    _logMax = json.get<Number>("LOG_MAXNUM");
    _visNum = json.get<Number>("LOG_VISIBLE_NUM");
    _logRowHeight = json.get<Number>("LOG_ROW_HEIGHT");
    _logOffset.x = json.get<Number>("LOG_OFFSET_X");
    _logOffset.y = json.get<Number>("LOG_OFFSET_Y");
    _scrollbar.SetOffset(json.get<Number>("SCROLLBAR_OFFSET_X"), json.get<Number>("SCROLLBAR_OFFSET_Y"));

    if (!_scrollbar.SetProperty(json))
        return false;

    return CBox::SetProperty(json);
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
    _scrollbar.SetMaxValue(_logList.size() <= _visNum ? 0 : _logList.size()-_visNum);
    _scrollbar.SetValue(_logList.size() <= _visNum ? 0 : _logList.size()-_visNum);
}

void CLogBox::AddLog(string text, sf::SoundBuffer* voice)
{
    if (_logList.size() < _logMax){
        _logList.push_back(new CTextLog());
    }else{
        _logList.push_back(_logList.front());
        _logList.pop_front();
    }
    
    _logList.back()->SetTextLog(text, voice);
}

bool CLogBox::OnMouseMove(int x, int y)
{
    for (size_t __i = 0; __i < _visNum; __i++){
        if (_scrollbar.GetValue()+__i < _logList.size()){
            if (_logList[_scrollbar.GetValue()+__i]->OnMouseMove(x, y))
                return true;
        }
        else
            break;
    }

    return _scrollbar.OnMouseMove(x, y);
}

bool CLogBox::OnLButtonDown(int x, int y)
{
    for (size_t __i = 0; __i < _visNum; __i++){
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
    for (size_t __i = 0; __i < _visNum; __i++){
        if (_scrollbar.GetValue()+__i < _logList.size()){
            if (_logList[_scrollbar.GetValue()+__i]->OnLButtonUp(x, y))
                return true;
        }
        else
            break;
    }

    return _scrollbar.OnLButtonUp(x, y);
}
