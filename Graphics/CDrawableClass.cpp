/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CDrawableClass.h"
#include "../Common/CResourceControl.h"

CDrawableClass::CDrawableClass()
{
    _layerOrder = 0;
    _alpha = 0.0f;
    _red = _green = _blue = 255.0f;
}

bool CDrawableClass::IsShowed() const
{
    return _alpha > 0;
}

float CDrawableClass::GetAlpha() const
{
    return _alpha;
}

float CDrawableClass::GetRed() const
{
    return _red;
}

float CDrawableClass::GetGreen() const
{
    return _green;
}

float CDrawableClass::GetBlue() const
{
    return _blue;
}

void CDrawableClass::SetRed(int r)
{
    if (r < 0.0f)
        _red = 0.0f;
    else if (r > 255.f)
        _red = 255.0f;
    else
        _red = r;
}

void CDrawableClass::SetGreen(int g)
{
    if (g < 0.0f)
        _green = 0.0f;
    else if (g > 255.f)
        _green = 255.0f;
    else
        _green = g;
}

void CDrawableClass::SetBlue(int b)
{
    if (b < 0.0f)
        _blue = 0.0f;
    else if (b > 255.f)
        _blue = 255.0f;
    else
        _blue = b;
}

void CDrawableClass::SetColor(int r, int g, int b)
{
    SetRed(r);
    SetGreen(g);
    SetBlue(b);
}

void CDrawableClass::SetAlpha(int alpha)
{
    if (alpha > 255)
        _alpha = 255;
    else if (_alpha < 0)
        _alpha = 0;
    else
        _alpha = alpha;
}

unsigned char CDrawableClass::GetLayerOrder() const
{
    return _layerOrder;
}

void CDrawableClass::SetLayerOrder(char order)
{
    _layerOrder = order;
    CResourceControl::_ResourceManager._DrawableObjectControl._isNeedSort = true;
}

void CDrawableClass::SetLayerOrder(vector<char> args)
{
    if (args.size() > 0)
        SetLayerOrder(args[0]);
}

CSimultaneousOfAction* CDrawableClass::CreateActionOfColorTo(size_t elapsed, float r, float g, float b, bool restore)
{
    if (r > 255.0f)
        r = 255.0f;
    else if (r < 0.0f)
        r = 0.0f;
    
    if (g > 255.0f)
        g = 255.0f;
    else if (g < 0.0f)
        g = 0.0f;

    if (b > 255.0f)
        b = 255.0f;
    else if (b < 0.0f)
        b = 0.0f;

    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionTo(&_red, elapsed, r, restore));
    __result->AddAction(new CActionTo(&_green, elapsed, g, restore ));
    __result->AddAction(new CActionTo(&_blue, elapsed, b, restore));
    return __result;
}

CActionTo* CDrawableClass::CreateActionOfColorRedTo(size_t elapsed, float r, bool restore)
{
    if (r > 255.0f)
        r = 255.0f;
    else if (r < 0.0f)
        r = 0.0f;

    return new CActionTo(&_red, elapsed, r, restore);
}

CActionTo* CDrawableClass::CreateActionOfColorGreenTo(size_t elapsed, float g, bool restore)
{
    if (g > 255.0f)
        g = 255.0f;
    else if (g < 0.0f)
        g = 0.0f;

    return new CActionTo(&_green, elapsed, g, restore);
}

CActionTo* CDrawableClass::CreateActionOfColorBlueTo(size_t elapsed, float b, bool restore)
{
    if (b > 255.0f)
        b = 255.0f;
    else if (b < 0.0f)
        b = 0.0f;

    return new CActionTo(&_blue, elapsed, b, restore);
}

CSimultaneousOfAction* CDrawableClass::CreateActionOfColorBy(size_t elapsed, float r, float g, float b, bool restore)
{
    if (r + _red > 255.0f)
        r = 255.0f - _red;
    else if (r + _red < 0.0f)
        r = _red;

    if (g + _green > 255.0f)
        g = 255.0f - _green;
    else if (g + _green < 0.0f)
        g = _green;
    
    if (b + _blue > 255.0f)
        b = 255.0f - _blue;
    else if (b + _blue < 0.0f)
        b = _blue;

    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionBy(&_red, elapsed, r, restore));
    __result->AddAction(new CActionBy(&_green, elapsed, g, restore));
    __result->AddAction(new CActionBy(&_blue, elapsed, b, restore));
    return __result;
}

CActionBy* CDrawableClass::CreateActionOfColorRedBy(size_t elapsed, float r, bool restore)
{
    if (r + _red > 255.0f)
        r = 255.0f - _red;
    else if (r + _red < 0.0f)
        r = _red;

    return new CActionBy(&_red, elapsed, r, restore);
}

CActionBy* CDrawableClass::CreateActionOfColorGreenBy(size_t elapsed, float g, bool restore)
{
    if (g + _green > 255.0f)
        g = 255.0f - _green;
    else if (g + _green < 0.0f)
        g = _green;

    return new CActionBy(&_green, elapsed, g, restore);
}

CActionBy* CDrawableClass::CreateActionOfColorBlueBy(size_t elapsed, float b, bool restore)
{
    if (b + _blue > 255.0f)
        b = 255.0f - _blue;
    else if (b + _blue < 0.0f)
        b = _blue;

    return new CActionBy(&_blue, elapsed, b, restore);
}

CActionTo* CDrawableClass::CreateActionOfAlphaTo(size_t elapsed, float alpha, bool restore)
{
    if (alpha > 255.0f)
        alpha = 255.0f;
    else if (alpha < 0.0f)
        alpha = 0.0f;

    return new CActionTo(&_alpha, elapsed, alpha, restore);
}

CActionBy* CDrawableClass::CreateActionOfAlphaBy(size_t elapsed, float alpha, bool restore)
{
    if (alpha + _alpha > 255.0f)
        alpha = 255.0f - _alpha;
    else if (alpha + _alpha < 0.0f)
        alpha = _alpha;

    return new CActionBy(&_alpha, elapsed, alpha, restore);
}

////////////////////////////////////////////////

void CDrawableClass::CreateActionOfColorToForSelf(size_t elapsed, float r, float g, float b, bool restore)
{
    _actionList.AddAction(CreateActionOfColorTo(elapsed, r, g, b, restore));
}

void CDrawableClass::CreateActionOfColorRedToForSelf(size_t elapsed, float r, bool restore)
{
    _actionList.AddAction(CreateActionOfColorRedTo(elapsed, r, restore));
}

void CDrawableClass::CreateActionOfColorGreenToForSelf(size_t elapsed, float g, bool restore)
{
    _actionList.AddAction(CreateActionOfColorGreenTo(elapsed, g, restore));
}

void CDrawableClass::CreateActionOfColorBlueToForSelf(size_t elapsed, float b, bool restore)
{
    _actionList.AddAction(CreateActionOfColorBlueTo(elapsed, b, restore));
}

void CDrawableClass::CreateActionOfColorByForSelf(size_t elapsed, float r, float g, float b, bool restore)
{
    _actionList.AddAction(CreateActionOfColorBy(elapsed, r, g, b, restore));
}

void CDrawableClass::CreateActionOfColorRedByForSelf(size_t elapsed, float r, bool restore)
{
    _actionList.AddAction(CreateActionOfColorRedBy(elapsed, r, restore));
}

void CDrawableClass::CreateActionOfColorGreenByForSelf(size_t elapsed, float g, bool restore)
{
    _actionList.AddAction(CreateActionOfColorGreenBy(elapsed, g, restore));
}

void CDrawableClass::CreateActionOfColorBlueByForSelf(size_t elapsed, float b, bool restore)
{
    _actionList.AddAction(CreateActionOfColorBlueBy(elapsed, b, restore));
}

void CDrawableClass::CreateActionOfAlphaToForSelf(size_t elapsed, float alpha, bool restore)
{
    _actionList.AddAction(CreateActionOfAlphaTo(elapsed, alpha, restore));
}

void CDrawableClass::CreateActionOfAlphaByForSelf(size_t elapsed, float alpha, bool restore)
{
    _actionList.AddAction(CreateActionOfAlphaBy(elapsed, alpha, restore));
}

void CDrawableClass::OnSaveData(Object& json) const
{
    CBaiscProperties::OnSaveData(json);
    json << "layer_order" << _layerOrder;
    json << "alpha" << _alpha;
    json << "red" << _red;
    json << "green" << _green;
    json << "blue" << _blue;
}

void CDrawableClass::OnLoadData(Object json)
{
    CBaiscProperties::OnLoadData(json);
    _layerOrder = json.get<Number>("layer_order");
    _alpha = json.get<Number>("alpha");
    _red = json.get<Number>("red");
    _green = json.get<Number>("green");
    _blue = json.get<Number>("blue");
}
