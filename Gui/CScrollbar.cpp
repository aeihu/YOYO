/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CScrollbar.h"

CScrollbar::CScrollbar()
{
    _obj = NULL;
    _incr = 0.f;
    _isMouseDown =
    _isMouseOver = false;
    _value =
    _maxValue = 0;
    AddChildNode(&_btnBar);
    AddChildNode(&_btnArrowUp);
    AddChildNode(&_btnArrowDown);
}

bool CScrollbar::OnMouseWheel(int delta)
{
    if (IsShowed()){
        if (_actionList.GetSize() < 1){
            if (delta > 0)
                Positive();
            else
                Negative();

            return true;
        }
    }

    return false;
}

bool CScrollbar::SetMaxValue(int value)
{
    if (value < 1)
        return false;

    _maxValue = value;
    _incr = (GetHeight() - (float)_btnBar.GetHeight()) / (float)_maxValue;
    return true;
}

void CScrollbar::SetObjectForCallback(CScrollbarCallback* obj)
{
    if (obj)
        _obj = obj;
}

void CScrollbar::Ref()
{
    _btnBar.SetPosition(
        _btnBar.GetPosition().x,
        _incr * _value);
}

void CScrollbar::SetValue(int val)
{
    _value = val;
    if (_value > _maxValue)
        _value = _maxValue;
    else if (_value < 0)
        _value = 0;

    Ref();
    if (_obj)
        _obj->SetValue(val);
}

int CScrollbar::GetValue() const
{
    return _value;
}

bool CScrollbar::Positive()
{
    if (_value > 0){
        _value--;
        Ref();
        if (_obj)
            _obj->SetValue(_value);
        return true;
    }
    else{
        if (_obj)
            _obj->PositiveOverflow();
    }

    return false;
}

bool CScrollbar::Negative()
{
    if (_value < _maxValue){
        _value++;
        Ref();
        if (_obj)
            _obj->SetValue(_value);
        return true;
    }
    else{
        if (_obj)
            _obj->NegativeOverflow();
    }

    return false;
}

//================================
//property:
//* PATH,
//JIUGONG
//{
//* WIDTH,
//* HEIGHT,
//* LEFT_WIDTH,
//* RIGHT_WIDTH,
//* TOP_HEIGHT,
//* BOTTOM_HEIGHT,
//}
//* UP_BUTTON
//{
//* PATH,
//* WIDTH,
//* HEIGHT,
//* MAX_FRAMES,
//* FRAME_RATE,
//}
//* DOWN_BUTTON
//{
//* PATH,
//* WIDTH,
//* HEIGHT,
//* MAX_FRAMES,
//* FRAME_RATE,
//}
//* BAR
//{
//* PATH,
//* WIDTH,
//* HEIGHT,
//* MAX_FRAMES,
//* FRAME_RATE,
//}
//ORDER,
//SCALE,
//SCALE_X,
//SCALE_Y,
//ROTATION,
//ORIGIN_X,
//ORIGIN_Y,
//X,
//Y,
//RED,
//GREEN,
//BLUE,
//ALPHA,
//================================
bool CScrollbar::CheckList(const Object& json)
{
    bool __result = CBox::CheckList(json);

    for (int i = 0; i < 3; i++){
        string __name = i == 0 ? "UP_BUTTON" : i == 1 ? "DOWN_BUTTON" : "BAR";
        if (json.has<Object>(__name)){
            const Object& __obj = json.get<Object>(__name);

            if (!__obj.has<String>("PATH")){
                cout << "can't find value of PATH." << endl;
                __result = false;
            }

            if (!__obj.has<Number>("WIDTH")){
                cout << "can't find value of WIDTH." << endl;
                __result = false;
            }

            if (!__obj.has<Number>("HEIGHT")){
                cout << "can't find value of HEIGHT." << endl;
                __result = false;
            }

            if (!__obj.has<Number>("MAX_FRAMES")){
                cout << "can't find value of MAX_FRAMES." << endl;
                __result = false;
            }

            if (!__obj.has<Number>("FRAME_RATE")){
                cout << "can't find value of FRAME_RATE." << endl;
                __result = false;
            }
        }
        else{
            cout << "can't find value of " << __name << "." << endl;
            __result = false;
        }
    }

    return __result;
}

bool CScrollbar::SetProperty(const Object& json, bool isLoad)
{
    if (!_btnArrowUp.SetProperty(json.get<Object>("UP_BUTTON"), isLoad) ||
        !_btnArrowDown.SetProperty(json.get<Object>("DOWN_BUTTON"), isLoad) ||
        !_btnBar.SetProperty(json.get<Object>("BAR"), isLoad))
        return false;

    return CBox::SetProperty(json, isLoad);
}

//============================================

void CScrollbar::CArrowUpButton::Exec(void *data)
{
    if (_baseNode){
        CScrollbar* __scrollbar = static_cast<CScrollbar*>(_baseNode);
        __scrollbar->Positive();
    }
}

void CScrollbar::CArrowDownButton::Exec(void *data)
{
    if (_baseNode){
        CScrollbar* __scrollbar = static_cast<CScrollbar*>(_baseNode);
        __scrollbar->Negative();
    }
}

void CScrollbar::CBarButton::Exec(void *data)
{
}
