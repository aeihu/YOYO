/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CEntityBaiscProperties.h"

float& CEntityBaiscProperties::GetRotation()
{
    return _rotation;
}

void CEntityBaiscProperties::SetRotation(float r)
{
    _rotation = r;
}

sf::Vector2f& CEntityBaiscProperties::GetPosition() 
{
    return _coordinate;
}

void CEntityBaiscProperties::SetPosition(float x, float y)
{
    _coordinate.x = x;
    _coordinate.y = y;
}

sf::Vector2f& CEntityBaiscProperties::GetOffset()
{
    return _offset;
}

void CEntityBaiscProperties::SetOffset(float x, float y)
{
    _offset.x = x;
    _offset.y = y;
}

void CEntityBaiscProperties::SetOffsetX(float x)
{
    _offset.x = x;
}

void CEntityBaiscProperties::SetOffsetY(float y)
{
    _offset.y = y;
}

void CEntityBaiscProperties::SetScale(float x, float y)
{
    _scale.x = x;
    _scale.y = y;
}

void CEntityBaiscProperties::SetScaleX(float x)
{
    _scale.x = x;
}

void CEntityBaiscProperties::SetScaleY(float y)
{
    _scale.y = y;
}
        
sf::Vector2f& CEntityBaiscProperties::GetScale()
{
    return _scale;
}
