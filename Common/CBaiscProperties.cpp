/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CBaiscProperties.h"
#include "CCommon.h"

CBaiscProperties::CBaiscProperties()
{
    _rotation = 0.0f;
}

float& CBaiscProperties::GetRotation()
{
    return _rotation;
}

void CBaiscProperties::SetRotation(float r)
{
    _rotation = r;
}

sf::Vector2f& CBaiscProperties::GetPosition() 
{
    return _coordinate;
}

void CBaiscProperties::SetPosition(float x, float y)
{
    _coordinate.x = x;
    _coordinate.y = y;
}

sf::Vector2f& CBaiscProperties::GetOffset()
{
    return _offset;
}

void CBaiscProperties::SetOffset(float x, float y)
{
    _offset.x = x;
    _offset.y = y;
}

void CBaiscProperties::SetOffsetX(float x)
{
    _offset.x = x;
}

void CBaiscProperties::SetOffsetY(float y)
{
    _offset.y = y;
}

void CBaiscProperties::SetScale(float x, float y)
{
    _scale.x = x;
    _scale.y = y;
}

void CBaiscProperties::SetScaleX(float x)
{
    _scale.x = x;
}

void CBaiscProperties::SetScaleY(float y)
{
    _scale.y = y;
}
        
sf::Vector2f& CBaiscProperties::GetScale()
{
    return _scale;
}

bool CBaiscProperties::OnLoop()
{
    return _actList.OnLoop() ? false : _actList.IsPause();
}

bool CBaiscProperties::AddAction(CActionBaseClass* act)
{
    if (!act)
        return false;

    _actList.AddAction(act);
    return true;
}

CAction* CBaiscProperties::CreateActionOfRotation(size_t elapsed, float rotation, bool restore, bool pause)
{
    return new CAction(&_rotation, elapsed, rotation, restore, pause);
}

CSimultaneousOfAction* CBaiscProperties::CreateActionOfScale(size_t elapsed, float x, float y, bool restore, bool pause)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CAction(&_scale.x, elapsed, x, restore, pause));
    __result->AddAction(new CAction(&_scale.y, elapsed, y, restore, pause));
    return __result;
}

CAction* CBaiscProperties::CreateActionOfScaleX(size_t elapsed, float x, bool restore, bool pause)
{
    return new CAction(&_scale.x, elapsed, x, restore, pause);
}

CAction* CBaiscProperties::CreateActionOfScaleY(size_t elapsed, float y, bool restore, bool pause)
{
    return new CAction(&_scale.y, elapsed, y, restore, pause);
}

CSimultaneousOfAction* CBaiscProperties::CreateActionOfMove(size_t elapsed, float x, float y, bool restore, bool pause)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CAction(&_coordinate.x, elapsed, x, restore, pause));
    __result->AddAction(new CAction(&_coordinate.y, elapsed, y, restore, pause));
    return __result;
}

CAction* CBaiscProperties::CreateActionOfMoveX(size_t elapsed, float x, bool restore, bool pause)
{
    return new CAction(&_coordinate.x, elapsed, x, restore, pause);
}

CAction* CBaiscProperties::CreateActionOfMoveY(size_t elapsed, float y, bool restore, bool pause)
{
    return new CAction(&_coordinate.y, elapsed, y, restore, pause);
}

void CBaiscProperties::OnSaveData(Object& json) const
{
    CObject::OnSaveData(json);
    json << "x" << _coordinate.x;
    json << "y" << _coordinate.y;
    json << "offset_x" << _offset.x;
    json << "offset_y" << _offset.y;
    json << "scale_x" << _scale.x;
    json << "scale_y" << _scale.y;
    json << "rotation" << _rotation;
}
