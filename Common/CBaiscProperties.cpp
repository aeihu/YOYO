/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CBaiscProperties.h"
#include "CCommon.h"

bool CBaiscProperties::_isActionRunning = false;

CBaiscProperties::CBaiscProperties()
{
    _rotation = 0.0f;
}

void CBaiscProperties::AddAction(CActionBaseClass* act)
{
    _actionList.AddAction(act);
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

void CBaiscProperties::SetPosition(vector<float> args)
{
    if (args.size() >= 2)
        SetPosition(args[0], args[1]);
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

CActionTo* CBaiscProperties::CreateActionOfRotationTo(size_t elapsed, float rotation, bool restore, bool pause)
{
    return new CActionTo(&_rotation, elapsed, rotation, restore, pause);
}

CActionBy* CBaiscProperties::CreateActionOfRotationBy(size_t elapsed, float rotation, bool restore, bool pause)
{
    return new CActionBy(&_rotation, elapsed, rotation, restore, pause);
}

CSimultaneousOfAction* CBaiscProperties::CreateActionOfScaleTo(size_t elapsed, float x, float y, bool restore, bool pause)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionTo(&_scale.x, elapsed, x, restore, pause));
    __result->AddAction(new CActionTo(&_scale.y, elapsed, y, restore, pause));
    return __result;
}

CActionTo* CBaiscProperties::CreateActionOfScaleXTo(size_t elapsed, float x, bool restore, bool pause)
{
    return new CActionTo(&_scale.x, elapsed, x, restore, pause);
}

CActionTo* CBaiscProperties::CreateActionOfScaleYTo(size_t elapsed, float y, bool restore, bool pause)
{
    return new CActionTo(&_scale.y, elapsed, y, restore, pause);
}

CSimultaneousOfAction* CBaiscProperties::CreateActionOfScaleBy(size_t elapsed, float x, float y, bool restore, bool pause)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionBy(&_scale.x, elapsed, x, restore, pause));
    __result->AddAction(new CActionBy(&_scale.y, elapsed, y, restore, pause));
    return __result;
}

CActionBy* CBaiscProperties::CreateActionOfScaleXBy(size_t elapsed, float x, bool restore, bool pause)
{
    return new CActionBy(&_scale.x, elapsed, x, restore, pause);
}

CActionBy* CBaiscProperties::CreateActionOfScaleYBy(size_t elapsed, float y, bool restore, bool pause)
{
    return new CActionBy(&_scale.y, elapsed, y, restore, pause);
}

CSimultaneousOfAction* CBaiscProperties::CreateActionOfMoveTo(size_t elapsed, float x, float y, bool restore, bool pause)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionTo(&_coordinate.x, elapsed, x, restore, pause));
    __result->AddAction(new CActionTo(&_coordinate.y, elapsed, y, restore, pause));
    return __result;
}

CActionTo* CBaiscProperties::CreateActionOfMoveXTo(size_t elapsed, float x, bool restore, bool pause)
{
    return new CActionTo(&_coordinate.x, elapsed, x, restore, pause);
}

CActionTo* CBaiscProperties::CreateActionOfMoveYTo(size_t elapsed, float y, bool restore, bool pause)
{
    return new CActionTo(&_coordinate.y, elapsed, y, restore, pause);
}

CSimultaneousOfAction* CBaiscProperties::CreateActionOfMoveBy(size_t elapsed, float x, float y, bool restore, bool pause)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionBy(&_coordinate.x, elapsed, x, restore, pause));
    __result->AddAction(new CActionBy(&_coordinate.y, elapsed, y, restore, pause));
    return __result;
}

CActionBy* CBaiscProperties::CreateActionOfMoveXBy(size_t elapsed, float x, bool restore, bool pause)
{
    return new CActionBy(&_coordinate.x, elapsed, x, restore, pause);
}

CActionBy* CBaiscProperties::CreateActionOfMoveYBy(size_t elapsed, float y, bool restore, bool pause)
{
    return new CActionBy(&_coordinate.y, elapsed, y, restore, pause);
}

/////////////////////////////////////////////////////

void CBaiscProperties::CreateActionOfRotationToForSelf(size_t elapsed, float rotation, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfRotationTo(elapsed, rotation, restore, pause));
}

void CBaiscProperties::CreateActionOfRotationByForSelf(size_t elapsed, float rotation, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfRotationBy(elapsed, rotation, restore, pause));
}


void CBaiscProperties::CreateActionOfScaleToForSelf(size_t elapsed, float x, float y, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfScaleTo(elapsed, x, y, restore, pause));
}

void CBaiscProperties::CreateActionOfScaleXToForSelf(size_t elapsed, float x, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfScaleXTo(elapsed, x, restore, pause));
}

void CBaiscProperties::CreateActionOfScaleYToForSelf(size_t elapsed, float y, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfScaleYTo(elapsed, y, restore, pause));
}

void CBaiscProperties::CreateActionOfScaleByForSelf(size_t elapsed, float x, float y, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfScaleBy(elapsed, x, y, restore, pause));
}

void CBaiscProperties::CreateActionOfScaleXByForSelf(size_t elapsed, float x, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfScaleXBy(elapsed, x, restore, pause));
}

void CBaiscProperties::CreateActionOfScaleYByForSelf(size_t elapsed, float y, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfScaleYBy(elapsed, y, restore, pause));
}

void CBaiscProperties::CreateActionOfMoveToForSelf(size_t elapsed, float x, float y, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfMoveTo(elapsed, x, y, restore, pause));
}

void CBaiscProperties::CreateActionOfMoveXToForSelf(size_t elapsed, float x, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfMoveXTo(elapsed, x, restore, pause));
}

void CBaiscProperties::CreateActionOfMoveYToForSelf(size_t elapsed, float y, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfMoveYTo(elapsed, y, restore, pause));
}

void CBaiscProperties::CreateActionOfMoveByForSelf(size_t elapsed, float x, float y, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfMoveBy(elapsed, x, y, restore, pause));
}

void CBaiscProperties::CreateActionOfMoveXByForSelf(size_t elapsed, float x, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfMoveXBy(elapsed, x, restore, pause));
}

void CBaiscProperties::CreateActionOfMoveYByForSelf(size_t elapsed, float y, bool restore, bool pause)
{
    _actionList.AddAction(CreateActionOfMoveYBy(elapsed, y, restore, pause));
}

void CBaiscProperties::OnLoop()
{
    _isActionRunning = _actionList.OnLoop();
}

void CBaiscProperties::OnCleanup()
{
    _actionList.OnCleanup();
}

void CBaiscProperties::OnSaveData(Object& json) const
{
    CObject::OnSaveData(json);
    json << "x" << _coordinate.x;
    json << "y" << _coordinate.y;
    json << "scale_x" << _scale.x;
    json << "scale_y" << _scale.y;
    json << "rotation" << _rotation;
}

void CBaiscProperties::OnLoadData(Object json)
{
    _coordinate.x = json.get<Number>("x");
    _coordinate.y = json.get<Number>("y");
    _scale.x = json.get<Number>("scale_x");
    _scale.y = json.get<Number>("scale_y");
    _rotation = json.get<Number>("rotation");
}
