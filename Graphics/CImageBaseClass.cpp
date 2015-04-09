/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CImageBaseClass.h"

CImageBaseClass::CImageBaseClass(float x, float y)
{
    _scale.x =
    _scale.y = 1.0f;
    _rotation = 0.0f;
    _coordinate.x = x;
    _coordinate.y = y;
    _flipX = _flipY = _isShowed = false;
    _red = _green = _blue = 255.0f;
}

CImageBaseClass::~CImageBaseClass()
{}
         
void CImageBaseClass::FlipX()
{
    _flipX = !_flipX;
}
        
void CImageBaseClass::FlipY()
{
    _flipY = !_flipY;
}

void CImageBaseClass::SetAlpha(int alpha)
{
    if (alpha > 255)
        alpha = 255;
    else if (_alpha < 0)
        alpha = 0;

    _alpha = alpha;
}

CSimultaneousOfAction* CImageBaseClass::CreateActionOfColorTo(size_t elapsed, float r, float g, float b, bool restore, bool pause)
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

CActionTo* CImageBaseClass::CreateActionOfColorRedTo(size_t elapsed, float r, bool restore, bool pause)
{
    if (r > 255.0f)
        r = 255.0f;
    else if (r < 0.0f)
        r = 0.0f;

    return new CActionTo(&_red, elapsed, r, restore, pause);
}

CActionTo* CImageBaseClass::CreateActionOfColorGreenTo(size_t elapsed, float g, bool restore, bool pause)
{
    if (g > 255.0f)
        g = 255.0f;
    else if (g < 0.0f)
        g = 0.0f;

    return new CActionTo(&_green, elapsed, g, restore, pause);
}

CActionTo* CImageBaseClass::CreateActionOfColorBlueTo(size_t elapsed, float b, bool restore, bool pause)
{
    if (b > 255.0f)
        b = 255.0f;
    else if (b < 0.0f)
        b = 0.0f;

    return new CActionTo(&_blue, elapsed, b, restore, pause);
}

CSimultaneousOfAction* CImageBaseClass::CreateActionOfColorBy(size_t elapsed, float r, float g, float b, bool restore, bool pause)
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

CActionBy* CImageBaseClass::CreateActionOfColorRedBy(size_t elapsed, float r, bool restore, bool pause)
{
    if (r + _red > 255.0f)
        r = 255.0f - _red;
    else if (r + _red < 0.0f)
        r = _red;

    return new CActionBy(&_red, elapsed, r, restore, pause);
}

CActionBy* CImageBaseClass::CreateActionOfColorGreenBy(size_t elapsed, float g, bool restore, bool pause)
{
    if (g + _green > 255.0f)
        g = 255.0f - _green;
    else if (g + _green < 0.0f)
        g = _green;

    return new CActionBy(&_green, elapsed, g, restore, pause);
}

CActionBy* CImageBaseClass::CreateActionOfColorBlueBy(size_t elapsed, float b, bool restore, bool pause)
{
    if (b + _blue > 255.0f)
        b = 255.0f - _blue;
    else if (b + _blue < 0.0f)
        b = _blue;

    return new CActionBy(&_blue, elapsed, b, restore, pause);
}

CSimultaneousOfAction* CImageBaseClass::CreateActionOfOriginBy(size_t elapsed, float x, float y, bool restore, bool pause)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionBy(&_origin.x, elapsed, x, restore, pause));
    __result->AddAction(new CActionBy(&_origin.y, elapsed, y, restore, pause));
    return __result;
}

CActionBy* CImageBaseClass::CreateActionOfOriginXBy(size_t elapsed, float x, bool restore, bool pause)
{
    return new CActionBy(&_origin.x, elapsed, x, restore, pause);
}

CActionBy* CImageBaseClass::CreateActionOfOriginYBy(size_t elapsed, float y, bool restore, bool pause)
{
    return new CActionBy(&_origin.y, elapsed, y, restore, pause);
}

CSimultaneousOfAction* CImageBaseClass::CreateActionOfOriginTo(size_t elapsed, float x, float y, bool restore, bool pause)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionTo(&_origin.x, elapsed, x, restore, pause));
    __result->AddAction(new CActionTo(&_origin.y, elapsed, y, restore, pause));
    return __result;
}

CActionTo* CImageBaseClass::CreateActionOfOriginXTo(size_t elapsed, float x, bool restore, bool pause)
{
    return new CActionTo(&_origin.x, elapsed, x, restore, pause);
}

CActionTo* CImageBaseClass::CreateActionOfOriginYTo(size_t elapsed, float y, bool restore, bool pause)
{
    return new CActionTo(&_origin.y, elapsed, y, restore, pause);
}

const sf::Vector2f& CImageBaseClass::GetOrigin() const
{
    return _origin;
}

void CImageBaseClass::SetOrigin(float x, float y)
{
    _origin.x = x;
    _origin.y = y;
}

void CImageBaseClass::SetOriginX(float x)
{
    _origin.x = x;
}

void CImageBaseClass::SetOriginY(float y)
{
    _origin.y = y;
}

const float& CImageBaseClass::GetAlpha() const
{
    return _alpha;
}

bool CImageBaseClass::GetVisible() const
{
    return _isShowed;
}

void CImageBaseClass::OnSaveData(Object& json) const
{
    CDrawableClass::OnSaveData(json);
    json << "origin_x" << _origin.x;
    json << "origin_y" << _origin.y;
    json << "flip_x" << _flipX;
    json << "flip_y" << _flipY;
    json << "red" << _red;
    json << "green" << _green;
    json << "blue" << _blue;
}

void CImageBaseClass::OnLoadData(Object json)
{
    CDrawableClass::OnLoadData(json);
    _origin.x = json.get<Number>("origin_x");
    _origin.y = json.get<Number>("origin_y");
    _red = json.get<Number>("red");
    _green = json.get<Number>("green");
    _blue = json.get<Number>("blue");

    if (_flipX != json.get<Boolean>("flip_x"))
        FlipX();

    if (_flipY != json.get<Boolean>("flip_y"))
        FlipY();
}