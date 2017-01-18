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
    _scale.x =
    _scale.y = 1.0f;
    _rotation =
    _coordinate.x =
    _coordinate.y =
    _rotation = 0.0f;
}

void CBaiscProperties::AddAction(CActionBaseClass* act)
{
    _actionList.AddAction(act);
}

float CBaiscProperties::GetRotation()
{
    return _rotation;
}

void CBaiscProperties::SetRotation(float r)
{
    _rotation = r;
}

sf::Vector2f CBaiscProperties::GetPosition() 
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

void CBaiscProperties::SetPositionX(float x)
{
    _coordinate.x = x;
}

void CBaiscProperties::SetPositionY(float y)
{
    _coordinate.y = y;
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

CActionTo* CBaiscProperties::CreateActionOfRotationTo(size_t elapsed, float rotation, bool restore)
{
    return new CActionTo(&_rotation, elapsed, rotation, restore);
}

CActionBy* CBaiscProperties::CreateActionOfRotationBy(size_t elapsed, float rotation, bool restore)
{
    return new CActionBy(&_rotation, elapsed, rotation, restore);
}

CSimultaneousOfAction* CBaiscProperties::CreateActionOfScaleTo(size_t elapsed, float x, float y, bool restore)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionTo(&_scale.x, elapsed, x, restore));
    __result->AddAction(new CActionTo(&_scale.y, elapsed, y, restore));
    return __result;
}

CActionTo* CBaiscProperties::CreateActionOfScaleXTo(size_t elapsed, float x, bool restore)
{
    return new CActionTo(&_scale.x, elapsed, x, restore);
}

CActionTo* CBaiscProperties::CreateActionOfScaleYTo(size_t elapsed, float y, bool restore)
{
    return new CActionTo(&_scale.y, elapsed, y, restore);
}

CSimultaneousOfAction* CBaiscProperties::CreateActionOfScaleBy(size_t elapsed, float x, float y, bool restore)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionBy(&_scale.x, elapsed, x, restore));
    __result->AddAction(new CActionBy(&_scale.y, elapsed, y, restore));
    return __result;
}

CActionBy* CBaiscProperties::CreateActionOfScaleXBy(size_t elapsed, float x, bool restore)
{
    return new CActionBy(&_scale.x, elapsed, x, restore);
}

CActionBy* CBaiscProperties::CreateActionOfScaleYBy(size_t elapsed, float y, bool restore)
{
    return new CActionBy(&_scale.y, elapsed, y, restore);
}

CSimultaneousOfAction* CBaiscProperties::CreateActionOfMoveTo(size_t elapsed, float x, float y, bool restore)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionTo(&_coordinate.x, elapsed, x, restore));
    __result->AddAction(new CActionTo(&_coordinate.y, elapsed, y, restore));
    return __result;
}

CActionTo* CBaiscProperties::CreateActionOfMoveXTo(size_t elapsed, float x, bool restore)
{
    return new CActionTo(&_coordinate.x, elapsed, x, restore);
}

CActionTo* CBaiscProperties::CreateActionOfMoveYTo(size_t elapsed, float y, bool restore)
{
    return new CActionTo(&_coordinate.y, elapsed, y, restore);
}

CSimultaneousOfAction* CBaiscProperties::CreateActionOfMoveBy(size_t elapsed, float x, float y, bool restore)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionBy(&_coordinate.x, elapsed, x, restore));
    __result->AddAction(new CActionBy(&_coordinate.y, elapsed, y, restore));
    return __result;
}

CActionBy* CBaiscProperties::CreateActionOfMoveXBy(size_t elapsed, float x, bool restore)
{
    return new CActionBy(&_coordinate.x, elapsed, x, restore);
}

CActionBy* CBaiscProperties::CreateActionOfMoveYBy(size_t elapsed, float y, bool restore)
{
    return new CActionBy(&_coordinate.y, elapsed, y, restore);
}

/////////////////////////////////////////////////////

void CBaiscProperties::CreateActionOfRotationToForSelf(size_t elapsed, float rotation, bool restore)
{
    _actionList.AddAction(CreateActionOfRotationTo(elapsed, rotation, restore));
}

void CBaiscProperties::CreateActionOfRotationByForSelf(size_t elapsed, float rotation, bool restore)
{
    _actionList.AddAction(CreateActionOfRotationBy(elapsed, rotation, restore));
}


void CBaiscProperties::CreateActionOfScaleToForSelf(size_t elapsed, float x, float y, bool restore)
{
    _actionList.AddAction(CreateActionOfScaleTo(elapsed, x, y, restore));
}

void CBaiscProperties::CreateActionOfScaleXToForSelf(size_t elapsed, float x, bool restore)
{
    _actionList.AddAction(CreateActionOfScaleXTo(elapsed, x, restore));
}

void CBaiscProperties::CreateActionOfScaleYToForSelf(size_t elapsed, float y, bool restore)
{
    _actionList.AddAction(CreateActionOfScaleYTo(elapsed, y, restore));
}

void CBaiscProperties::CreateActionOfScaleByForSelf(size_t elapsed, float x, float y, bool restore)
{
    _actionList.AddAction(CreateActionOfScaleBy(elapsed, x, y, restore));
}

void CBaiscProperties::CreateActionOfScaleXByForSelf(size_t elapsed, float x, bool restore)
{
    _actionList.AddAction(CreateActionOfScaleXBy(elapsed, x, restore));
}

void CBaiscProperties::CreateActionOfScaleYByForSelf(size_t elapsed, float y, bool restore)
{
    _actionList.AddAction(CreateActionOfScaleYBy(elapsed, y, restore));
}

void CBaiscProperties::CreateActionOfMoveToForSelf(size_t elapsed, float x, float y, bool restore)
{
    _actionList.AddAction(CreateActionOfMoveTo(elapsed, x, y, restore));
}

void CBaiscProperties::CreateActionOfMoveXToForSelf(size_t elapsed, float x, bool restore)
{
    _actionList.AddAction(CreateActionOfMoveXTo(elapsed, x, restore));
}

void CBaiscProperties::CreateActionOfMoveYToForSelf(size_t elapsed, float y, bool restore)
{
    _actionList.AddAction(CreateActionOfMoveYTo(elapsed, y, restore));
}

void CBaiscProperties::CreateActionOfMoveByForSelf(size_t elapsed, float x, float y, bool restore)
{
    _actionList.AddAction(CreateActionOfMoveBy(elapsed, x, y, restore));
}

void CBaiscProperties::CreateActionOfMoveXByForSelf(size_t elapsed, float x, bool restore)
{
    _actionList.AddAction(CreateActionOfMoveXBy(elapsed, x, restore));
}

void CBaiscProperties::CreateActionOfMoveYByForSelf(size_t elapsed, float y, bool restore)
{
    _actionList.AddAction(CreateActionOfMoveYBy(elapsed, y, restore));
}

CSimultaneousOfAction* CBaiscProperties::CreateActionOfOriginBy(size_t elapsed, float x, float y, bool restore)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionBy(&_origin.x, elapsed, x, restore));
    __result->AddAction(new CActionBy(&_origin.y, elapsed, y, restore));
    return __result;
}

CActionBy* CBaiscProperties::CreateActionOfOriginXBy(size_t elapsed, float x, bool restore)
{
    return new CActionBy(&_origin.x, elapsed, x, restore);
}

CActionBy* CBaiscProperties::CreateActionOfOriginYBy(size_t elapsed, float y, bool restore)
{
    return new CActionBy(&_origin.y, elapsed, y, restore);
}

CSimultaneousOfAction* CBaiscProperties::CreateActionOfOriginTo(size_t elapsed, float x, float y, bool restore)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionTo(&_origin.x, elapsed, x, restore));
    __result->AddAction(new CActionTo(&_origin.y, elapsed, y, restore));
    return __result;
}

CActionTo* CBaiscProperties::CreateActionOfOriginXTo(size_t elapsed, float x, bool restore)
{
    return new CActionTo(&_origin.x, elapsed, x, restore);
}

CActionTo* CBaiscProperties::CreateActionOfOriginYTo(size_t elapsed, float y, bool restore)
{
    return new CActionTo(&_origin.y, elapsed, y, restore);
}

void CBaiscProperties::CreateActionOfOriginToForSelf(size_t elapsed, float x, float y, bool restore)
{
    _actionList.AddAction(CreateActionOfOriginTo(elapsed, x, y, restore));
}

void CBaiscProperties::CreateActionOfOriginXToForSelf(size_t elapsed, float x, bool restore)
{
    _actionList.AddAction(CreateActionOfOriginXTo(elapsed, x, restore));
}

void CBaiscProperties::CreateActionOfOriginYToForSelf(size_t elapsed, float y, bool restore)
{
    _actionList.AddAction(CreateActionOfOriginYTo(elapsed, y, restore));
}

void CBaiscProperties::CreateActionOfOriginByForSelf(size_t elapsed, float x, float y, bool restore)
{
    _actionList.AddAction(CreateActionOfOriginBy(elapsed, x, y, restore));
}

void CBaiscProperties::CreateActionOfOriginXByForSelf(size_t elapsed, float x, bool restore)
{
    _actionList.AddAction(CreateActionOfOriginXBy(elapsed, x, restore));
}

void CBaiscProperties::CreateActionOfOriginYByForSelf(size_t elapsed, float y, bool restore)
{
    _actionList.AddAction(CreateActionOfOriginYBy(elapsed, y, restore));
}

sf::Vector2f CBaiscProperties::GetOrigin()
{
    return _origin;
}

void CBaiscProperties::SetOrigin(float x, float y)
{
    _origin.x = x;
    _origin.y = y;
}

void CBaiscProperties::SetOriginX(float x)
{
    _origin.x = x;
}

void CBaiscProperties::SetOriginY(float y)
{
    _origin.y = y;
}

void CBaiscProperties::OnLoop()
{
    _isActionRunning = _actionList.OnLoop();
}

void CBaiscProperties::CleanActionList()
{
    _actionList.OnCleanup();
}

void CBaiscProperties::OnCleanup()
{
    CleanActionList();
}

void CBaiscProperties::OnSaveData(Object& json) const
{
    CObject::OnSaveData(json);
    json << "x" << _coordinate.x;
    json << "y" << _coordinate.y;
    json << "scale_x" << _scale.x;
    json << "scale_y" << _scale.y;
    json << "rotation" << _rotation;
    json << "origin_x" << _origin.x;
    json << "origin_y" << _origin.y;
}

void CBaiscProperties::OnLoadData(Object json)
{
    _coordinate.x = json.get<Number>("x");
    _coordinate.y = json.get<Number>("y");
    _scale.x = json.get<Number>("scale_x");
    _scale.y = json.get<Number>("scale_y");
    _rotation = json.get<Number>("rotation");
    _origin.x = json.get<Number>("origin_x");
    _origin.y = json.get<Number>("origin_y");
}
