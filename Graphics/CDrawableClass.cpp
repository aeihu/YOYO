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
    _isShowed = false;
    _red = _green = _blue = 255.0f;
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

void CDrawableClass::SetLayerOrder(vector<string> args)
{
    if (args.size() > 0)
        SetLayerOrder((unsigned char)atoi(args[0].c_str()));
}

CSimultaneousOfAction* CDrawableClass::CreateActionOfColorTo(size_t elapsed, float r, float g, float b, bool restore, bool pause)
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
    __result->AddAction(new CActionTo(&_red, elapsed, r, restore, pause));
    __result->AddAction(new CActionTo(&_green, elapsed, g, restore, pause));
    __result->AddAction(new CActionTo(&_blue, elapsed, b, restore, pause));
    return __result;
}

CActionTo* CDrawableClass::CreateActionOfColorRedTo(size_t elapsed, float r, bool restore, bool pause)
{
    if (r > 255.0f)
        r = 255.0f;
    else if (r < 0.0f)
        r = 0.0f;

    return new CActionTo(&_red, elapsed, r, restore, pause);
}

CActionTo* CDrawableClass::CreateActionOfColorGreenTo(size_t elapsed, float g, bool restore, bool pause)
{
    if (g > 255.0f)
        g = 255.0f;
    else if (g < 0.0f)
        g = 0.0f;

    return new CActionTo(&_green, elapsed, g, restore, pause);
}

CActionTo* CDrawableClass::CreateActionOfColorBlueTo(size_t elapsed, float b, bool restore, bool pause)
{
    if (b > 255.0f)
        b = 255.0f;
    else if (b < 0.0f)
        b = 0.0f;

    return new CActionTo(&_blue, elapsed, b, restore, pause);
}

CSimultaneousOfAction* CDrawableClass::CreateActionOfColorBy(size_t elapsed, float r, float g, float b, bool restore, bool pause)
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
    __result->AddAction(new CActionBy(&_red, elapsed, r, restore, pause));
    __result->AddAction(new CActionBy(&_green, elapsed, g, restore, pause));
    __result->AddAction(new CActionBy(&_blue, elapsed, b, restore, pause));
    return __result;
}

CActionBy* CDrawableClass::CreateActionOfColorRedBy(size_t elapsed, float r, bool restore, bool pause)
{
    if (r + _red > 255.0f)
        r = 255.0f - _red;
    else if (r + _red < 0.0f)
        r = _red;

    return new CActionBy(&_red, elapsed, r, restore, pause);
}

CActionBy* CDrawableClass::CreateActionOfColorGreenBy(size_t elapsed, float g, bool restore, bool pause)
{
    if (g + _green > 255.0f)
        g = 255.0f - _green;
    else if (g + _green < 0.0f)
        g = _green;

    return new CActionBy(&_green, elapsed, g, restore, pause);
}

CActionBy* CDrawableClass::CreateActionOfColorBlueBy(size_t elapsed, float b, bool restore, bool pause)
{
    if (b + _blue > 255.0f)
        b = 255.0f - _blue;
    else if (b + _blue < 0.0f)
        b = _blue;

    return new CActionBy(&_blue, elapsed, b, restore, pause);
}

CActionTo* CDrawableClass::CreateActionOfAlphaTo(size_t elapsed, float alpha, bool restore, bool pause)
{
    if (alpha > 255.0f)
        alpha = 255.0f;
    else if (alpha < 0.0f)
        alpha = 0.0f;

    return new CActionTo(&_alpha, elapsed, alpha, restore, pause);
}

CActionBy* CDrawableClass::CreateActionOfAlphaBy(size_t elapsed, float alpha, bool restore, bool pause)
{
    if (alpha + _alpha > 255.0f)
        alpha = 255.0f - _alpha;
    else if (alpha + _alpha < 0.0f)
        alpha = _alpha;

    return new CActionBy(&_alpha, elapsed, alpha, restore, pause);
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
