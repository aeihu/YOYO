/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CScrollbar.h"

CScrollbar::CScrollbar()
{
    _isMouseDown =
    _isMouseOver = false;
    _alpha =
    _value =
    _maxValue = 0;
}

void CScrollbar::OnLoop()
{
    if (_maxValue < 1)
        return;

    if (_value >= _maxValue)
        _value = _maxValue-1;
    else if (_value < 0)
        _value = 0;

    _btnBar._Alpha = _btnArrowDown._Alpha = _btnArrowUp._Alpha = _alpha;

    _btnArrowUp.SetPosition(_coordinate.x, _coordinate.y);
    _btnArrowDown.SetPosition(_coordinate.x, _coordinate.y + _height - _btnArrowDown.GetHeight());
    _btnBar.SetPosition(_coordinate.x, 
        _coordinate.y + _btnArrowDown.GetHeight() + 
        ((_height - _btnArrowDown.GetHeight() - _btnArrowUp.GetHeight() - _btnBar.GetHeight())/
        (_maxValue < 1 ? 1.0f : _maxValue)*_value));

    _btnArrowUp.OnLoop();
    _btnArrowDown.OnLoop();
    _btnBar.OnLoop();
}


void CScrollbar::OnRender(sf::RenderWindow* Surf_Dest)
{
    if (_maxValue < 1)
        return;

    _btnBar.OnRender(Surf_Dest);
    _btnArrowUp.OnRender(Surf_Dest);
    _btnArrowDown.OnRender(Surf_Dest);
}

void CScrollbar::OnMouseMove(int x, int y)
{
    if (_maxValue < 1)
        return;

    _btnBar.OnMouseMove(x, y);
    _btnArrowUp.OnMouseMove(x, y);
    _btnArrowDown.OnMouseMove(x, y);

    if (_btnBar.IsMouseDown())
    {
        float __tmp = _btnBar.GetPosition().y;
        float __cell = (_height - _btnArrowDown.GetHeight() - _btnArrowUp.GetHeight())/(_maxValue < 1 ? 1.0f : _maxValue);

        if (y < _coordinate.y + _btnArrowUp.GetHeight())
            _btnBar.SetPosition(_btnBar.GetPosition().x, _coordinate.y + _btnArrowUp.GetHeight());
        else if (y > _btnArrowDown.GetPosition().y - _btnBar.GetHeight())
            _btnBar.SetPosition(_btnBar.GetPosition().x, _btnArrowDown.GetPosition().y - _btnBar.GetHeight());
        else
            _btnBar.SetPosition(_btnBar.GetPosition().x, y);

        _value += static_cast<int>((__tmp - _btnBar.GetPosition().y)/(__cell == 0.0f ? 1.0f : __cell));
    }
}

bool CScrollbar::OnLButtonDown(int x, int y)
{
    if (_maxValue < 1)
        return false;

    if(!_btnBar.OnLButtonDown(x, y))
        if(!_btnArrowUp.OnLButtonDown(x, y))
            return _btnArrowDown.OnLButtonDown(x, y);
    
    return true;
}

bool CScrollbar::OnLButtonUp(int x, int y)
{
    if (_maxValue < 1)
        return false;

    if(!_btnBar.OnLButtonUp(x, y))
        if(!_btnArrowUp.OnLButtonUp(x, y))
            return _btnArrowDown.OnLButtonUp(x, y);

    return true;
}

void CScrollbar::CArrowUpButton::Exec(void *data)
{
    if (data != NULL){
        int* __p = static_cast<int*>(data);
        *__p -= 1;
    }
}

void CScrollbar::CArrowDownButton::Exec(void *data)
{
    if (data != NULL){
        int* __p = static_cast<int*>(data);
        *__p += 1;
    }
}

void CScrollbar::CBarButton::Exec(void *data)
{
}

bool CScrollbar::SetMaxValue(int value)
{
    if (value < 1)
        return true;

    _maxValue = value;
    return true;
}

void CScrollbar::SetPosition(float x, float y)
{
    _coordinate.x = x;
    _coordinate.y = y;
}

int CScrollbar::GetValue() const
{
    return _value;
}

bool CScrollbar::CheckList(map<string, string>& list)
{
    bool __result = true;

    if (list.count("SCROLLBAR_HEIGHT") < 1){
        cout << "can't find value of SCROLLBAR_HEIGHT." << endl;
        __result = false;
    }

    if (list.count("BUTTON_ARROW_DOWN_PATH") < 1){
        cout << "can't find value of BUTTON_ARROW_DOWN_PATH." << endl;
        __result = false;
    }

    if (list.count("BUTTON_ARROW_UP_PATH") < 1){
        cout << "can't find value of BUTTON_ARROW_UP_PATH." << endl;
        __result = false;
    }

    if (list.count("BUTTON_BAR_PATH") < 1){
        cout << "can't find value of BUTTON_BAR_PATH." << endl;
        __result = false;
    }

    return __result;
}

bool CScrollbar::SetProperty(map<string, string>& list)
{
    _height = atof(list["SCROLLBAR_HEIGHT"].c_str());

    if (!_btnArrowUp.LoadConfigFile(list["BUTTON_ARROW_UP_PATH"].c_str()))
        return false;

    if (!_btnArrowDown.LoadConfigFile(list["BUTTON_ARROW_DOWN_PATH"].c_str()))
        return false;

    if (!_btnBar.LoadConfigFile(list["BUTTON_BAR_PATH"].c_str()))
        return false;

    return true;
}
