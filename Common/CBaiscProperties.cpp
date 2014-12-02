/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CBaiscProperties.h"

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
