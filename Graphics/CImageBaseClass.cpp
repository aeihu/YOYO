/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
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

void CImageBaseClass::CreateActionOfOriginToForSelf(size_t elapsed, float x, float y, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfOriginTo(elapsed, x, y, restore, pause));
}

void CImageBaseClass::CreateActionOfOriginXToForSelf(size_t elapsed, float x, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfOriginXTo(elapsed, x, restore, pause));
}

void CImageBaseClass::CreateActionOfOriginYToForSelf(size_t elapsed, float y, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfOriginYTo(elapsed, y, restore, pause));
}

void CImageBaseClass::CreateActionOfOriginByForSelf(size_t elapsed, float x, float y, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfOriginBy(elapsed, x, y, restore, pause));
}

void CImageBaseClass::CreateActionOfOriginXByForSelf(size_t elapsed, float x, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfOriginXBy(elapsed, x, restore, pause));
}

void CImageBaseClass::CreateActionOfOriginYByForSelf(size_t elapsed, float y, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfOriginYBy(elapsed, y, restore, pause));
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
}

void CImageBaseClass::OnLoadData(Object json)
{
    CDrawableClass::OnLoadData(json);
    _origin.x = json.get<Number>("origin_x");
    _origin.y = json.get<Number>("origin_y");

    if (_flipX != json.get<Boolean>("flip_x"))
        FlipX();

    if (_flipY != json.get<Boolean>("flip_y"))
        FlipY();
}